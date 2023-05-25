#pragma once

#include <math.h>

#include "Position.hpp"

class RealPosition : public Position<double> {
   public:
    RealPosition() : Position<double>(0, 0) {}
    RealPosition(double x, double y) : Position<double>(x, y) {}
    double distance_from(RealPosition other) const {
        double dx = x() - other.x();
        double dy = y() - other.y();
        return sqrt(dx * dx + dy * dy);
    }
};
