#include "GUI.hpp"

#include <raylib.h>

#include "../radar_objects/MobileRadarObject.hpp"
#include "../util.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

GUI::GUI(std::string title, RadarSystem& radar_system)
    : m_radar_system(radar_system),
      m_pause_toggle_button(HEIGHT, 0, 32, 32, "#132#"),
      m_terrain_view(0, 0, HEIGHT, HEIGHT, radar_system),
      m_radar_view(0, 0, HEIGHT, HEIGHT, radar_system),
      m_warning_view(0, 0, HEIGHT, HEIGHT, radar_system),
      m_route_editor(0, 0, HEIGHT, HEIGHT, HEIGHT, 40, WIDTH - HEIGHT, 200,
                     radar_system),
      m_warning_list(HEIGHT, 248, WIDTH - HEIGHT, HEIGHT - 248 - 40,
                     radar_system),
      m_file_selector(HEIGHT, HEIGHT - 32, WIDTH - HEIGHT, 32)

{
    InitWindow(WIDTH, HEIGHT, title.c_str());
    SetTargetFPS(60);

    m_pause_toggle_button.signal_clicked().connect([this]() {
        if (m_paused && m_route_editor.visible()) {
            m_radar_system.change_mobile_object_route(
                m_route_editor.radar_object_id(), m_route_editor.get_route());
            m_route_editor.set_visible(false);
        }
        set_paused(!m_paused);
    });
    add_widget(m_pause_toggle_button);

    add_widget(m_terrain_view);

    m_radar_view.load_textures();
    m_radar_view.signal_radar_object_clicked().connect(
        [this](RadarObjectId obj_id) {
            if (m_route_editor.visible()) return;
            for (auto& ro : m_radar_system.radar_objects()) {
                if (ro->id() != obj_id) continue;
                auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
                if (!as_mobile) break;
                m_route_editor.load_from_object(*as_mobile);
                set_paused(true);
                m_route_editor.set_visible(true);
                return;
            }
        });
    add_widget(m_radar_view);

    add_widget(m_warning_view);

    m_route_editor.signal_finished().connect([this](RadarObjectId obj_id) {
        m_radar_system.change_mobile_object_route(obj_id,
                                                  m_route_editor.get_route());
        set_paused(false);
    });
    m_route_editor.signal_cancelled().connect(
        [this](RadarObjectId obj_id) { set_paused(false); });
    add_widget(m_route_editor);

    add_widget(m_warning_list);

    m_file_selector.signal_file_selected().connect([&](std::string filename) {
        auto* raw_data = LoadFileText(filename.c_str());
        std::string data = std::string(raw_data);
        UnloadFileText(raw_data);

        m_radar_system.load_from_string_data(data);
    });
    add_widget(m_file_selector);
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
            process_error_box();
            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
}

bool GUI::m_error_box_visible = false;
std::string GUI::m_error_box_message = "";

void GUI::process_error_box() {
    if (m_error_box_visible) {
        Rectangle bounds;
        bounds.width = 200;
        bounds.height = 100;
        bounds.x = WIDTH * 0.5 - bounds.width * 0.5;
        bounds.y = HEIGHT * 0.5 - bounds.height * 0.5;

        if (GuiMessageBox(bounds, "Error", (m_error_box_message + ";").c_str(),
                          "OK") == 1) {
            hide_error_box();
        }
    }
}
void GUI::show_error_box(std::string message) {
    m_error_box_visible = true;
    m_error_box_message = message;
}
void GUI::hide_error_box() { m_error_box_visible = false; }
