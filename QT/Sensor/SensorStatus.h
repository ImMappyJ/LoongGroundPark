#ifndef SENSORSTATUS_H
#define SENSORSTATUS_H
#include <QString>
#include <QList>
#include <QObject>

class Sensor{
private:
    int id;
    bool isTriggered = false;
    bool isParkingSpace;
    Sensor* top = NULL;
    Sensor* bottom = NULL;
    Sensor* left = NULL;
    Sensor* right = NULL;
public:
    Sensor(int id,bool isParkingSpace);
    int get_status();
    int change_status();
    bool is_park_space();
    QList<Sensor*> get_nearby_sensor();
    int set_nearby(Sensor* t,Sensor* l,Sensor* r,Sensor* b);
    int getid();
};

#endif // SENSORSTATUS_H
