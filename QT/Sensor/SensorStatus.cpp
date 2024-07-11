#include "SensorStatus.h"
#include "../MacroDefine.h"

int Sensor::change_status(){
    this->isTriggered = !this->isTriggered;
    return STATUS_OK;
}

Sensor::Sensor(int id, bool isParkingSpace)
{
    this->id = id;
    this->isParkingSpace = isParkingSpace;
}

int Sensor::get_status(){
    return this->isTriggered;
}

bool Sensor::is_park_space(){
    return this->isParkingSpace;
}

QList<Sensor*> Sensor::get_nearby_sensor(){
    QList<Sensor*> s;
    if(this->top != NULL) s.push_back(this->top);
    if(this->left != NULL) s.push_back(this->left);
    if(this->right != NULL) s.push_back(this->right);
    if(this->bottom != NULL) s.push_back(this->bottom);
    return s;
}

int Sensor::set_nearby(Sensor* t,Sensor* l,Sensor* r,Sensor* b){
    this->top = t;
    this->left = l;
    this->right = r;
    this->bottom = b;
    return STATUS_OK;
}

int Sensor::getid()
{
    return this->id;
}
