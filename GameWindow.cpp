#include "GameWindow.h"


GameWindow::GameWindow() : AnimationWindow{20, 20, 1000, 1000, "Buper Cars"}
{
    //initialiserer vektorer:
    cars.emplace_back();
    cars.emplace_back();
}

void GameWindow::run(){
    while(!should_close()){ // spilløkke
        drawBall();
        for(auto& car : cars){
            car.slide();
            drawCars(car);
            bounce(car); 
            checkBoundsAndReflect(car);           
        }

        ball.slide();
        checkBoundsAndReflect(ball);
        
        
        handleInput(); // håndtere input fra tastatur
        next_frame();
    }
}

void GameWindow::handleInput(){
    static bool lastUpKeyState = false;
    static bool lastRightKeyState = false;
    static bool lastLeftKeyState = false;
    static bool lastDownKeyState = false;

    bool currentUpKeyState = is_key_down(KeyboardKey::UP);
    bool currentRightKeyState = is_key_down(KeyboardKey::RIGHT);
    bool currentLeftKeyState = is_key_down(KeyboardKey::LEFT);
    bool currentDownKeyState = is_key_down(KeyboardKey::DOWN);
    
    
    if(currentUpKeyState && !lastUpKeyState) {
        cars.at(0).accelerate();
    }   

    if(currentRightKeyState && !lastRightKeyState) { 
        cars.at(0).rotateRight();
    }  

    if(currentLeftKeyState && !lastLeftKeyState) {
        cars.at(0).rotateLeft();
    }
    if(currentDownKeyState && !lastDownKeyState) {
        cars.at(0).reverse();
    }

    //-----------------------------------
    // Player 2
    static bool lastWKeyState = false;
    static bool lastDKeyState = false;
    static bool lastAKeyState = false;

    bool currentWKeyState = is_key_down(KeyboardKey::W);
    bool currentDKeyState = is_key_down(KeyboardKey::D);
    bool currentAKeyState = is_key_down(KeyboardKey::A);

    if(currentWKeyState && !lastWKeyState) {
        cars.at(1).accelerate();
    }   

    if(currentDKeyState && !lastDKeyState) {
        cars.at(1).rotateRight();
    }  

    if(currentAKeyState && !lastAKeyState) {
        cars.at(1).rotateLeft();
    }
}


void GameWindow::drawCars(Car& car){
    FloatPoint velocity = car.getVelocity();
    FloatPoint position = car.getPosition();
    int size = car.getSize();

    // Midlertidig! Byttes ut med bilde som roterer, evt animasjon.
    double direction = car.getAngle();
    FloatPoint p1 = {
    car.getPosition().x + size * cos(direction),
    position.y + car.getSize() * sin(direction)
    };
    FloatPoint p2 = {
    position.x + size/2.0 * cos(direction + 2.0/3.0 * M_PI),
    position.y + size/2.0 * sin(direction + 2.0/3.0 * M_PI)
    };
    FloatPoint p3 = {
    position.x + size/2.0 * cos(direction - 2.0/3.0 * M_PI),
    position.y + size/2.0 * sin(direction - 2.0/3.0 * M_PI)
    };
    draw_triangle(
    {static_cast<int> (p1.x), static_cast<int> (p1.y)},
    {static_cast<int> (p2.x), static_cast<int> (p2.y)},
    {static_cast<int> (p3.x), static_cast<int> (p3.y)}, TDT4102::Color::black
    );
}


bool GameWindow::checkCollision(Car& car, Ball& ball){
    // Finn avstanden mellom sentrene av bilen og ballen
    double dx = car.getPosition().x - ball.position.x;
    double dy = car.getPosition().y - ball.position.y;
    double distance = sqrt(dx * dx + dy * dy);

    // Sammenlign avstanden med summen av radiene
    double sumOfRadii = car.getSize() + ball.size;

    // Returner true hvis de kolliderer, ellers false
    return distance <= sumOfRadii;
}

void GameWindow::bounce(Car& car){
    if(checkCollision(car, ball)){
        FloatPoint direction = {ball.position.x - car.getPosition().x, ball.position.y - car.getPosition().y};
        ball.pushImpulse(direction, car.getVelocity().size()*3);
    }
}

void GameWindow::drawBall(){
    draw_circle({static_cast<int>(ball.position.x), static_cast<int>(ball.position.y)}, ball.size);
}

void GameWindow::checkBoundsAndReflect(Car& car){
    FloatPoint position = car.getPosition();
    FloatPoint velocity = car.getVelocity();

    if(position.x > Win_W || position.x < 0){
        velocity.x = -velocity.x; // Bytt fortegnet til x-komponenten av hastigheten
        car.setVelocity(velocity);
    }
    
    if(position.y > Win_H || position.y < 0){
        velocity.y = -velocity.y; // Bytt fortegnet til y-komponenten av hastigheten
        car.setVelocity(velocity);
    }
}

void GameWindow::checkBoundsAndReflect(Ball& ball){
    FloatPoint position = ball.position;
    FloatPoint direction = ball.direction;
    FloatPoint velocity = ball.velocity;
    double radius = ball.size;

    if(position.x + radius > Win_W){
        direction.x = -abs(direction.x); // setter retning mot banen
        ball.direction = direction;
        ball.pushImpulse(direction, 2.0); // dytter inn i map
    }
    if(position.x < radius){
        direction.x = abs(direction.x);
        ball.direction = direction;
        ball.pushImpulse(direction, 2.0);
    }
    
    if(position.y + radius > Win_H){
        direction.y = -abs(direction.y); // Bytt fortegnet til y-komponenten av retningen
        ball.direction = direction;
        ball.pushImpulse(direction, 2.0); // dytter inn i map
    }
    if(position.y < radius){
        direction.y = abs(direction.y); // Bytt fortegnet til y-komponenten av retningen
        ball.direction = direction;
        ball.pushImpulse(direction, 2.0); // dytter inn i map
    }
}
