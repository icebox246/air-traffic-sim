#include "RouteEditor.hpp"

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "../util.hpp"

RouteEditor::RouteEditor(int radar_x, int radar_y, int radar_width,
                         int radar_height, int props_x, int props_y,
                         int props_width, int props_height,
                         RadarSystem& radar_system)
    : m_radar_system(radar_system),
      m_velocity_label(props_x + 8, props_y + 8, props_width - 16, 24,
                       "velocity:"),
      m_velocity_field(props_x + 8, props_y + 8 + 24 + 4, props_width - 16, 24,
                       32),
      m_altitude_label(props_x + 8, props_y + 8 + 24 + 4 + 24 + 8,
                       props_width - 16, 24, "altitude:"),
      m_altitude_field(props_x + 8, props_y + 8 + 24 + 4 + 24 + 8 + 24 + 4,
                       props_width - 16, 24, 32),
      m_finish_button(props_x + 8,
                      props_y + 8 + 24 + 4 + 24 + 8 + 24 + 4 + 24 + 8,
                      props_width - 16, 24, "Finish"),
      m_cancel_button(props_x + 8,
                      props_y + 8 + 24 + 4 + 24 + 8 + 24 + 4 + 24 + 8 + 24 + 4,
                      props_width - 16, 24, "Cancel")

{
    m_radar_bounds.x = radar_x;
    m_radar_bounds.y = radar_y;
    m_radar_bounds.width = radar_width;
    m_radar_bounds.height = radar_height;

    m_props_bounds.x = props_x;
    m_props_bounds.y = props_y;
    m_props_bounds.width = props_width;
    m_props_bounds.height = props_height;

    m_finish_button.signal_clicked().connect([this]() {
        set_visible(false);
        m_signal_finished.call(m_radar_object_id);
    });

    m_cancel_button.signal_clicked().connect([this]() {
        set_visible(false);
        m_signal_cancelled.call(m_radar_object_id);
    });

    set_visible(false);
}

RouteEditor::RoutePoint::RoutePoint(RouteCheckpoint checkpoint)
    : position(checkpoint.point()),
      velocity(checkpoint.velocity()),
      altitude(checkpoint.altitude()) {}

RouteEditor::RoutePoint::RoutePoint(RealPosition position, double velocity,
                                    double altitude)
    : position(position), velocity(velocity), altitude(altitude) {}

RouteCheckpoint RouteEditor::RoutePoint::into_checkpoint() const {
    return RouteCheckpoint(position, velocity, altitude);
}

void RouteEditor::set_selected_point(size_t index) {
    ASSERT(index < m_points.size());
    m_selected_point = index;
    m_velocity_field.set_value(m_points[index].velocity);
    m_altitude_field.set_value(m_points[index].altitude);
}

void RouteEditor::load_from_object(MobileRadarObject& obj) {
    m_radar_object_id = obj.id();
    m_radar_object_position = obj.position();

    m_points.clear();
    for (auto& checkpoint : obj.route().checkpoints()) {
        m_points.emplace_back(checkpoint);
    }

    set_selected_point(0);
}

Route RouteEditor::get_route() const {
    std::vector<RouteCheckpoint> checkpoints;
    for (auto& p : m_points) {
        checkpoints.push_back(p.into_checkpoint());
    }
    return Route(std::move(checkpoints));
}

void RouteEditor::process() {
    process_widgets();
    process_mouse_dragging();
    process_points();
}

void RouteEditor::process_widgets() {
    std::string props_caption =
        "Editing: #" + std::to_string(m_radar_object_id);
    GuiGroupBox(m_props_bounds, props_caption.c_str());

    m_velocity_label.process();
    m_velocity_field.process();

    m_altitude_label.process();
    m_altitude_field.process();

    m_finish_button.process();
    m_cancel_button.process();

    m_points[m_selected_point].velocity = m_velocity_field.get_value();
    m_points[m_selected_point].altitude = m_altitude_field.get_value();
}

void RouteEditor::process_mouse_dragging() {
    int sx = m_radar_system.terrain().width();
    int sy = m_radar_system.terrain().height();

    auto world_to_screen = [&](RealPosition wpos) {
        Vector2 v;
        v.x = wpos.x() / sx * m_radar_bounds.width + m_radar_bounds.x;
        v.y = wpos.y() / sy * m_radar_bounds.height + m_radar_bounds.y;
        return v;
    };

    auto screen_to_world = [&](Vector2 spos) {
        double x = (spos.x - m_radar_bounds.x) * sx / m_radar_bounds.width;
        double y = (spos.y - m_radar_bounds.y) * sy / m_radar_bounds.height;
        return RealPosition(x, y);
    };
    auto mouse_position = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (size_t i = 0; i < m_points.size(); i++) {
            auto& point = m_points[i];
            auto sc = world_to_screen(point.position);
            if (CheckCollisionPointCircle(mouse_position, sc, 8)) {
                m_dragging = true;
                if (m_selected_point != i)
                    set_selected_point(i);
                else
                    break;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_dragging = false;
    }

    if (m_dragging) {
        auto& point = m_points[m_selected_point];
        point.position = screen_to_world(mouse_position);
    }
}

void RouteEditor::process_points() {
    int sx = m_radar_system.terrain().width();
    int sy = m_radar_system.terrain().height();

    auto world_to_screen = [&](RealPosition wpos) {
        Vector2 v;
        v.x = wpos.x() / sx * m_radar_bounds.width + m_radar_bounds.x;
        v.y = wpos.y() / sy * m_radar_bounds.height + m_radar_bounds.y;
        return v;
    };

    auto screen_to_world = [&](Vector2 spos) {
        double x = (spos.x - m_radar_bounds.x) * sx / m_radar_bounds.width;
        double y = (spos.y - m_radar_bounds.y) * sy / m_radar_bounds.height;
        return RealPosition(x, y);
    };

    auto mouse_position = GetMousePosition();
    RealPosition last_position = m_radar_object_position;
    bool inserted_point = false;
    bool deleted_point = false;
    for (size_t i = 0; i < m_points.size(); i++) {
        auto& point = m_points[i];
        auto sl = world_to_screen(last_position);
        auto sc = world_to_screen(point.position);
        Vector2 scenter;
        scenter.x = (sl.x + sc.x) / 2;
        scenter.y = (sl.y + sc.y) / 2;

        DrawLineV(sl, sc, BLUE);
        DrawCircleV(sc, 8, i == m_selected_point ? GREEN : BLUE);

        if (CheckCollisionPointCircle(mouse_position, scenter, 30)) {
            DrawRing(scenter, 5, 8, 0, 360, 12, GREEN);  // Draw ring
        }
        if (!inserted_point && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointCircle(mouse_position, scenter, 5)) {
            RoutePoint new_point = {screen_to_world(scenter), point.velocity,
                                    point.altitude};
            m_points.insert(m_points.begin() + i, new_point);
            set_selected_point(i);
            i--;
            inserted_point = true;
        }

        if (!deleted_point && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) &&
            CheckCollisionPointCircle(mouse_position, sc, 8) &&
            m_points.size() > 1) {
            m_points.erase(m_points.begin() + i);
            if (i < m_points.size())
                set_selected_point(i);
            else
                set_selected_point(i - 1);
            i--;
            deleted_point = true;
            continue;
        }

        last_position = point.position;
    }
}
