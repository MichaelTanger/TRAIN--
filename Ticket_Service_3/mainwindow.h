#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "User.h"
#include "Train.h"
#include <QString>
#include <QDateTime>
#include<QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool islog=false,bool isadmin=false,QWidget *parent = 0);//默认值设为未登录
    ~MainWindow();
    void setIs_log(QString u);
    void setIs_admin(bool judge);
    bool getIs_again();

private slots:
    void signinButton_clicked();
    void registerButton_clicked();
    void userpageButton_clicked();
    void pushButton_add_clicked();
    void checkButton_clicked();
    void on_buyButton_clicked();
    void on_pushButton_change_clicked();
    void on_pushButton_delete_clicked();
    void on_logoff_button_clicked();
    void double_clicked(int,int);

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget;
    bool is_log;
    bool is_admin;
    bool is_again;
    QString username;
    QDateTime sysTime;
    int seatrow;
    int seatcolumn;
    Train trainBuy;
//    Passenger aPassenger;
//    Administrator aAdmin;
};

#endif // MAINWINDOW_H
