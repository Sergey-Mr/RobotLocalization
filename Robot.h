#ifndef ROBOT_H
#define ROBOT_H

#include "Map.h"

class Robot {
    public:
        Robot(int x, int y, Map& map);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

    private:
        int x; 
        int y;
        Map& map;
};

#endif