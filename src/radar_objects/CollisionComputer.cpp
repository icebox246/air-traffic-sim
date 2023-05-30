#include "CollisionComputer.hpp"

#include <cmath>

#include "../util.hpp"
#include "../warnings/CollisionWarning.hpp"
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

    auto bounds_overlap = [](double lower_a, double upper_a, double lower_b,
                             double upper_b) {
        ASSERT(lower_a < upper_a);
        ASSERT(lower_b < upper_b);
        return (lower_a <= lower_b && lower_b <= upper_a) ||
               (lower_a <= upper_b && upper_b <= upper_a) ||
               (lower_b <= lower_a && lower_a <= upper_b) ||
               (lower_b <= upper_a && upper_a <= upper_b);
    };

    for (double dt = 0.; dt <= 10.; dt += 0.1) {
        auto p1 = obj1.position_after(dt);
        auto p2 = obj2.position_after(dt);
        auto l1 = obj1.lower_bound(dt);
        auto u1 = obj1.upper_bound(dt);
        auto l2 = obj2.lower_bound(dt);
        auto u2 = obj2.upper_bound(dt);
        double dist = p1.distance_from(p2);
        if (bounds_overlap(l1, u1, l2, u2) &&
            dist <= obj1.radius() + obj2.radius()) {
            m_time = dt;
            m_distance = 0;
            m_point =
                RealPosition((p1.x() + p2.x()) * .5, (p1.y() + p2.y()) * .5);
            return;
        }
        if (dist <= proximity_warning_threshold && dt < m_time) {
            m_time = dt;
            m_distance = dist;
            m_point =
                RealPosition((p1.x() + p2.x()) * .5, (p1.y() + p2.y()) * .5);
        }
    }
}

bool CollisionComputer::should_warn() const { return m_time != INFINITY; }

std::unique_ptr<Warning> CollisionComputer::generate_warning() {
    if (m_distance == 0)
        return std::make_unique<CollisionWarning>(m_point, m_obj1.id(),
                                                  m_obj2.id(), m_time);
    else
        return std::make_unique<ProximityWarning>(
            m_point, m_obj1.id(), m_obj2.id(), m_time, m_distance);
};
