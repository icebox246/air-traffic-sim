#pragma once

#include "MobileRadarObject.hpp"

class Helicopter : public MobileRadarObject {
   public:
    Helicopter(RealPosition position, Route route)
        : MobileRadarObject(position, route) {}
    virtual RadarObjectKind kind() const { return RadarObjectKind::Helicopter; }
};
