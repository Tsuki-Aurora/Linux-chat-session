#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include "chatRoomServer.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWindow; }
QT_END_NAMESPACE

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::ServerWindow *ui;
};
#endif // SERVERWINDOW_H
