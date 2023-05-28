#pragma once

#include "RadarObject.hpp"

class ImmobileRadarObject : public RadarObject {
   protected:
    double m_height;

    ImmobileRadarObject(RealPosition position, double height)
        : RadarObject(position), m_height(height) {}

   public:
    virtual RealPosition position_after(double delta_time) const {
        return position();
    }
    virtual double upper_bound() const { return m_height; };
    virtual double lower_bound() const { return 0; };
    virtual void process(double delta_time) {}
};
