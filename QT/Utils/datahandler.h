#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#define DB_BASE_CARS "db_cars"
#define DB_BASE_SENSORS "db_sensors"
#define DB_BASENAME "data.db"
#include "MacroDefine.h"
#include <string>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QList>

class SQLDB{
public:
    static QSqlDatabase db;
    static int initdb();
};

class DataCar:SQLDB{
private:
    QString sign;
    QString wxid;
    long int bindTime;
public:
    DataCar(QString sign,QString wxid);
    static int initdb();
    static int add(DataCar& car);
    static int del(QString sign);
    static DataCar query_bysign(QString sign);
    static DataCar query_bywxid(QString wxid);
};

class DataSensor:SQLDB{
private:
    int id;
    int top;
    int left;
    int right;
    int bottom;
    bool isParkSpace;
public:
    DataSensor(int id,int top,int left,int right,int bottom,bool isParkSpace);
    static int initdb();
    static int add(DataSensor& sensor);
    static int clear();
    static QList<DataSensor*> getAll();
    static DataSensor query(int id);
    int getId() const;
    int getTop() const;
    int getLeft() const;
    int getRight() const;
    int getBottom() const;
    bool getIsParkSpace() const;
};

#endif // DATAHANDLER_H
