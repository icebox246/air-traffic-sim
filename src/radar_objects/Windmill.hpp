#pragma once

#include "ImmobileRadarObject.hpp"

class Windmill : public ImmobileRadarObject {
   public:
    Windmill(RealPosition position, double height)
        : ImmobileRadarObject(position, height) {}
    virtual RadarObjectKind kind() { return RadarObjectKind::Windmill; }
};
