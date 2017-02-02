#include "changepassword.h"
#include "ui_changepassword.h"
#include "info_database.h"
#include <QMessageBox>

changepassword::changepassword(Passenger &p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);
//********
    pas=new Passenger(p);
//**********
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton_2_clicked()));
}

changepassword::~changepassword()
{
    delete ui;
}

void changepassword::pushButton_2_clicked()
{
    close();
}
//**************************************************************
void changepassword::on_pushButton_clicked()
{
    QString oldPass=ui->lineEdit_now->text();
    QString newPass=ui->lineEdit_new->text();
    QString rePass=ui->lineEdit_re->text();
    if(pas->getPassword()==oldPass)
    {
        if(newPass==rePass)
        {
            if(newPass==oldPass)
            {
                QMessageBox::critical(0,tr("warning"),tr("new passwords is same as now password!"));
            }
            else
            {
                pas->setPassword(newPass);
                writePassenger(*pas);
                close();
            }
        }
        else
        {
            QMessageBox::critical(0,tr("warning"),tr("two new passwords is not same!"));
        }
    }
    else
    {
        QMessageBox::critical(0,tr("warning"),tr("Current password is wrong!"));
    }
}
