#pragma once

#include <raylib.h>

#include "../RadarSystem.hpp"
#include "Widget.hpp"

class TerrainView : public Widget {
   private:
    Rectangle m_bounds;
    RadarSystem const& m_radar_system;

   public:
    TerrainView(int x, int y, int width, int height,
                const RadarSystem& radar_system);

    virtual void process();
};
