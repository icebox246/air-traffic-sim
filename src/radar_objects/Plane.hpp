#pragma once

#include "MobileRadarObject.hpp"

class Plane : public MobileRadarObject {
   public:
    Plane(RealPosition position, Route route)
        : MobileRadarObject(position, route) {
        m_radius = 0.35;
    }
    virtual RadarObjectKind kind() const { return RadarObjectKind::Plane; }
};
