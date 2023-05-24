#pragma once

#include "../RealPosition.hpp"
#include "RadarObjectId.hpp"
#include "RadarObjectKind.hpp"

class RadarObject {
   protected:
    RadarObjectId m_id;
    RealPosition m_position;
    double m_radius;

   private:
    static RadarObjectId m_next_id;

   public:
    RadarObjectId id() { return m_id; }
    RealPosition position() { return m_position; }
    double radius() { return m_radius; }

    virtual RealPosition position_after(double delta_time) = 0;
    virtual double upper_bound() = 0;
    virtual double lower_bound() = 0;
    virtual RadarObjectKind kind() = 0;
};
