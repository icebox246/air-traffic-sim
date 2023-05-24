#pragma once

#include "RadarObject.hpp"

class ImmobileRadarObject : public RadarObject {
   protected:
    double m_height;

   public:
    virtual RealPosition position_after(double delta_time) {
        return position();
    }
    virtual double upper_bound() { return m_height; };
    virtual double lower_bound() { return 0; };
};
