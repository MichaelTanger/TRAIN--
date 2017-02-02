#ifndef INFO_DATABASE_H
#define INFO_DATABASE_H
#include"User.h"
#include"Time.h"
#include"Train.h"
#include"Ticket.h"
#include"connection.h"
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include<QDateTime>
#include<QString>
#include<QSqlRecord>
void writePassenger(Passenger &passer);//将数据存入数据库，如果有重复则删除原有，再写入

void writeAdmin(Administrator &admin1);

void writeTrain(Train &mytrain);

void writeTicket(Ticket &tic);

Passenger readPassenger(QString username);

Administrator readAdmin(QString username);

Train readTrain(QString NO,QString begintime);

Ticket readTicket(QString username,QString NO);
Ticket readTicket(QString username, QString NO,QString begintime);


void delete_train(QString No,QString begintime);

#endif // INFO_DATABASE_H
