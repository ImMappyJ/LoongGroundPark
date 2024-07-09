#ifndef SENSORS_H
#define SENSORS_H
#include <vector>
#include "SensorStatus.h"

class Sensors{
private:
    std::vector<Sensor*> sensor_list;
    int set_sensor_nearby(int i,int t,int l,int r,int b);
    bool is_in_the_list(int id);
public:
    Sensor* find_sensor(int id);
    int add_sensor(int id,bool isParkSpace);
    int init_sensor_position(int* id,int* top,int* left,int* right,int* bottom);
};

#endif // SENSORS_H
