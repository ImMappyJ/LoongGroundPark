#include "datahandler.h"

QSqlDatabase DataCar::db = QSqlDatabase::addDatabase("QSQLITE", "DataCarConnection");
QSqlDatabase DataSensor::db = QSqlDatabase::addDatabase("QSQLITE", "DataSensorConnection");

DataCar::DataCar(std::string sign, std::string wxid) {
    this->sign = sign;
    this->wxid = wxid;
    db.setDatabaseName(DB_BASE_CARS);
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
    }
}

DataSensor::DataSensor(int id, int top, int left, int right, int bottom, bool isParkSpace) {
    this->id = id;
    this->top = top;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->isParkSpace = isParkSpace;
    db.setDatabaseName(DB_BASE_SENSORS);
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
    }
}

int DataCar::add(DataCar car) {
}

int DataSensor::add(DataSensor sensor) {
}

// 其他静态方法的实现
