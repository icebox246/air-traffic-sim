#pragma once

#include <raylib.h>

#include "../RadarSystem.hpp"
#include "Widget.hpp"

class RadarView : public Widget {
   private:
    Rectangle m_bounds;
    RadarSystem& m_radar_system;
    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];


   public:
    void load_textures();
    virtual void process();
    RadarView(int x, int y, int width, int height, RadarSystem& radar_system);

    ~RadarView() {
        // TODO: should probably unload those but here isn't a great place
        /* for (auto i = 0; i < (size_t)RadarObjectKind::CountKinds; i++) */
        /*     UnloadTexture(m_icon_textures[i]); */
    }
};
