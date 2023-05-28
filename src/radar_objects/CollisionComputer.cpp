#include "CollisionComputer.hpp"

#include <cmath>

#include "../util.hpp"
#include "../warnings/ProximityWarning.hpp"
#include "MobileRadarObject.hpp"

CollisionComputer::CollisionComputer(RadarObject const& obj1,
                                     RadarObject const& obj2,
                                     double proximity_warning_threshold)
    : m_obj1(obj1),
      m_obj2(obj2),
      m_proximity_warning_threshold(proximity_warning_threshold) {
    auto as_mobile1 = dynamic_cast<MobileRadarObject const*>(&m_obj1);
    auto as_mobile2 = dynamic_cast<MobileRadarObject const*>(&m_obj2);

    m_time = INFINITY;

    if (!as_mobile1 && !as_mobile2) {
        // Neither is mobile
        return;
    }

    for (auto dt = 0.; dt <= 5.; dt += 0.1) {
        auto p1 = obj1.position_after(dt);
        auto p2 = obj2.position_after(dt);
        double dist = p1.distance_from(p2);
        if (dist <= proximity_warning_threshold) {
            m_time = dt;
            m_distance = dist;
            m_point =
                RealPosition((p1.x() + p2.x()) * .5, (p1.y() + p2.y()) * .5);
            return;
        }
    }
}

bool CollisionComputer::should_warn() const { return m_time != INFINITY; }

std::unique_ptr<Warning> CollisionComputer::generate_warning() {
    return std::make_unique<ProximityWarning>(m_point, m_obj1.id(), m_obj2.id(),
                                              m_time, m_distance);
};
