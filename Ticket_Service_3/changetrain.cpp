#include "changetrain.h"
#include "ui_changetrain.h"
#include "info_database.h"
#include <QMessageBox>

changetrain::changetrain(Train train,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changetrain)
{
    ui->setupUi(this);
    ui->lineEdit_NO->setEnabled(false);
    ui->dateTimeEdit_start->setEnabled(false);
    ui->lineEdit_NO->setText(train.getNO());
    ui->dateTimeEdit_start->setDateTime(train.getBeginTime());

    ui->dateTimeEdit_end->setDateTime(train.getEndTime());
    ui->lineEdit_starts->setText(train.getBeginStation());
    ui->lineEdit_ends->setText(train.getEndStation());
    ui->lineEdit_value->setText(QString("%1").arg(train.getValue()));
    ui->comboBox->setCurrentText(train.gettype());
}

changetrain::~changetrain()
{
    delete ui;
}

void changetrain::on_pushButton_clicked()
{
    Train changedtrain;
    changedtrain.setNO(ui->lineEdit_NO->text());
    changedtrain.setBeginStation(ui->lineEdit_starts->text());
    changedtrain.setEndStation(ui->lineEdit_ends->text());
    changedtrain.setValue(ui->lineEdit_value->text().toDouble());
    changedtrain.setBeginTime(ui->dateTimeEdit_start->dateTime());
    changedtrain.setEndTime(ui->dateTimeEdit_end->dateTime());
    changedtrain.settype(ui->comboBox->currentText());
    switch(ui->comboBox->currentIndex())
    {
    case 0:{
        changedtrain.setRestNum(120);
        break;}
    case 1:{
        changedtrain.setRestNum(60);
        break;}
    case 2:{
        changedtrain.setRestNum(120);
        break;}
    case 3:{
        changedtrain.setRestNum(60);
        break;}
    case 4:{
        changedtrain.setRestNum(120);
        break;}
    default:
        break;
    }
    writeTrain(changedtrain);
    QMessageBox::about(this,tr("OK"),tr("Successfully Change!"));
    close();
}

void changetrain::on_pushButton_2_clicked()
{
    close();
}
