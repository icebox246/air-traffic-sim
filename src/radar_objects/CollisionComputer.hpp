#pragma once

#include <memory>

#include "../warnings/Warning.hpp"
#include "RadarObject.hpp"

class CollisionComputer {
   private:
    RadarObject const& m_obj1;
    RadarObject const& m_obj2;

    double m_time;
    double m_distance;
    double m_proximity_warning_threshold;
    RealPosition m_point;

   public:
    CollisionComputer(RadarObject const& obj1, RadarObject const& obj2,
                      double proximity_warning_threshold);
    bool should_warn() const;
    std::unique_ptr<Warning> generate_warning();
};
