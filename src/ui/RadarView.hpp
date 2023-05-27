#pragma once

#include <raylib.h>

#include "../RadarSystem.hpp"
#include "Signal.hpp"
#include "Widget.hpp"

class RadarView : public Widget {
   private:
    Rectangle m_bounds;
    RadarSystem& m_radar_system;
    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];
    Signal<void, RadarObjectId> m_signal_radar_object_clicked;

   public:
    RadarView(int x, int y, int width, int height, RadarSystem& radar_system);
    ~RadarView() {
        // TODO: should probably unload those but here isn't a great place
        /* for (auto i = 0; i < (size_t)RadarObjectKind::CountKinds; i++) */
        /*     UnloadTexture(m_icon_textures[i]); */
    }
    Signal<void, RadarObjectId>& signal_radar_object_clicked() {
        return m_signal_radar_object_clicked;
    }
    void load_textures();
    virtual void process();
};
