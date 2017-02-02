#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signin.h"
#include "register.h"
#include "userpage.h"
#include "traininfo.h"
#include "changetrain.h"
#include "connection.h"
#include "Ticket.h"
#include "info_database.h"
#include <QSqlTableModel>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(bool islog,bool isadmin,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->is_log=islog;
    this->is_admin=isadmin;
    is_again=false;

    sysTime=QDateTime::currentDateTime();//显示当前时间
    ui->dateEdit_data->setDate(sysTime.date());
    ui->label_4->setAlignment(Qt::AlignCenter);

    if(!is_log)
    {
        ui->buyButton->setVisible(false);
        ui->userPassageButton->setVisible(false);
        ui->pushButton_add->setVisible(false);
        ui->pushButton_change->setVisible(false);
        ui->pushButton_delete->setVisible(false);
        ui->label_welcome->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->logoff_button->setVisible(false);
    }
    else
    {
        ui->signinButton->setVisible(false);
        ui->registerButton->setVisible(false);
        ui->lineEdit->setText(username);
        ui->lineEdit->setEnabled(false);
        //*****************************************************************
        ui->lineEdit->setStyleSheet("background-color:rgb(240, 240, 240)");
        //*********************************************************************
        if(!is_admin)
        {
            ui->pushButton_add->setVisible(false);
            ui->pushButton_change->setVisible(false);
            ui->pushButton_delete->setVisible(false);

        }
        else
        {
            ui->buyButton->setVisible(false);
            ui->userPassageButton->setVisible(false);

        }
    }

    connect(ui->signinButton,SIGNAL(clicked()),this,SLOT(signinButton_clicked()));
    connect(ui->registerButton,SIGNAL(clicked()),this,SLOT(registerButton_clicked()));
    connect(ui->userPassageButton,SIGNAL(clicked()),this,SLOT(userpageButton_clicked()));
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(pushButton_add_clicked()));
    connect(ui->checkButton,SIGNAL(clicked()),this,SLOT(checkButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIs_log(QString u)
{
    is_log=true;
    username=u;
    if(is_log)
    {
        ui->signinButton->setVisible(false);
        ui->registerButton->setVisible(false);
        ui->label_welcome->setVisible(true);
        ui->logoff_button->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->lineEdit->setText(username);
    }
}

void MainWindow::setIs_admin(bool judge)
{
    is_admin=judge;
    if(is_admin)
    {
        ui->pushButton_add->setVisible(true);
        ui->pushButton_change->setVisible(true);
        ui->pushButton_delete->setVisible(true);
    }
    else
    {
        ui->userPassageButton->setVisible(true);
        ui->buyButton->setVisible(true);
    }
}

void MainWindow::signinButton_clicked()
{
    Signin signDialog(this);
    signDialog.exec();
}

void MainWindow::registerButton_clicked()
{
    Register reg;
    reg.exec();
}

void MainWindow::userpageButton_clicked()
{
    userpage userp(username);
    userp.exec();
}

void MainWindow::pushButton_add_clicked()
{
    traininfo newtrain;
    newtrain.exec();
}

void MainWindow::checkButton_clicked()//数据库查询操作
{

    if(createDatabase())
    {
         QSqlTableModel *model=new QSqlTableModel(this);
         model->setTable("train");
         model->setHeaderData(0,Qt::Horizontal,tr("车次编号"));
         model->setHeaderData(1,Qt::Horizontal,tr("/   车次类型   /"));
         model->setHeaderData(2,Qt::Horizontal,tr("/                出发时间                /"));
         model->setHeaderData(3,Qt::Horizontal,tr("/                到站时间                /"));
         model->setHeaderData(4,Qt::Horizontal,tr("始发车站"));
         model->setHeaderData(5,Qt::Horizontal,tr("到达车站"));
         model->setHeaderData(6,Qt::Horizontal,tr("车票价格"));
         model->setHeaderData(7,Qt::Horizontal,tr("余票数量"));
         model->setHeaderData(8,Qt::Horizontal,tr("/            发车日期            /"));

//
//**************************************************************
         ui->tableViewinfo->setModel(model);
         ui->tableViewinfo->resizeColumnsToContents();

//恰当的设置列宽********************************************************
//*****************************************************************

         model->setEditStrategy(QSqlTableModel::OnManualSubmit);
         ui->tableViewinfo->setSelectionMode(QAbstractItemView::SingleSelection);
         ui->tableViewinfo->setSelectionBehavior(QAbstractItemView::SelectRows);

         ui->tableViewinfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
         QString begin=ui->lineEdit_start->text();
         QString end=ui->lineEdit_end->text();
         QDate date=ui->dateEdit_data->date();
         QString date_str=date.toString();
         model->setFilter(QString("beginstation='%1' and endstation='%2'  and begindate='%3'").arg(begin).arg(end).arg(date_str));
         model->select();
         model->removeColumn(0);
         ui->tableViewinfo->setModel(model);
    }
}



void MainWindow::on_buyButton_clicked()//获取选中行
{
    int row=ui->tableViewinfo->currentIndex().row();
    //*********************************************
    if(row==-1)
    {
        QMessageBox::critical(this,tr("warning"),tr("Didn't choose a train!"));
    }
    else
    {
    //***********************************************
        QAbstractItemModel *model = ui->tableViewinfo->model();
        if(model->data(model->index(row,7)).toInt()>0)
        {
//******************************************************
            QString No_1=model->data(model->index(row,0)).toString();
            QString  begintime_1=model->data(model->index(row,2)).toString();
            Ticket tic_1=readTicket(username,No_1,begintime_1);
            qDebug()<<tic_1.getnum();
            if(tic_1.getnum()!=0){
                QMessageBox::critical(this,tr("Warning"),tr("您已购票!"));
            }
            else
            {
//*******************************************************
                    QString begin_time=model->data(model->index(row,2)).toString();
                    QDateTime begintime=QDateTime::fromString(begin_time,Qt::TextDate);
                    if(begintime>sysTime.addSecs(1800))
                    {
                        if (QMessageBox::Yes == QMessageBox::question(this,
                                                                  tr("Make Sure"),
                                                                  tr("Are you sure to buy it?"),
                                                                  QMessageBox::Yes | QMessageBox::No,
                                                                  QMessageBox::Yes))
                        {
                            trainBuy.setNO(model->data(model->index(row,0)).toString());
                            trainBuy.settype(model->data(model->index(row,1)).toString());
                            QString begin_time=model->data(model->index(row,2)).toString();
                            trainBuy.setBeginTime(QDateTime::fromString(begin_time,Qt::TextDate));
                            QString end_time=model->data(model->index(row,3)).toString();
                            trainBuy.setEndTime(QDateTime::fromString(end_time,Qt::TextDate));
                            trainBuy.setBeginStation(model->data(model->index(row,4)).toString());
                            trainBuy.setEndStation(model->data(model->index(row,5)).toString());
                            trainBuy.setValue(model->data(model->index(row,6)).toInt());
                            trainBuy.setRestNum(model->data(model->index(row,7)).toInt()-1);
                            trainBuy.initSeat();
                            qDebug()<<trainBuy.getNO();

                //***********************************************************可视化选座
                            tableWidget = new QTableWidget(24,6);
                            tableWidget->setWindowTitle(tr("Choose Seat"));
                            tableWidget->resize(320, 500);  //设置表格
                            QStringList header;
                            header<<"1"<<"2"<<"3"<<tr("走廊")<<"4"<<"5";
                            tableWidget->setHorizontalHeaderLabels(header);
                            tableWidget->verticalHeader()->setVisible(false);
                            tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
                            tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);  //选中单个目标
                            tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //选中单个目标

                            for(int row=0;row<24;row++)
                            {
                                tableWidget->setRowHeight(row,30);
                            }
                            for(int column=0;column<6;column++)
                            {
                                tableWidget->setColumnWidth(column,50);
                            }
                            int seatNum=1;
                            for(int i=0;i<24;i++)
                            {
                                for(int j=0;j<6;j++)
                                {
                                    if(j==3)
                                    {
                                        QTableWidgetItem *item=new QTableWidgetItem("");
                                        tableWidget->setItem(i,j,item);
                                        item->setBackgroundColor(Qt::lightGray);
                                        //设置颜色，为走廊
                                    }
                                    else
                                    {
                                        if(j<3)
                                        {
                                            seatNum=i*5+j+1;
                                        }
                                        else
                                        {
                                            seatNum=i*5+j;
                                        }

                                        QTableWidgetItem *item=new QTableWidgetItem( QString("%1").arg(seatNum));
                                        tableWidget->setItem(i,j,item);
                                        if(trainBuy.getSeat()[seatNum-1]==1)
                                        {
                                            item->setBackgroundColor(Qt::yellow);
                                        }
                                        else
                                        {
                                            item->setBackgroundColor(Qt::blue);
                                        }
                                    }
                                }
                            }
                            tableWidget->show();
                            connect(tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(double_clicked(int,int)));
                //************************************************************************

/*                            qDebug()<<row;
                            int seatchosen;
                            int i=row;
                            int j=column;
                            if(j<3)
                            {
                                seatchosen=i*5+j+1;
                            }
                            else
                            {
                                seatchosen=i*5+j;
                            }
                            trainBuy.changeSeat(seatchosen);
                            writeTrain(trainBuy);

                            int num=seatchosen;
                            Ticket ticketBuy(aPassenger,trainBuy,num);
                            qDebug()<<ticketBuy.getpassenger().getUsername();
                            writeTicket(ticketBuy);
*/
                        }

                    }
                    else
                    {
                        QMessageBox::critical(this,tr("Warning"),tr("It's too late, can't buy ticket of this train!"));
                    }
                }
        }
        else
        {
            QMessageBox::critical(this,tr("Warning"),tr("Don't have tickets!"));
        }
    }
}

void MainWindow:: on_pushButton_change_clicked()
{
    int row=ui->tableViewinfo->currentIndex().row();
//*******************************************************************
    if(row==-1)
    {
        QMessageBox::critical(this,tr("warning"),tr("Didn't choose a train!"));
    }
    else
    {
//****************************************************************
        QAbstractItemModel *model = ui->tableViewinfo->model();
        QString searchNO=model->data(model->index(row,0)).toString();
        if(1)//在车票表内搜索该车次，若未找到****************************************************************
        {
            Train trainChange;//创建已购买的车票对象中的车次对象
            trainChange.setNO(model->data(model->index(row,0)).toString());
            trainChange.settype(model->data(model->index(row,1)).toString());

            QString begin_time=model->data(model->index(row,2)).toString();
            trainChange.setBeginTime(QDateTime::fromString(begin_time,Qt::TextDate));
            QString end_time=model->data(model->index(row,3)).toString();
            trainChange.setEndTime(QDateTime::fromString(end_time,Qt::TextDate));

            trainChange.setBeginStation(model->data(model->index(row,4)).toString());
            trainChange.setEndStation(model->data(model->index(row,5)).toString());
            trainChange.setValue(model->data(model->index(row,6)).toInt());
            changetrain changeDialog(trainChange);
            changeDialog.exec();
        }
        else
        {
            QMessageBox::critical(this,"warning","tickets of this train have been sold, please don't change it!");
        }
    }
}
//***********************************************2:24,删除按钮
void MainWindow::on_pushButton_delete_clicked()
{
    int row=ui->tableViewinfo->currentIndex().row();
    if(row==-1)
    {
        QMessageBox::critical(this,tr("warning"),tr("Didn't choose a train!"));
    }
    else
    {
        QAbstractItemModel *model = ui->tableViewinfo->model();
        QString NO=model->data(model->index(row,0)).toString();
        QString begin_time=model->data(model->index(row,2)).toString();
        delete_train(NO,begin_time);
    }
}
//***************************************************


void MainWindow::on_logoff_button_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                              tr("Make Sure"),
                                              tr("Are you sure to log off?"),
                                              QMessageBox::Yes | QMessageBox::No,
                                              QMessageBox::Yes))
    {
        is_again=true;
        close();
    }
}

bool MainWindow::getIs_again()
{
    return is_again;
}

void MainWindow::double_clicked(int row,int column)
{
    qDebug()<<row;
    int seatchosen;
    int i=row;
    int j=column;
    if(j==3)
    {
        QMessageBox::critical(this,tr("Waring"),tr("Here is corridor, can't be chosen!"));
        tableWidget->close();
    }
    else
    {
        if(j<3)
        {
            seatchosen=i*5+j+1;
        }
        else
        {
            seatchosen=i*5+j;
        }
        trainBuy.changeSeat(seatchosen);
        writeTrain(trainBuy);

        Passenger aPassenger=readPassenger(username);

        int num=seatchosen;
        Ticket ticketBuy(aPassenger,trainBuy,num);
        qDebug()<<ticketBuy.getpassenger().getUsername();
        writeTicket(ticketBuy);
        tableWidget->close();
    }
}
