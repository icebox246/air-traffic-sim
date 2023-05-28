#pragma once

#include <string>

#include "../RealPosition.hpp"
#include "../radar_objects/RadarObjectId.hpp"
#include "WarningKind.hpp"

class Warning {
   protected:
    RealPosition m_point;
    RadarObjectId m_id1;
    RadarObjectId m_id2;
    double m_time;
    Warning(RealPosition point, RadarObjectId id1, RadarObjectId id2,
            double time)
        : m_point(point), m_id1(id1), m_id2(id2), m_time(time) {}

   public:
    RealPosition point() const { return m_point; }
    virtual WarningKind kind() const = 0;
    virtual std::string message() const = 0;
};
