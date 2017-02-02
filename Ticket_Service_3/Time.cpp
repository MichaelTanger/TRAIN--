#include<iostream>
#include"Time.h"
using namespace std;

Time::Time(){}

Time::Time(int y, int mon, int d, int h, int min)
{
    year = y;
    month = mon;
    day = d;
	hour = h;
    minter = min;
}
Time::Time(const Time &t0)
{
    year=t0.year;
    month=t0.month;
    day=t0.day;
    hour=t0.hour;
    minter=t0.minter;
}

void Time::setTime(int y, int mon, int d, int h, int min)
{
    year = y;
    month = mon;
    day = d;
	hour = h;
    minter = min;
}
