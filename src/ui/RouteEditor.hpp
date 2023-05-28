#pragma once

#include <raylib.h>

#include <vector>

#include "../RadarSystem.hpp"
#include "../RealPosition.hpp"
#include "../radar_objects/MobileRadarObject.hpp"
#include "../radar_objects/RouteCheckpoint.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "RealField.hpp"
#include "Signal.hpp"
#include "Widget.hpp"

class RouteEditor : public Widget {
   private:
    RadarSystem& m_radar_system;

    Rectangle m_radar_bounds;
    Rectangle m_props_bounds;

    Label m_velocity_label;
    Label m_altitude_label;

    RealField m_velocity_field;
    RealField m_altitude_field;

    Button m_finish_button;
    Button m_cancel_button;

    struct RoutePoint {
        RealPosition position;
        double velocity;
        double altitude;

        RoutePoint(RealPosition position, double velocity, double altitude);
        RoutePoint(RouteCheckpoint checkpoint);
        RouteCheckpoint into_checkpoint() const;
    };

    Signal<void, RadarObjectId> m_signal_finished;
    Signal<void, RadarObjectId> m_signal_cancelled;

    RadarObjectId m_radar_object_id;
    RealPosition m_radar_object_position;
    std::vector<RoutePoint> m_points;
    size_t m_selected_point;
    bool m_dragging = false;

    void set_selected_point(size_t index);

   public:
    RouteEditor(int radar_x, int radar_y, int radar_width, int radar_height,
                int props_x, int props_y, int props_width, int props_height,
                RadarSystem& radar_system);
    Signal<void, RadarObjectId>& signal_finished() { return m_signal_finished; }
    Signal<void, RadarObjectId>& signal_cancelled() {
        return m_signal_cancelled;
    }
    RadarObjectId radar_object_id() const { return m_radar_object_id; }
    void load_from_object(MobileRadarObject& obj);
    Route get_route() const;
    virtual void process();
};
