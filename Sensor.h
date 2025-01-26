#ifndef SENSOR_H
#define SENSOR_H

#include "Map.h"
#include <random>

class Sensor {
    public:
        Sensor(double noiseLevel);
        std::vector<int> getReading(int x, int y, const Map& map) const;

    private:
        double noiseLevel;
        mutable std::default_random_engine generator;
        mutable std::normal_distribution<double> distribution;
};

#endif