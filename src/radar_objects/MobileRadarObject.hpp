#pragma once

#include "RadarObject.hpp"
#include "Route.hpp"

class MobileRadarObject : public RadarObject {
   protected:
    Route m_route;

   public:
    MobileRadarObject(RealPosition position, Route route)
        : RadarObject(position), m_route(route) {}
    Route& route() { return m_route; }
    void change_route(Route new_route) { m_route = new_route; }
    virtual RealPosition position_after(double delta_time);
    virtual double upper_bound() { return m_route.altitude() + m_radius; }
    virtual double lower_bound() { return m_route.altitude() - m_radius; }
    virtual void process(double delta_time);
    double heading();
    double time_to_checkpoint() const;
};
