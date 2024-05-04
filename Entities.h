#pragma once
#include "std_lib_facilities.h"
#include "Point.h"

struct FloatPoint{
    double x;
    double y;
    void normalize();
    double size();
};


class Car {

int size = 50;
double topSpeed = 40.0;
FloatPoint velocity = {0, 0};
double rotationSpeed = 0.1;
double friction = 0.1;
double angle = 0;
FloatPoint position = {200, 200};

public:
    void accelerate();
    void reverse();
    void slide();
    void rotateRight();
    void rotateLeft();

    //get- setfunksjoner
    FloatPoint getPosition() const{return position;}
    int getSize(){return size;}
    FloatPoint getVelocity(){return velocity;}
    double getAngle(){return angle;}
    void setVelocity(FloatPoint p){velocity = p;}
};

class Ball {
public:
    FloatPoint position = {400, 400};
    FloatPoint direction;
    FloatPoint velocity = {0, 0};
    double maxSpeed = 20.0;
    
    // double velocity = 0;
    double friction = 0.05;
    int size = 10;

    void pushImpulse(FloatPoint dir, double vel);
    void slide();
};