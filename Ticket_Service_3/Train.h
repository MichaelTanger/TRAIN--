#ifndef TRAIN_H
#define TRAIN_H

#include<QWidget>
#include<QDateTime>
#include<QString>
using namespace std;

//enum { Tsit, Tlay, Ksit, Klay, G };//�г����
class Train//����ָ���Ĳ�ѯ��ʽ��õģ�data������վ���յ�վ�����û������
{
private:
    QString NO;
    QString type;
    QString beginStation;
    QString endStation;
    QDateTime beginTime;
    QDateTime endTime;
    double value;
	int restNum;//��Ʊ����
    bool seat[120];
public:
    Train(){}
    Train(QString n, QString t, QString bs, QString es, QDateTime bt, QDateTime et, double v, int r);
    Train(Train &t0);
    QString getNO()const{ return  NO; }
    QString gettype()const{ return  type; }
    QString getBeginStation()const{ return  beginStation; }
    QString getEndStation()const{ return endStation; }
    QDateTime getBeginTime()const{ return  beginTime; }
    QDateTime getEndTime()const{ return  endTime; }
    double getValue()const{ return value; }
	int getRestNum()const{ return restNum; }

    bool *getSeat()const{ return (bool*)seat; }

    void initSeat();//**********************

    void setNO(QString n);
    void settype(QString t);
    void setBeginStation(QString bs);
    void setEndStation(QString es);
    void setBeginTime(QDateTime bt);
    void setEndTime(QDateTime et);
    void setValue(double v);
    void setRestNum(int r);

    void changeSeat(int seat_num);//ticket of this seat is selled

    void storeInfo();//store in database
//	void show()const;//����
};

#endif
