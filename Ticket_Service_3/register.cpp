#include "register.h"
#include "ui_register.h"
#include "connection.h"
#include "User.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->pushButton_reg,SIGNAL(clicked()),this,SLOT(pushButton_reg_clicked()));
    connect(ui->pushButton_can,SIGNAL(clicked()),this,SLOT(close()));

    btnGroupSex = new QButtonGroup(this);
    btnGroupSex->addButton(ui->radioButton_male, 0);
    btnGroupSex->addButton(ui->radioButton_female, 1);
}

Register::~Register()
{
    delete ui;
}

void Register::pushButton_can_clicked()
{
    close();
}

void Register::pushButton_reg_clicked()
{
   if(createDatabase())
   {
       QSqlQuery query;
       QString name=ui->lineEdit_name->text();
       QString username=ui->lineEdit_user->text();

       SEX sex;
       if(!btnGroupSex->checkedId())
       {
           sex=male;
       }
       else
       {
           sex=female;
       }
       //QString sex=ui->lineEdit_sex->text();
       QString password=ui->lineEdit_password->text();
       QString repassword=ui->lineEdit_repassword->text();
       QString id=ui->lineEdit_znumber->text();
       QString tele=ui->lineEdit_tele->text();
       if(!is_blank())
       {
           bool nofound=true;
           bool nofound_passenger=true;
           bool nofound_admin=true;
           query.exec("select * from passenger");
           while(query.next())
           {
               if(query.value("username").toString()==username)
               {
                   nofound_passenger=false;
                   break;
               }
           }
           query.exec("select * from admin");
           while(query.next())
           {
               if(query.value("username").toString()==username)
               {
                   nofound_passenger=false;
                   break;
               }
           }
           if(nofound_passenger==false||nofound_admin==false)
           {
               nofound=false;
           }
           if(nofound)//数据库中检索用户名
           {
               if(password==repassword)
               {
                   query.prepare("insert into passenger(username,name,sex,id,tele,password) "
                                  "values(:username, :name,:sex,:id,:tele,:password)") ;
                   query.bindValue(":username",username);
                   query.bindValue(":name",name);
                   query.bindValue(":sex",sex);
                   query.bindValue(":id",id);
                   query.bindValue(":tele",tele);
                   query.bindValue(":password",password);
                   query.exec();
                   QMessageBox::about(this,tr("Congratulations!"),tr("Successfully Register!"));
                   this->close();
               }
               else
               {
                   QMessageBox::critical(0,tr("warning"),tr("two passwords is not same!"));
               }
           }
           else
           {
               QMessageBox::critical(0,tr("warning"),tr("the username is exist!"));
           }
       }
       else
       {
           QMessageBox::critical(0,tr("warning"),tr("Some lines are blank!"));
       }
   }
   else
   {
       QMessageBox::critical(0,"warning","disconnect!");
   }
}

bool Register::is_blank()
{
    if(ui->lineEdit_name->text()==""||
            ui->lineEdit_password->text()==""||
            ui->lineEdit_repassword->text()==""||
            ui->lineEdit_tele->text()==""||
            ui->lineEdit_user->text()==""||
            ui->lineEdit_znumber->text()=="")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
