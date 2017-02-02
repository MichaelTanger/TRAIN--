#include "signin.h"
#include "ui_signin.h"
#include "register.h"
#include<QMessageBox>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include<QDebug>
Signin::Signin(MainWindow *m,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
    main=m;
    match=false;
    isAdmin=false;
    connect(ui->RegisterButton,SIGNAL(clicked()),this,SLOT(RegisterButton_clicked()));
    connect(ui->SigninButton,SIGNAL(clicked()),this,SLOT(SigninButton_clicked()));
}
Signin::~Signin()
{
    delete ui;
}
void Signin::RegisterButton_clicked()
{
    Register reg;
    reg.exec();
}

void Signin::SigninButton_clicked()
{
    judge();
    if(match)
    {
        main->setIs_log(ui->TextUsername->text());
        if(isAdmin)
        {
            main->setIs_admin(true);
        }
        else
        {
            main->setIs_admin(false);
        }
        close();
    }
    else{
        QMessageBox::critical(0,"error","wrong username or password");
    }
}
void Signin::judge(){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    QString _username=ui->TextUsername->text();
    QString _password=ui->TextPassword->text();
    query.exec("select * from admin");
    while(query.next())
    {
        if(query.value(0).toString()==_username&&query.value(1).toString()==_password)
        {
            isAdmin=true;
            match=true;
        }
        else if(query.value(0).toString()==_username&&query.value(1).toString()!=_password)
        {
            isAdmin=true;
        }
        else
        {
        }
    }
    if(!isAdmin)
    {
        query.exec("select * from passenger ");
        while(query.next())
        {
            if(query.value(0).toString()==_username&&query.value(5).toString()==_password)
            {
                match=true;
                break;
            }
        }
    }
}
