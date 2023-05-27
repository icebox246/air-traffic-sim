#pragma once

#include <cstddef>

enum class RadarObjectKind : size_t {
    Plane = 0,
    Helicopter,
    Glider,
    HotAirBalloon,
    Skyscraper,
    Mountain,
    Windmill,
    CountKinds,
};
