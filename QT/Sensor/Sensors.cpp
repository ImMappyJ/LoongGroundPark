#include "Sensors.h"
#include <iostream>
#include "../MacroDefine.h"

int Sensors::set_sensor_nearby(int i, int t, int l, int r, int b)
{
    Sensor* s_ptr = this->find_sensor(i);
    if(s_ptr == NULL) return STATUS_ERROR;
    s_ptr->set_nearby(this->is_in_the_list(t)?this->find_sensor(t):NULL,
                      this->is_in_the_list(l)?this->find_sensor(l):NULL,
                      this->is_in_the_list(r)?this->find_sensor(r):NULL,
                      this->is_in_the_list(b)?this->find_sensor(b):NULL);
    return STATUS_OK;
}

bool Sensors::is_in_the_list(int id)
{
    return id > 0 && id <= this->sensor_list.capacity();
}

Sensor* Sensors::find_sensor(int id){
    for(auto i = this->sensor_list.begin();i != this->sensor_list.end();i++){
        if((*i)->getid() == id){
            return *i;
        }
    }
    return NULL;
}

int Sensors::add_sensor(int id, bool isParkSpace)
{
    Sensor* sensor = new Sensor(id,isParkSpace);
    this->sensor_list.push_back(sensor);
    return STATUS_OK;
}

int Sensors::init_sensor_position(int *id, int *top, int *left, int *right, int *bottom)
{
    int temp = 0;
    while(id[temp] > 0){
        if(this->set_sensor_nearby(id[temp],top[temp],left[temp],right[temp],bottom[temp]) == STATUS_ERROR){
            return STATUS_ERROR;
        }
    }
    return STATUS_OK;
}

