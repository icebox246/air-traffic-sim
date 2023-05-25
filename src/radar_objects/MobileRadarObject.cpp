#include "MobileRadarObject.hpp"

#include "../util.hpp"

RealPosition MobileRadarObject::position_after(double delta_time) {
    auto& checkpoints = m_route.checkpoints();
    auto position = m_position;

    auto time_to_point = [&](RouteCheckpoint const& checkpoint) {
        return position.distance_from(checkpoint.point()) /
               checkpoint.velocity();
    };

    auto current_point = checkpoints.begin();
    {
        double t;
        while (current_point != checkpoints.end() &&
               (t = time_to_point(*current_point)) <= delta_time) {
            position = current_point->point();
            current_point++;
            delta_time -= t;
        }
    }

    if (current_point == checkpoints.end()) return position;

    double distance_to_checkpoint =
        position.distance_from(current_point->point());

    double dx = current_point->point().x() - position.x();
    double dy = current_point->point().y() - position.y();

    dx /= distance_to_checkpoint;
    dy /= distance_to_checkpoint;

    dx *= current_point->velocity() * delta_time;
    dy *= current_point->velocity() * delta_time;

    return position.moved(dx, dy);
}

void MobileRadarObject::process(double delta_time) {
    while (time_to_checkpoint() <= delta_time) {
        delta_time -= time_to_checkpoint();
        if (!m_route.advance_checkpoint()) {
            // should destroy object
            TODO();
        }
    }

    m_position = position_after(delta_time);
}

double MobileRadarObject::heading() {
    RealPosition target = m_route.target();
    double dx = m_position.x() - target.x();
    double dy = m_position.y() - target.y();
    return std::atan2(dy, dx);
}

double MobileRadarObject::time_to_checkpoint() const {
    return m_position.distance_from(m_route.target()) / m_route.velocity();
};
