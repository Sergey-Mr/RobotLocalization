#ifndef ROBOT_H
#define ROBOT_H

#include "Map.h"
#include "Sensor.h"
#include <vector>

class Robot {
    public:
        Robot(int x, int y, Map& map, double sensorNoiseLevel);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void displayPosition() const;
        std::vector<int> getSensorReading() const;
        void displayProbabilityDistribution() const;
        int getX() const;
        int getY() const;
        std::vector<std::vector<double>> getProbabilityDistribution() const;

    private:
        int x; 
        int y;
        Map& map;
        Sensor sensor;
        std::vector<std::vector<double>> probabilityDistribution;
        void updatePosition(int newX, int newY);
        void initializeProbabilityDistribution();
        void updateProbabilityDistributionAfterMove();
        void updateProbabilityDistributionAfterSensorReading();
        double calculateLikelihood(double sensorReading, int x, int y);
};

#endif