#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <functional>
#include <stdexcept>

namespace LI {

    class ThreadPool {
    public:
        ThreadPool(size_t threads);
        ~ThreadPool();

        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args)
            -> std::future<typename std::result_of<F(Args...)>::type>;


    private:
        // 线程函数
        void worker_loop();

        // 用于存储工作线程的vector
        std::vector<std::thread> workers;

        // 任务队列
        std::queue<std::function<void()>> tasks;

        // 同步原语
        std::mutex queue_mutex;
         std::condition_variable condv;
        bool stop;

        // 用于保存promise的容器，以便我们可以返回futures
        std::vector<std::shared_ptr<std::promise<void>>> promises;
    };
    template<class _Callable, class... Args>
    auto ThreadPool::enqueue(_Callable&& _f, Args&&... args)
        -> std::future< typename std::result_of<_Callable(Args...)>::type >
    {
        using return_type = typename std::result_of<_Callable(Args...)>::type;

            // 创建一个 shared_ptr 指向 packaged_task 对象
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<_Callable>(_f), std::forward<Args>(args)...)
            );

            // 获取 future 对象
            std::future<return_type> res = task->get_future();

            // 将任务包装成 std::function 并推送到队列中
            {
                std::unique_lock<std::mutex> lock(queue_mutex);

                // 不要在锁定的范围内调用 task()
                // 相反，将 task 添加到队列中，并通知可能正在等待的线程
                tasks.emplace([task](){ (*task)(); });
                condv.notify_one(); // 唤醒一个等待的线程
            }

            return res;
    }

    // 这里不需要extern template

} // namespace LI

#endif // THREADPOOL_H_
