#include "Cars.h"
#include "../MacroDefine.h"

int Cars::car_in(Car* car){

    this->car_list.push_back(car);
    return STATUS_OK;
}

Car* Cars::findCar(QString sign){
    for(Car* c:this->car_list){
        if(c->getSign().compare(sign)){
            return c;
        }
    }
    return NULL;
}

int Cars::car_out(Car* car){
    for(Car* c:this->car_list){
        if(c->getSign().compare(car->getSign())){
            this->car_list.removeOne(c);
            return STATUS_OK;
        }
    }
    return STATUS_ERROR;
}

