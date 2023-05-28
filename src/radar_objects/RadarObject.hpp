#pragma once

#include "../RealPosition.hpp"
#include "RadarObjectId.hpp"
#include "RadarObjectKind.hpp"

class RadarObject {
   protected:
    RadarObjectId m_id;
    RealPosition m_position;
    double m_radius;

    RadarObject(RealPosition position)
        : m_id(m_next_id++), m_position(position) {}

   private:
    static RadarObjectId m_next_id;

   public:
    RadarObjectId id() const { return m_id; }
    RealPosition position() const { return m_position; }
    double radius() const { return m_radius; }

    virtual RealPosition position_after(double delta_time) const = 0;
    virtual double upper_bound() const = 0;
    virtual double lower_bound() const = 0;
    virtual RadarObjectKind kind() const = 0;
    virtual void process(double delta_time) = 0;
};
