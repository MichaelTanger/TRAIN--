#include "userpage.h"
#include "ui_userpage.h"
#include "User.h"
#include "changepassword.h"
#include "info_database.h"
#include <QDebug>
#include<QSqlTableModel>
userpage::userpage(QString username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userpage)
{
    ui->setupUi(this);
    ui->pushButtonEdit_ok->setVisible(false);
    this->username=username;

    Passenger p(readPassenger(username));
    aPassenger=new Passenger(p);
    //-----------------显示我的订单
   QSqlTableModel *model=new QSqlTableModel();
   model->setTable("ticket");
   model->setHeaderData(0,Qt::Horizontal,tr("用户账号"));
   model->setHeaderData(1,Qt::Horizontal,tr("车次编号"));
   model->setHeaderData(2,Qt::Horizontal,tr("真实姓名"));
   model->setHeaderData(3,Qt::Horizontal,tr("座位号码"));
   model->setHeaderData(4,Qt::Horizontal,tr("/                出发时间                /"));
   model->setHeaderData(5,Qt::Horizontal,tr("/                到站时间                /"));
   model->setHeaderData(6,Qt::Horizontal,tr("始发车站"));
   model->setHeaderData(7,Qt::Horizontal,tr("终点车站"));
   model->setHeaderData(8,Qt::Horizontal,tr("车票价格"));
   model->setHeaderData(9,Qt::Horizontal,tr("/   车次类型   /"));
   model->setEditStrategy(QSqlTableModel::OnManualSubmit);
           ui->tableView_ticket->setSelectionMode(QAbstractItemView::SingleSelection);
           ui->tableView_ticket->setSelectionBehavior(QAbstractItemView::SelectRows);
           ui->tableView_ticket->resizeColumnsToContents();
           ui->tableView_ticket->setEditTriggers(QAbstractItemView::NoEditTriggers);
           model->setFilter(QString("username=='%1'").arg(username));
           model->select();
           model->removeColumn(0);
           ui->tableView_ticket->setModel(model);
        //---------------------显示我的订单


    qDebug()<<aPassenger->getTele();
    ui->lineEdit_user_2->setText(this->username);
    ui->lineEdit_name_2->setText(p.getName());
    ui->lineEdit_znumber_2->setText(aPassenger->getId());
    ui->lineEdit_tele_2->setText(aPassenger->getTele());
    if(aPassenger->getSex()==0)
    {
        ui->radioButton_male->setChecked(true);
    }
    else
    {
        ui->radioButton_female->setChecked(true);
    }

    connect(ui->pushButtonEdit,SIGNAL(clicked()),this,SLOT(pushButtonEdit_clicked()));
    connect(ui->pushButtonEdit_ok,SIGNAL(clicked()),this,SLOT(pushButtonEdit_ok_clicked()));
    connect(ui->pushButton_change,SIGNAL(clicked()),this,SLOT(pushButton_change_clicked()));

    btnGroupSex = new QButtonGroup(this);
    btnGroupSex->addButton(ui->radioButton_male, 0);
    btnGroupSex->addButton(ui->radioButton_female, 1);
}

userpage::~userpage()
{
    delete ui;
    delete aPassenger;
}

void userpage::pushButtonEdit_clicked()
{
    ui->pushButtonEdit->setVisible(false);
    ui->pushButtonEdit_ok->setVisible(true);

    ui->lineEdit_name_2->setEnabled(true);
    ui->lineEdit_tele_2->setEnabled(true);
    ui->lineEdit_znumber_2->setEnabled(true);
    ui->radioButton_male->setEnabled(true);
    ui->radioButton_female->setEnabled(true);
}

void userpage::pushButtonEdit_ok_clicked()
{
    //    QString username=ui->lineEdit_user->text();//默认不能更改用户名
    if(ui->lineEdit_name_2->text()!="")
    {
        aPassenger->setName(ui->lineEdit_name_2->text());
    }
    if(!btnGroupSex->checkedId())
    {
        aPassenger->setSex(male);
    }
    else
    {
        aPassenger->setSex(female);
    }
    if(ui->lineEdit_tele_2->text()!="")
    {
        aPassenger->setTele(ui->lineEdit_tele_2->text());
    }
    if(ui->lineEdit_znumber_2->text()!="")
    {
        aPassenger->setId(ui->lineEdit_znumber_2->text());
    }
    //writeUser();//调用相关数据库的函数，写入
    writePassenger(*aPassenger);
    close();
}

void userpage::pushButton_change_clicked()
{
    changepassword change(*aPassenger);
    change.exec();
}
