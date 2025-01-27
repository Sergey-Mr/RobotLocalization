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

void Robot::updateProbabilityDistributionAfterMove() {
    int width = map.getGrid()[0].size();
    int height = map.getGrid().size();
    std::vector<std::vector<double>> newDistribution(height, std::vector<double>(width, 0.0));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (map.isValidMove(j, i)) {
                // Update probabilities based on movement model
                if (i > 0) newDistribution[i][j] += 0.25 * probabilityDistribution[i-1][j]; // from above
                if (i < height - 1) newDistribution[i][j] += 0.25 * probabilityDistribution[i+1][j]; // from below
                if (j > 0) newDistribution[i][j] += 0.25 * probabilityDistribution[i][j-1]; // from left
                if (j < width - 1) newDistribution[i][j] += 0.25 * probabilityDistribution[i][j+1]; // from right
            }
        }
    }

    probabilityDistribution = newDistribution;
}

void Robot::updateProbabilityDistributionAfterSensorReading() {
    int width = map.getGrid()[0].size();
    int height = map.getGrid().size();
    double totalProbability = 0.0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double sensorReading = sensor.getSingleReading(j, i, map);
            double likelihood = calculateLikelihood(sensorReading, j, i);
            probabilityDistribution[i][j] *= likelihood;
            totalProbability += probabilityDistribution[i][j];
        }
    }

    // Normalize the probabilities
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            probabilityDistribution[i][j] /= totalProbability;
        }
    }
}

double Robot::calculateLikelihood(double sensorReading, int x, int y) {
    double expectedReading = map.getExpectedReading(x, y);
    double variance = sensor.getNoise() * sensor.getNoise();
    double diff = sensorReading - expectedReading;
    return exp(-diff * diff / (2 * variance)) / sqrt(2 * M_PI * variance);
}

void Robot::updatePosition(int newX, int newY){
    if (this->map.updateRobotPosition(this->x, this->y, newX, newY)){  
        this->x = newX;
        this->y = newY;
        updateProbabilityDistributionAfterMove();
        updateProbabilityDistributionAfterSensorReading();
    } else {
        // Handle invalid move
        std::cerr << "Invalid move to position (" << newX << ", " << newY << ")" << std::endl;
    }
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
        this->updatePosition(newX, y);
    }
}

void Robot::moveRight(){
    if (map.isValidMove(x + 1, y)){
        int newX = x + 1;
        this->updatePosition(newX, y);
    }
}

std::vector<int> Robot::getSensorReading() const {
    return sensor.getReading(x, y, map);
}

void Robot::displayProbabilityDistribution() const {
    for (const auto& row : probabilityDistribution) {
        for (double prob : row) {
            std::cout << prob << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>> Robot::getProbabilityDistribution() const {
    return probabilityDistribution;
}