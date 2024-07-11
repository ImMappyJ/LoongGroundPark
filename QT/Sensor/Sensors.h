#ifndef SENSORS_H
#define SENSORS_H
#include <vector>
#include "SensorStatus.h"

class Sensors{
private:
    QList<Sensor*> sensor_list;
    bool is_in_the_list(int id);
public:
    Sensor* find_sensor(int id);
    int add_sensor(int id,bool isParkSpace);
    int set_sensor_nearby(int i,int t,int l,int r,int b);
};

#endif // SENSORS_H
