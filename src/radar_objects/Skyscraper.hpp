#pragma once

#include "ImmobileRadarObject.hpp"

class Skyscraper : public ImmobileRadarObject {
   public:
    Skyscraper(RealPosition position, double height)
        : ImmobileRadarObject(position, height) {}
    virtual RadarObjectKind kind() const { return RadarObjectKind::Skyscraper; }
};
