#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include"mainwindow.h"

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(MainWindow *m,QWidget *parent = 0);
    ~Signin();
    void judge();//检查用户名和密码和数据库是否匹配,检查是否是管理员

private slots:
    void RegisterButton_clicked();
    void SigninButton_clicked();
signals:
    void signinInfo();
private:
    Ui::Signin *ui;
    MainWindow *main;
    bool match;
    bool isAdmin;


};

#endif // SIGNIN_H
