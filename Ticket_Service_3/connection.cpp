#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include<Qdatetime>
#include"connection.h"
//连接到数据库
bool createDatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    if(!db.open())
    {
        return false;
    }
    else
    {
        QSqlQuery query;

        query.exec("create table if not exists passenger(username varchar primary key,name varchar,"
                   "sex varchar,id varchar,tele varchar,password varchar )");
             query.exec("create table if not exists train(id INTEGER PRIMARY KEY AUTOINCREMENT,NO varchar,type varchar,begintime varchar,"
                       "endtime varchar,beginstation varchar,endstation varchar,value decimal,restnum int,begindate varchar)");
             query.exec("create table if not exists ticket(id INTEGER PRIMARY KEY AUTOINCREMENT,username varchar,No varchar,name varchar,"
                       "num int,begintime varchar,endtime varchar,beginstation varchar,endstation varchar,value decimal,type varchar)");
             query.exec("create table if not exists admin(name varchar primary key,password varchar)");
             query.exec("insert into admin values('admin1','admin1')");
        return true;
    }
}
