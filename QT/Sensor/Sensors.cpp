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
    for(Sensor* s:sensor_list){
        if(s->getid() == id) return true;
    }
    return false;
}

Sensor* Sensors::find_sensor(int id){
    for(Sensor* s:sensor_list){
        if((s)->getid() == id){
            return s;
        }
    }
    return NULL;
}

int Sensors::add_sensor(int id, bool isParkSpace)
{
    Sensor* sensor = new Sensor(id,isParkSpace);
    this->sensor_list.append(sensor);
    return STATUS_OK;
}

