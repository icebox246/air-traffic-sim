#pragma once

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "../RadarSystem.hpp"
#include "../radar_objects/RadarObject.hpp"
#include "Button.hpp"
#include "Signal.hpp"

class GUI {
   private:
    static const size_t WIDTH = 1000;
    static const size_t HEIGHT = 800;
    RadarSystem& m_radar_system;
    bool m_paused = false;
    Button m_pause_toggle_button;

    void set_paused(bool new_paused) {
        if (m_paused == new_paused) return;
        m_paused = new_paused;
        if (new_paused) {
            m_pause_toggle_button.change_text("#131#");
        } else {
            m_pause_toggle_button.change_text("#132#");
        }
    }

    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];

   public:
    GUI(std::string title, RadarSystem& radar_system);
    ~GUI();

    void run();
};
