#pragma once

#include <raylib.h>

#include "../RadarSystem.hpp"
#include "Widget.hpp"

class WarningList : public Widget {
   private:
    Rectangle m_bounds;
    RadarSystem const& m_radar_system;

    Vector2 m_scroll;

   public:
    WarningList(int x, int y, int width, int height,
                RadarSystem const& radar_system);

    virtual void process();
};
