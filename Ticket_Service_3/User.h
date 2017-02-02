#ifndef USER_H
#define USER_H

#include"Train.h"
#include<QString>
using namespace std;

enum SEX{male , female };
enum special{ adult,child,student,disabled_army};

class User
{
    //普通用户账户信息至少包括：账号（用户名）、姓名、性别、身份证号（或者其他有效证件及证件号码）、联系方式
private:
    QString username;
    QString name;
	SEX sex;
    QString password;

public:
    User(){}
    User(QString u,QString n,SEX s,QString p);
	//更改信息
    void setUsername(QString u);
    void setName(QString n);
    void setSex(SEX s);
    void setPassword(QString now);//输入正确的以前的密码same=1，才能更改密码

	//读取信息
    QString getUsername()const{ return  username; }
    QString getName()const{ return  name; }
	SEX getSex()const{ return  sex; }
    QString getPassword()const{ return password; }
/*
    void getInfo();//get infomation from database
    void storeInfo();//store infomation in database
    void showInfo();//show infomation ui
    void changeInfo();//get infomation from ui
	//由数据库中查找、存入内存对象。
    //存入数据库function。
*/
};

class Passenger:public User
{
private:
    QString id;
    QString tele;
//    Ticket ticket;
    special type;//用户其他信息（学生证等其他信息，可为空）
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
