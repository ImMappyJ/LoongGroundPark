#include "datahandler.h"

QSqlDatabase SQLDB::db = QSqlDatabase::addDatabase("QSQLITE");

DataCar::DataCar(QString sign, QString wxid) {
    this->sign = sign;
    this->wxid = wxid;
}

int DataCar::initdb()
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE IF NOT EXISTS ").append(DB_BASE_CARS).append(" (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)"));
    if (!query.exec()) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return STATUS_ERROR;
    }
}

int DataCar::add(DataCar& car)
{
}

int DataSensor::getId() const
{
    return id;
}

int DataSensor::getTop() const
{
    return top;
}

int DataSensor::getLeft() const
{
    return left;
}

int DataSensor::getRight() const
{
    return right;
}

int DataSensor::getBottom() const
{
    return bottom;
}

bool DataSensor::getIsParkSpace() const
{
    return isParkSpace;
}

DataSensor::DataSensor(int id, int top, int left, int right, int bottom, bool isParkSpace) {
    this->id = id;
    this->top = top;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->isParkSpace = isParkSpace;
}

int DataSensor::initdb()
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE IF NOT EXISTS ").append(DB_BASE_SENSORS).append("(id INTEGER PRIMARY KEY, top INTEGER, left INTEGER, right INTEGER,bottom INTEGER,isParkSpace INTEGER)"));
    if (!query.exec()) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

int DataSensor::add(DataSensor &sensor)
{
    if(!db.open()){
        qDebug() << "SQL NOT OPEN";
        return STATUS_ERROR;
    }
    QSqlQuery query(db);
    query.prepare(QString("INSERT INTO ").append(DB_BASE_SENSORS).append("(id, top, left, right, bottom, isParkSpace) VALUES (?, ?, ?, ?, ?, ?)"));
    query.addBindValue(sensor.id);
    query.addBindValue(sensor.top);
    query.addBindValue(sensor.left);
    query.addBindValue(sensor.right);
    query.addBindValue(sensor.bottom);
    query.addBindValue(sensor.isParkSpace);
    if (!query.exec()) {
        qDebug() << "Error adding sensor:" << query.lastError().text();
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

int DataSensor::clear()
{
    QSqlQuery query(db);
    query.prepare(QString("DELETE FROM ").append(DB_BASE_SENSORS));
    if(!query.exec()){
        qDebug() << "Error deleting table info:" << query.lastError().text();
        db.close();
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

QList<DataSensor*> DataSensor::getAll()
{
    QList<DataSensor*> qlist;
    QSqlQuery query(db);
    query.prepare(QString("SELECT * FROM ").append(DB_BASE_SENSORS));
    if (!query.exec()) {
        qDebug() << "Error querying table info:" << query.lastError().text();
        db.close();
        return qlist;
    }
    qDebug() << "Reading all the sensors in sql...";
    while (query.next()) {
        int currentID = query.value(0).toInt();
        int top = query.value(1).toInt();
        int left = query.value(2).toInt();
        int right = query.value(3).toInt();
        int bottom = query.value(4).toInt();
        bool parkSpace = query.value(5).toBool();
        DataSensor* data = new DataSensor(currentID,top,left,right,bottom,parkSpace);
        qlist.push_back(data);
    }
    qDebug() << "Reading compeletely";
    return qlist;
}

int SQLDB::initdb()
{
    db.setDatabaseName(DB_BASENAME);
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return STATUS_ERROR;
    }
    return STATUS_OK;
}
