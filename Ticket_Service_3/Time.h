#ifndef TIME_H
#define TIME_H

class Time   //:public Data//������ΰ�ʱ�������ѯ���ơ������ա�����Э��
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
