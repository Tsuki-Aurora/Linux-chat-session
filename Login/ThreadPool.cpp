#include"ThreadPool.hpp"
namespace LI{

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lk(queue_mutex);
        stop = true;
    }
    condv.notify_all(); // 唤醒所有线程
    for (std::thread& worker : workers) {
        worker.join();
    }
}
ThreadPool::ThreadPool(size_t threads): stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        // 新增线程
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                // 取任务
                {
                    std::unique_lock<std::mutex> lk(this->queue_mutex);
                    // 等待锁 且 满足条件变量
                    this->condv.wait(lk,
                        [this]() {
                            return this->stop || !this->tasks.empty();
                    });
                    // 保证队列为空 且 有终止标记
                    if (this->stop && this->tasks.empty()) {
                        return;
                    }
                    task = std::move(this->tasks.front()); // 避免复制
                    this->tasks.pop();
                    // 出作用域 lk 自动 unlock()
                }

                task(); // 执行任务
            }
        } );
    }
}



}
