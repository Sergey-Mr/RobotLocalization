#include "Sensor.h"

Sensor::Sensor(double noiseLevel) : noiseLevel(noiseLevel), distribution(0.0, noiseLevel) {}

std::vector<int> Sensor::getReading(int x, int y, const Map& map) const {
    std::vector<int> readings;
    const auto& grid = map.getGrid();

    // Simulate sensor readings with noise
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                double reading = grid[newY][newX] + distribution(generator);
                readings.push_back(static_cast<int>(reading));
            } else {
                readings.push_back(-1); // Out of bounds
            }
        }
    }

    return readings;
}

double Sensor::getNoise() const {
    return this->noiseLevel;
}