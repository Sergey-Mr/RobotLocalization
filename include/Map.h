#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>

class Map {
    public:
        Map(int width, int height);
        void addObject(int x, int y, int objWidth, int objHeigth);
        void addRobot(int x, int y);
        void display() const;
        const std::vector<std::vector<int>>& getGrid() const;
        bool isValidMove(int newX, int newY) const;
        bool updateRobotPosition(int oldX, int oldY, int newX, int newY);
        double getExpectedReading(int x, int y) const; // Add this method

    private:
        int width;
        int height;
        std::vector<std::vector<int>> grid;
        void initializeGrid();
};

#endif