#include"Train.h"
#include<iostream>
#include"connection.h"
using namespace std;

Train::Train(QString n, QString t, QString bs, QString es, QDateTime bt, QDateTime et, double v, int r)
{
	NO = n;
	type = t;
    beginStation = bs;
    endStation = es;
    beginTime = bt;
    endTime = et;
    value = v;
	restNum = r;

}
Train::Train(Train &t0)
{
    NO = t0.getNO();
    type = t0.gettype();
    beginStation = t0.getBeginStation();
    endStation = t0.getEndStation();
    beginTime = t0.getBeginTime();
    endTime = t0.getEndTime();
    value = t0.getValue();
    restNum = t0.getRestNum();
    for(int i=0;i<120;i++)
    {
        seat[i]=t0.getSeat()[i];
    }
}

void Train::initSeat()//init seat infomation**************************
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select from ticket where NO==:NO and begintime==:begintime");
    query.bindValue(":NO",NO);
    query.bindValue(":begintime",beginTime.toString());
    while(query.next())
    {
        seat[query.value(4).toInt()-1]=1;
    }
}

void Train::setNO(QString n){NO=n;}
void Train::settype(QString t){type=t;}
void Train::setBeginStation(QString bs){beginStation=bs;}
void Train::setEndStation(QString es){endStation=es;}
void Train::setBeginTime(QDateTime bt){beginTime=bt;}
void Train::setEndTime(QDateTime et){endTime=et;}
void Train::setValue(double v){value=v;}
void Train::setRestNum(int r){restNum=r;}
void Train::changeSeat(int seat_num)//ticket is selled
{
    seat[seat_num-1]=1;//*****************************
}
