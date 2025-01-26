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

    private:
        int x; 
        int y;
        Map& map;
        Sensor sensor;
        void updatePosition(int newX, int newY);
};

#endif