#include "Cars.h"
#include "../MacroDefine.h"

int Cars::car_in(Car* car){

    this->car_list.push_back(car);
    return STATUS_OK;
}

Car* Cars::findCar(std::string sign){
    for(auto i = this->car_list.begin();i != this->car_list.end();i++){
        if((*i)->getSign().compare(sign)){
            return (*i);
        }
    }
    return NULL;
}

int Cars::car_out(Car* car){
    for(auto i = this->car_list.cbegin();i != this->car_list.cend();i++){
        if((*i)->getSign().compare(car->getSign())){
            this->car_list.erase(i);
            return STATUS_OK;
        }
    }
    return STATUS_ERROR;
}

