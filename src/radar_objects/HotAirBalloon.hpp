#pragma once

#include "MobileRadarObject.hpp"

class HotAirBalloon : public MobileRadarObject {
   public:
    HotAirBalloon(RealPosition position, Route route)
        : MobileRadarObject(position, route) {}
    virtual RadarObjectKind kind() { return RadarObjectKind::HotAirBalloon; }
};
