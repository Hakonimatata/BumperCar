#pragma once
#include "AnimationWindow.h"
#include "Entities.h"


class GameWindow : public TDT4102::AnimationWindow{

int Win_W = 1000;
int Win_H = 1000;

vector<Car> cars;
Ball ball;


public:
    GameWindow();
    void run();
    void handleInput();
    void drawCars(Car& car);
    void drawBall();
    bool checkCollision(Car& car, Ball& ball);
    void bounce(Car& car);

    void checkBoundsAndReflect(Car& car);
    void checkBoundsAndReflect(Ball& ball);
};