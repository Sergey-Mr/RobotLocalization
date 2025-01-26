#include "Robot.h"
#include <iostream>

Robot::Robot(int x, int y, Map& map): x(x), y(y), map(map){
    map.addRobot(x, y);
}

void Robot::updatePosition(int newX, int newY){
    if (this->map.updateRobotPosition(this->x, this->y, newX, newY)){  
        this->x = newX;
        this->y = newY;
    }

    // else rise an error
}

void Robot::moveUp(){
    if (this->map.isValidMove(x, y - 1)){
        int newY = y-1;
        this->updatePosition(x, newY);
    }
}

void Robot::moveDown(){
    if (map.isValidMove(x, y + 1)){
        int newY = y + 1;
        this->updatePosition(x, newY);
    }
}

void Robot::moveLeft(){
    if (map.isValidMove(x - 1, y)){
        int newX = x - 1;
        this-> updatePosition(newX, y);
    }
}

void Robot::moveRight(){
    if (map.isValidMove(x+1, y)){
        int newX = x + 1;
        this-> updatePosition(newX, y);
    }
}

