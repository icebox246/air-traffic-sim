#pragma once

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "../RadarSystem.hpp"
#include "../radar_objects/RadarObject.hpp"
#include "Button.hpp"
#include "FileSelector.hpp"
#include "RadarView.hpp"
#include "RouteEditor.hpp"
#include "Signal.hpp"
#include "TerrainView.hpp"
#include "WarningList.hpp"
#include "WarningView.hpp"

class GUI {
   private:
    static const size_t WIDTH = 1200;
    static const size_t HEIGHT = 800;
    std::vector<std::reference_wrapper<Widget>> m_widgets;
    RadarSystem& m_radar_system;
    bool m_paused = false;
    Button m_pause_toggle_button;
    TerrainView m_terrain_view;
    RadarView m_radar_view;
    RouteEditor m_route_editor;
    WarningList m_warning_list;
    WarningView m_warning_view;
    FileSelector m_file_selector;

    void process_widgets();
    void add_widget(Widget& widget);
    void set_paused(bool new_paused);

    static bool m_error_box_visible;
    static std::string m_error_box_message;
    void process_error_box();

   public:
    GUI(std::string title, RadarSystem& radar_system);
    ~GUI();

    static void show_error_box(std::string message);
    static void hide_error_box();

    void run();
};
