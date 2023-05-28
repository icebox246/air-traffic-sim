#pragma once

#include "ImmobileRadarObject.hpp"

class Mountain : public ImmobileRadarObject {
   public:
    Mountain(RealPosition position, double height)
        : ImmobileRadarObject(position, height) {}
    virtual RadarObjectKind kind() const { return RadarObjectKind::Mountain; }
};
