#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    this->initializeGrid();
}

void Map::initializeGrid() {
    this->grid.resize(this->height, std::vector<int>(this->width, 0));
}

void Map::addObject(int x, int y, int objWidth, int objHeigth) {
    for (int i = y; i < y + objHeigth && i < this->height; i++){
        for (int j = x; j < x + objWidth && j < this->width; j++){
            this->grid[i][j] = 1;
        }
    }
}

void Map::addRobot(int x, int y){
    if (x >= 0 && x < this->width && y >= 0 && y < this->height){
        this->grid[y][x] = 2;
    }
}

void Map::display() const {
    for (const auto& row : this->grid){
        for (const auto& column : row){
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
}