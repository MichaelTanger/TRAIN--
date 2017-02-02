#include"info_database.h"
#include<QDateTime>
#include<QString>
#include<QDate>
#include<QDebug>
void writePassenger(Passenger &passer){//将数据存入数据库，如果有重复则删除原有，再写入
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("delete from passenger where username==:username");
    query.bindValue(":username",passer.getUsername());
    query.exec();
    query.prepare("insert into passenger(username,name,sex,id,tele,password) "
                    "values(:username, :name,:sex,:id,:tele,:password)") ;
    query.bindValue(":username",passer.getUsername());
    query.bindValue(":name",passer.getName());
    query.bindValue(":sex",passer.getSex());
    query.bindValue(":id",passer.getId());
    query.bindValue(":tele",passer.getTele());
    query.bindValue(":password",passer.getPassword());
    query.exec();
}
//------------------------------
void writeAdmin(Administrator &admin1){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("delete from admin where username==:username");
    query.bindValue(":username",admin1.getUsername());
    query.exec();
    query.prepare("insert into admin(name,password) "
                    "values(:name,:password)") ;
    query.bindValue(":name",admin1.getUsername());
    query.bindValue(":password",admin1.getPassword());
    query.exec();
}
//-------------------------------
void writeTrain(Train &mytrain){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("delete from train where NO==:NO and begintime==:begintime");
    query.bindValue(":NO",mytrain.getNO());
    query.bindValue(":begintime",mytrain.getBeginTime().toString(Qt::TextDate));
    query.exec();
    query.prepare("insert into train(NO,type,begintime,endtime,beginstation,endstation,value,restnum,begindate) "
                    "values(:NO,:type,:begintime,:endtime,:beginstation,:endstation,:value,:restnum,:begindate)") ;
    query.bindValue(":NO",mytrain.getNO());
    query.bindValue(":type",mytrain.gettype());
    query.bindValue(":begintime",mytrain.getBeginTime().toString());
    query.bindValue(":endtime",mytrain.getEndTime().toString());
    query.bindValue(":value",mytrain.getValue());
    query.bindValue(":beginstation",mytrain.getBeginStation());
    query.bindValue(":endstation",mytrain.getEndStation());
    query.bindValue(":restnum",mytrain.getRestNum());
    QDate begindate= mytrain.getBeginTime().date();//
    query.bindValue(":begindate",begindate.toString());//
    query.exec();
}
//----------------------------
void writeTicket(Ticket &tic){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("insert into ticket(No,username,name,num,begintime,endtime,beginstation,endstation,value,type)"
              "values(:No,:username,:name,:num,:begintime,:endtime,:beginstation,:endstation,:value,:type)");
    query.bindValue(":No",tic.gettrain().getNO());
    query.bindValue(":username",tic.getpassenger().getUsername());
    query.bindValue(":name",tic.getpassenger().getName());
    query.bindValue(":num",tic.getnum());
    query.bindValue(":begintime",tic.gettrain().getBeginTime().toString(Qt::TextDate));
    query.bindValue(":endtime",tic.gettrain().getEndTime().toString(Qt::TextDate));
    query.bindValue(":beginstation",tic.gettrain().getBeginStation());
    qDebug()<<tic.gettrain().getBeginStation();
    query.bindValue(":endstation",tic.gettrain().getEndStation());
    query.bindValue(":value",tic.gettrain().getValue());
    query.bindValue(":type",tic.gettrain().gettype());
    //query.bindValue(":No",tic.gettrain().getNO());
    qDebug()<<tic.gettrain().getNO();
    query.exec();
}
//-------------------
Passenger readPassenger(QString username){//根据username查询数据库中的数据并用于初始化一个对象，并返回该对象
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select * from passenger where username==:username");
    query.bindValue(":username",username);
    query.exec();
    query.next();
    Passenger p;
    p.setUsername(username);
    p.setName(query.value("name").toString());
    p.setPassword(query.value("password").toString());
    int sex=query.value("sex").toInt();
    p.setSex((SEX)sex);
   // p.setType(query.value("type").toString());
    p.setId(query.value("id").toString());
    p.setTele(query.value("tele").toString());
  return p;
}
//---------------------------------------
Administrator readAdmin(QString username){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select * from admin where username==:username");
    query.bindValue(":username",username);
    query.exec();
    query.next();
    Administrator admin;
    admin.setUsername(query.value("username").toString());
    admin.setPassword(query.value("password").toString());
    return admin;
}
//----------------------------------
Train readTrain(QString NO,QString begintime){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select * from train where NO==:NO and begintime==:begintime");
    query.bindValue(":NO",NO);
    query.bindValue(":begintime",begintime);
    query.exec();
  query.next();
    Train tr;
    tr.setNO(NO);
    tr.settype(query.value("type").toString());
    tr.setBeginStation(query.value("beginstation").toString());
    tr.setEndStation(query.value("endstation").toString());
    tr.setBeginTime(QDateTime::fromString( query.value("begintime").toString()));
    tr.setEndTime(QDateTime::fromString( query.value("endtime").toString()));
    tr.setValue(query.value("value").toDouble());
    tr.setRestNum(query.value("restnum").toInt());
    return tr;
}
//-------------------------------
Ticket readTicket(QString username,QString NO){
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select * from ticket where NO==:NO AND username==:username");
    query.bindValue(":NO",NO);
    query.bindValue(":username",username);
    query.exec();
    query.next();
    Passenger p;
    p.setUsername(username);
    p.setName(query.value("name").toString());
    Train tr;
    tr.setNO(NO);
    tr.settype(query.value("type").toString());
    tr.setBeginStation(query.value("beginstation").toString());
    tr.setEndStation(query.value("endstation").toString());
    tr.setBeginTime(QDateTime::fromString( query.value("begintime").toString()));
    tr.setEndTime(QDateTime::fromString( query.value("endtime").toString()));
    tr.setValue(query.value("value").toDouble());
    Ticket tic;
    tic.setnum(query.value("num").toInt());
    tic.setpassenger(p);
    tic.settrain(tr);
    return tic;
}
//------------------------
void delete_train(QString No,QString begintime){

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("delete from train where NO==:NO and begintime==:begintime");
    query.bindValue(":NO",No);
    query.bindValue(":begintime",begintime);
    query.exec();
}
//-----------------------------
Ticket readTicket(QString username, QString NO,QString begintime)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Service.db");
    db.open();
    QSqlQuery query;
    query.prepare("select * from ticket where NO==:NO AND username==:username AND begintime==:begintime");
    query.bindValue(":NO",NO);
    query.bindValue(":username",username);
    query.bindValue(":begintime",begintime);
    query.exec();
    query.next();
    Passenger p;
    p.setUsername(username);
    p.setName(query.value("name").toString());
    Train tr;
    tr.setNO(NO);
    tr.settype(query.value("type").toString());
    tr.setBeginStation(query.value("beginstation").toString());
    tr.setEndStation(query.value("endstation").toString());
    tr.setBeginTime(QDateTime::fromString( query.value("begintime").toString()));
    tr.setEndTime(QDateTime::fromString( query.value("endtime").toString()));
    tr.setValue(query.value("value").toDouble());
    Ticket tic;
    tic.setnum(query.value("num").toInt());
    tic.setpassenger(p);
    tic.settrain(tr);
    return tic;
}
