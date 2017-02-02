#ifndef USER_H
#define USER_H

#include"Train.h"
#include<QString>
using namespace std;

enum SEX{male , female };
enum special{ adult,child,student,disabled_army};

class User
{
    //��ͨ�û��˻���Ϣ���ٰ������˺ţ��û��������������Ա����֤�ţ�����������Ч֤����֤�����룩����ϵ��ʽ
private:
    QString username;
    QString name;
	SEX sex;
    QString password;

public:
    User(){}
    User(QString u,QString n,SEX s,QString p);
	//������Ϣ
    void setUsername(QString u);
    void setName(QString n);
    void setSex(SEX s);
    void setPassword(QString now);//������ȷ����ǰ������same=1�����ܸ�������

	//��ȡ��Ϣ
    QString getUsername()const{ return  username; }
    QString getName()const{ return  name; }
	SEX getSex()const{ return  sex; }
    QString getPassword()const{ return password; }
/*
    void getInfo();//get infomation from database
    void storeInfo();//store infomation in database
    void showInfo();//show infomation ui
    void changeInfo();//get infomation from ui
	//�����ݿ��в��ҡ������ڴ����
    //�������ݿ�function��
*/
};

class Passenger:public User
{
private:
    QString id;
    QString tele;
//    Ticket ticket;
    special type;//�û�������Ϣ��ѧ��֤��������Ϣ����Ϊ�գ�
public:
    Passenger(){}
    Passenger(QString u, QString n, SEX s, QString p, QString i, QString t, special type = adult);
    Passenger(Passenger &p0);
    void setId(QString i);
    void setTele(QString t);
    void setType(special type);
//    Ticket bookTicket(Train &train);//seat_num
//    void withdrewTicket();
    QString getId()const{ return id; }
    QString getTele()const{ return tele; }
//    Ticket getTicket(){return ticket;}
    special getType()const{ return type; }

};

class Administrator:public User//what power administrator has?
{
public:
    Administrator(){}
    Administrator(QString u,QString n,SEX s,QString p);
    Administrator(Administrator &ad);
    void addTrain(Train &newtrain);
    void deleteTrain(Train &detrain);
    void changeTrain(Train &chtrain);
};

#endif // USER_H
