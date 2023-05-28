#pragma once

#include <raygui.h>

#include "../RadarSystem.hpp"
#include "Widget.hpp"

class WarningView : public Widget {
    Rectangle m_bounds;
    RadarSystem const& m_radar_system;

   public:
    WarningView(int x, int y, int width, int height,
                const RadarSystem& m_radar_system);
    virtual void process();
};
