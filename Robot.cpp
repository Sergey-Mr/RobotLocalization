#include "Robot.h"
#include <iostream>
#include <cmath>

Robot::Robot(int x, int y, Map& map, double sensorNoiseLevel): x(x), y(y), map(map), sensor(sensorNoiseLevel){
    map.addRobot(x, y);
    initializeProbabilityDistribution();
}

int Robot::getX() const{
    return this->x;
}

int Robot::getY() const {
    return this->y;
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

double Robot::sensorModel(int x, int y, const std::vector<int>& sensorReadings) const {
    const auto& grid = map.getGrid();
    double probability = 1.0;

    int index = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                int expectedReading = grid[newY][newX];
                int actualReading = sensorReadings[index];
                double readingProbability = std::exp(-std::pow(expectedReading - actualReading, 2) / (2 * std::pow(sensor.getNoise(), 2)));
                probability *= readingProbability;
            }
            ++index;
        }
    }

    return probability;
}

void Robot::normalizeProbabilityDistribution() {
    double sum = 0.0;
    for (const auto& row : probabilityDistribution) {
        for (double prob : row) {
            sum += prob;
        }
    }

    for (auto& row : probabilityDistribution) {
        for (double& prob : row) {
            prob /= sum;
        }
    }
}

void Robot::updateProbabilityDistribution() {
    std::vector<int> sensorReadings = getSensorReading();

    for (int i = 0; i < probabilityDistribution.size(); ++i) {
        for (int j = 0; j < probabilityDistribution[0].size(); ++j) {
            double prior = probabilityDistribution[i][j];
            double likelihood = sensorModel(j, i, sensorReadings);
            probabilityDistribution[i][j] = prior * likelihood;
        }
    }

    normalizeProbabilityDistribution();
}