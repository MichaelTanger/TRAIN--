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

//�����ݿ��в��ҡ������ڴ����
//�������ݿ�function��
