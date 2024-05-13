#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QList>
#include <QModelIndex>
#include "mainwindow.h"
#include "ShareData.h"
#include "chatRoomClient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class sessionWindow; }
QT_END_NAMESPACE

class sessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    sessionWindow(QWidget *parent = nullptr);
    ~sessionWindow();
    qint8 num_textEdit_2=0;
    qint8 num_textEdit=0;
    QString unmask_to_mask="";
    QString mask_to_unmask="";

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_plainTextEdit_blockCountChanged(int newBlockCount);

    //void on_listView_indexesMoved(const QList<QModelIndex> &indexes);


    void on_radioButton_clicked();

    //void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_textEdit_copyAvailable(bool b);

    void on_comboBox_activated(const QString &arg1);

    void on_radioButton_3_clicked();

    //void on_textEdit_2_copyAvailable(bool b);

    void on_textEdit_2_copyAvailable(bool b);

    void on_radioButton_2_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_label_linkActivated(const QString &link);

private:
    Ui::sessionWindow *ui;
};
#endif // SESSIONWINDOW_H
