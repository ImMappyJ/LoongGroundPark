#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#define DB_BASE_CARS "db_cars"
#define DB_BASE_SENSORS "db_sensors"
#include <string>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>



class DataCar{
private:
    std::string sign;
    std::string wxid;
    long int bindTime;
public:
    static QSqlDatabase db;
    DataCar(std::string sign,std::string wxid);
    static int add(DataCar car);
    static int del(std::string sign);
    static DataCar query_bysign(std::string sign);
    static DataCar query_bywxid(std::string wxid);
};

class DataSensor{
private:
    int id;
    int top;
    int left;
    int right;
    int bottom;
public:
    DataSensor(int id,int top,int left,int right,int bottom);
    static int add(DataSensor sensor);
    static int clear();
    static DataSensor query(int id);
};

#endif // DATAHANDLER_H
