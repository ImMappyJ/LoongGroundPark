#include "CarStatus.h"
#include "../MacroDefine.h"
#include "../Utils/timegenerator.h"
#include <string>

int Car::moveTo(int id){
    this->position_sensor = id;
    return STATUS_OK;
}

Car::Car(QString sign, int target_position)
{
    this->sign = sign;
    this->target_position = target_position;
    this->timetamp = get_now_time();
}

bool Car::isStopped(){
    if(this->target_position == this->position_sensor) return STATUS_OK;
    else return STATUS_ERROR;
}

int Car::bindWx(){
    this->binded_wx = "testWxid";
    if(this->binded_wx == ""){
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

QString Car::getSign(){
    return this->sign;
}
