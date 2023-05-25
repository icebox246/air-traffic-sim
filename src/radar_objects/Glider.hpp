#pragma once

#include "MobileRadarObject.hpp"

class Glider : public MobileRadarObject {
   public:
    Glider(RealPosition position, Route route)
        : MobileRadarObject(position, route) {}
    virtual RadarObjectKind kind() { return RadarObjectKind::Glider; }
};
