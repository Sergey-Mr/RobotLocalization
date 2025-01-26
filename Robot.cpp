#include "Robot.h"
#include <iostream>

Robot::Robot(int x, int y, Map& map, double sensorNoiseLevel): x(x), y(y), map(map), sensor(sensorNoiseLevel){
    map.addRobot(x, y);
    initializeProbabilityDistribution();
}

void Robot::initializeProbabilityDistribution() {
    int width = map.getGrid()[0].size();
    int height = map.getGrid().size();
    double initialProbability = 1.0 / (width * height);
    probabilityDistribution.resize(height, std::vector<double>(width, initialProbability));
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

void Robot::displayPosition() const {
    std::cout << "Robot position: (" << this->x << ", " << this->y << ")" << std::endl;
}

std::vector<int> Robot::getSensorReading() const{
    return this->sensor.getReading(x, y, map);
}

void Robot::displayProbabilityDistribution() const {
    std::cout << "Probability Distribution:" << std::endl;
    for (const auto& row : probabilityDistribution) {
        for (double prob : row) {
            std::cout << prob << " ";
        }
        std::cout << std::endl;
    }
}