#include "traininfo.h"
#include "ui_traininfo.h"
#include "info_database.h"
#include <QMessageBox>
#include <QDebug>

traininfo::traininfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::traininfo)
{
    ui->setupUi(this);
    newtrain=new Train();

    sysTime=QDateTime::currentDateTime();//显示当前时间
    ui->dateTimeEdit_start->setDateTime(sysTime);
    ui->dateTimeEdit_end->setDateTime(sysTime);
}

traininfo::~traininfo()
{
    delete ui;
    delete newtrain;
    newtrain=NULL;
}

void traininfo::on_pushButton_2_clicked()
{
    close();
}

void traininfo::on_pushButton_clicked()
{
    newtrain->setNO(ui->lineEdit_NO->text());
    newtrain->setBeginStation(ui->lineEdit_starts->text());
    newtrain->setEndStation(ui->lineEdit_ends->text());
    newtrain->setValue(ui->lineEdit_value->text().toDouble());
    newtrain->setBeginTime(ui->dateTimeEdit_start->dateTime());
    newtrain->setEndTime(ui->dateTimeEdit_end->dateTime());
    newtrain->settype(ui->comboBox->currentText());
    switch(ui->comboBox->currentIndex())
    {
    case 0:{
        newtrain->setRestNum(120);
        break;}
    case 1:{
        newtrain->setRestNum(60);
        break;}
    case 2:{
        newtrain->setRestNum(120);
        break;}
    case 3:{
        newtrain->setRestNum(60);
        break;}
    case 4:{
        newtrain->setRestNum(120);
        break;}
    default:
        break;
    }
    writeTrain(*newtrain);
    QMessageBox::about(this,tr("OK"),tr("Successfully Add!"));
    close();
}
