#ifndef SENSOR_H
#define SENSOR_H

#include "Map.h"
#include <vector>
#include <random>

class Sensor {
    public:
        Sensor(double noiseLevel);
        std::vector<int> getReading(int x, int y, const Map& map) const;
        double getSingleReading(int x, int y, const Map& map) const; // Add this method
        double getNoise() const;

    private:
        double noiseLevel;
        mutable std::default_random_engine generator;
        mutable std::normal_distribution<double> distribution;
};

#endif