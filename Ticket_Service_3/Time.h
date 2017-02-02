#ifndef TIME_H
#define TIME_H

class Time   //:public Data//考虑如何把时间类与查询机制“年月日”合理协调
{
private:
    int year;
    int month;
    int day;
	int hour;
	int minter;
public:
	Time();
    Time(int y, int mon, int d,int h, int min);
    Time(const Time &t0);

    void setTime(int y, int mon, int d, int h, int min);
    int getyear()const{ return year; }
    int getmonth()const{ return month; }
    int getday()const{ return day; }
	int gethour()const{ return hour; }
	int getminter()const{ return minter; }
};
#endif
