#ifndef CARSTATUS_H
#define CARSTATUS_H
#include <string>

class Car{
private:
    std::string sign;   //车牌号
    long int timetamp;  //车辆进入时间戳
    int position_sensor = -1;    //所在位置触发器ID
    int target_position = -1;    //目标停车位ID
    std::string binded_wx = "";  //绑定微信账号
public:
    Car(std::string sign,int target_position);
    bool isStopped();
    int moveTo(int id);
    int bindWx();
    std::string getSign();
};

#endif // CARSTATUS_H
