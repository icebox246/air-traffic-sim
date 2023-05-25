#pragma once

#include "MobileRadarObject.hpp"

class Plane : public MobileRadarObject {
   public:
    Plane(RealPosition position, Route route)
        : MobileRadarObject(position, route) {}
    virtual RadarObjectKind kind() { return RadarObjectKind::Plane; }
};
