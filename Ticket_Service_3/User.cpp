#include"User.h"
#include<iostream>
using namespace std;

User::User(QString u,QString n,SEX s,QString p)
{
    username=u;
    name=n;
    sex=s;
    password=p;
}
void User::setUsername(QString u){ username = u; }
void User::setName(QString n){ name = n; }
void User::setSex(SEX s){ sex = s; }
void User::setPassword(QString now)//输入正确的以前的密码same=1，才能更改密码
{

    password = now;

}



Passenger::Passenger(QString u, QString n, SEX s, QString p, QString i, QString t, special type)
    :User(u,n,s,p)
{
    id=i;
    tele=t;
    this->type=type;
}
Passenger::Passenger(Passenger &p0):User(p0.getUsername(),p0.getName(),p0.getSex(),p0.getPassword())
{
    id=p0.id;
    tele=p0.tele;
    type=p0.type;
}
void Passenger::setId(QString i){id=i;}
void Passenger::setTele(QString t){tele=t;}
void Passenger::setType(special type){this->type = type;}

/*
Ticket Passenger::bookTicket(Train &train)//***************************************************
{
    if(train.getRestNum()!=0)
    {
        if(train.gettype()==1||train.gettype()==3)//lay ticket
        {
            for(int i=0;i<60;i++)
            {
                if(train.getSeat()[i]==0)
                {
                    Ticket t(this->getUsername(),train,i);
                    train.setRestNum(train.getRestNum()-1);
                    train.changeSeat(i);
                }
            }
        }
        else
        {
            for(int i=0;i<120;i++)
            {
                if(train.getSeat()[i]==0)
                {
                    Ticket t(this->getUsername(),train,i);
                    train.setRestNum(train.getRestNum()-1);
                    train.changeSeat(i);
                }
            }
        }
        return t;
    }
    else
    {
        //window show error!**********************************************************************
    }
}
//    void withdrewTicket();
*/



Administrator::Administrator(QString u,QString n,SEX s,QString p):User(u,n,s,p){}

Administrator::Administrator(Administrator &ad):User(ad.getUsername(),ad.getName(),ad.getSex(),ad.getPassword()){}
void Administrator::addTrain(Train &newtrain)//***************************************************
{

}

void Administrator::deleteTrain(Train &detrain)//***************************************************
{

}

void Administrator::changeTrain(Train &chtrain)//***************************************************
{

}

