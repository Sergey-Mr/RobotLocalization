#include "Map.h"
#include "Robot.h"
#include <iostream>

int main() {
    Map map(10, 10);
    map.addObject(2, 3, 3, 2);
    map.addObject(5, 5, 2, 3);
    Robot robot(1, 1, map, 0.1); // Initialize robot with sensor noise level
    map.display();
    robot.displayPosition();
    robot.displayProbabilityDistribution(); // Display the initial probability distribution
    robot.moveRight();
    robot.moveDown();
    robot.displayPosition();
    map.display(); // Display the map again to see the updated position
    robot.displayProbabilityDistribution();

    // Get and display sensor readings
    std::vector<int> readings = robot.getSensorReading();
    std::cout << "Sensor readings: ";
    for (int reading : readings) {
        std::cout << reading << " ";
    }
    std::cout << std::endl;

    return 0;
}