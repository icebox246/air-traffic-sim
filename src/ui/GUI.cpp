#include "GUI.hpp"

#include <raylib.h>

#include "../radar_objects/MobileRadarObject.hpp"
#include "../util.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

GUI::GUI(std::string title, RadarSystem& radar_system)
    : m_radar_system(radar_system),
      m_pause_toggle_button(HEIGHT, 0, 32, 32, "#132#"),
      m_radar_view(0, 0, HEIGHT, HEIGHT, radar_system) {
    InitWindow(WIDTH, HEIGHT, title.c_str());

    m_pause_toggle_button.signal_clicked().connect(
        [this]() { set_paused(!m_paused); });
    add_widget(m_pause_toggle_button);

    m_radar_view.load_textures();
    m_radar_view.signal_radar_object_clicked().connect(
        [this](RadarObjectId obj_id) {
            for (auto& ro : m_radar_system.radar_objects()) {
                if (ro->id() != obj_id) continue;
                auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
                if (!as_mobile) break;
                std::cout << "Clicked: " << ro->id() << std::endl;
            }
        });
    add_widget(m_radar_view);
}

GUI::~GUI() { CloseWindow(); }

void GUI::process_widgets() {
    for (auto& w : m_widgets)
        if (w.get().visible()) w.get().process();
}

void GUI::add_widget(Widget& widget) { m_widgets.emplace_back(widget); }

void GUI::set_paused(bool new_paused) {
    if (m_paused == new_paused) return;
    m_paused = new_paused;
    if (new_paused) {
        m_pause_toggle_button.change_text("#131#");
    } else {
        m_pause_toggle_button.change_text("#132#");
    }
}

void GUI::run() {
    while (!WindowShouldClose()) {
        if (!m_paused) {
            m_radar_system.process(GetFrameTime());
        }

        BeginDrawing();
        {
            process_widgets();
            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
}
