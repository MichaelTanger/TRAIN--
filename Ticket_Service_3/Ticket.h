#ifndef TICKET_H
#define TICKET_H

#include"Train.h"
#include"User.h"
class Ticket
{
private:
	Train train;
    int num;//座位号,暂且考虑把卧铺的上中下,is from 1 to 60 ; num/3+1=num, num%3=position;
    Passenger passenger;

public:
    Ticket(){}
    Ticket(Passenger &passenger, Train &train, int num);
    Ticket(Ticket &t0);
    void settrain(Train &train){this->train=train;}
    void setnum(int num){this->num=num;}
    void setpassenger(Passenger &passenger){this->passenger=passenger;}
    Train gettrain(){return train;}
    int getnum(){return num;}
    Passenger getpassenger(){return passenger;}
	void show();//界面化展示信息
	//由数据库中查找、存入内存对象。
	//存入数据库function。
};
#endif
