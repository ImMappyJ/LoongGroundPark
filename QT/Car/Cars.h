#ifndef CARS_H
#define CARS_H
#include "CarStatus.h"
#include <vector>
#include <string>

class Cars{
private:
    std::vector<Car*> car_list; //汽车列表
public:
    int car_in(Car* car);
    int car_out(Car* car);
    Car* findCar(std::string sign);
};

#endif // CARS_H
