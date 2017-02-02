#include"Ticket.h"
#include<iostream>
using namespace std;

Ticket::Ticket(Passenger &passenger, Train &train, int num) :passenger(passenger),train(train)
{
	this->num = num;
}
Ticket::Ticket(Ticket &t0):passenger(t0.passenger),train(t0.train)
{
    num=t0.num;
}

//由数据库中查找、存入内存对象。
//存入数据库function。
