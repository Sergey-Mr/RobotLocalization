#ifndef ROBOT_H
#define ROBOT_H

#include "Map.h"
#include "Sensor.h"

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
        void updateProbabilityDistribution();

    private:
        int x; 
        int y;
        Map& map;
        Sensor sensor;
        std::vector<std::vector<double>> probabilityDistribution;
        void updatePosition(int newX, int newY);
        void initializeProbabilityDistribution();
        double sensorModel(int x, int y, const std::vector<int>& sensorReading) const;
        void normalizeProbabilityDistribution();
};

#endif