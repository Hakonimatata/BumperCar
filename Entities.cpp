#include "Entities.h"

double FloatPoint::size(){
    return sqrt(pow(x,2) + pow(y,2));
}

void FloatPoint::normalize(){
    double magnitude = size();
    if (magnitude != 0) {
        x = x / magnitude;
        y = y / magnitude;
    }
}


void Car::accelerate(){

    double acceleration = 1;
    velocity.x += acceleration * cos(angle);
    velocity.y += acceleration * sin(angle);
    
    // Sjekk om akselerasjonen overskrider toppfarten
    if(velocity.size() > topSpeed) {
        // Begrens hastigheten til toppfarten hvis den overskrider
        velocity.normalize(); // Normaliserer vektoren
        velocity.x *= topSpeed;
        velocity.y *= topSpeed;
    }
}

void Car::reverse(){
    double acceleration = 0.5;
    velocity.x -= acceleration * cos(angle);
    velocity.y -= acceleration * sin(angle);
    
    // Sjekk om akselerasjonen overskrider toppfarten
    if(velocity.size() > topSpeed) {
        // Begrens hastigheten til toppfarten hvis den overskrider
        velocity.normalize(); // Normaliserer vektoren
        velocity.x *= topSpeed;
        velocity.y *= topSpeed;
    }
}

void Car::slide(){
    position.x += velocity.x;
    position.y += velocity.y;

    velocity.x -= velocity.x * friction;
    velocity.y -= velocity.y * friction;
    // if(velocity.size() < 0.01) velocity = {0,0};
}

void Car::rotateRight(){
    angle = angle + rotationSpeed;
    if(angle < 0) angle += 2*M_PI;
}
    
void Car::rotateLeft(){
    angle = angle - rotationSpeed;
    if(angle >= 2*M_PI) angle -= 2*M_PI;
}





void Ball::pushImpulse(FloatPoint dir, double vel){
    dir.normalize();
    direction = dir;
    
    // Legg til impuls
    velocity.x += dir.x * vel;
    velocity.y += dir.y * vel;

    // Begrens hastigheten til maxSpeed
    double currentSpeed = velocity.size();
    if (currentSpeed > maxSpeed) {
        velocity.x *= maxSpeed / currentSpeed;
        velocity.y *= maxSpeed / currentSpeed;
    }
}




void Ball::slide(){
    if(velocity.size() > 0.05){
        // Oppdater ballens posisjon basert på retning og hastighet
        position.x += velocity.x;
        position.y += velocity.y;
        // Reduser hastigheten basert på friksjon
        velocity.x -= velocity.x * friction;
        velocity.y -= velocity.y * friction;
    }
}