#include "CollisionComputer.hpp"

#include "../util.hpp"
#include "MobileRadarObject.hpp"

CollisionComputer::CollisionComputer(RadarObject const& obj1,
                                     RadarObject const& obj2,
                                     double proximity_warning_threshold)
    : m_obj1(obj1),
      m_obj2(obj2),
      m_proximity_warning_threshold(proximity_warning_threshold) {
    TODO();
}

bool CollisionComputer::should_warn() const { TODO(); }

std::unique_ptr<Warning> CollisionComputer::generate_warning() { TODO(); };
