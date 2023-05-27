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
    std::vector<std::reference_wrapper<Widget>> m_widgets;
    RadarSystem& m_radar_system;
    bool m_paused = false;
    Button m_pause_toggle_button;
    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];

    void process_widgets();
    void add_widget(Widget& widget);
    void set_paused(bool new_paused);

   public:
    GUI(std::string title, RadarSystem& radar_system);
    ~GUI();

    void run();
};
