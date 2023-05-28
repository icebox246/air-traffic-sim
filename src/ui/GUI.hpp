#pragma once

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "../RadarSystem.hpp"
#include "../radar_objects/RadarObject.hpp"
#include "Button.hpp"
#include "RadarView.hpp"
#include "RouteEditor.hpp"
#include "Signal.hpp"
#include "WarningList.hpp"

class GUI {
   private:
    static const size_t WIDTH = 1200;
    static const size_t HEIGHT = 800;
    std::vector<std::reference_wrapper<Widget>> m_widgets;
    RadarSystem& m_radar_system;
    bool m_paused = false;
    Button m_pause_toggle_button;
    RadarView m_radar_view;
    RouteEditor m_route_editor;
    WarningList m_warning_list;

    void process_widgets();
    void add_widget(Widget& widget);
    void set_paused(bool new_paused);

   public:
    GUI(std::string title, RadarSystem& radar_system);
    ~GUI();

    void run();
};
