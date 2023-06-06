#pragma once

#include "RadarObject.hpp"
#include "Route.hpp"

class MobileRadarObject : public RadarObject {
   protected:
    Route m_route;
    MobileRadarObject(RealPosition position, Route route)
        : RadarObject(position), m_route(route) {}

   public:
    virtual ~MobileRadarObject() {}
    Route const& route() const { return m_route; }
    void change_route(Route new_route) { m_route = new_route; }
    virtual RealPosition position_after(double delta_time) const;
    double altitude_after(double delta_time) const;
    virtual double upper_altitude_bound_after(double delta_time) const {
        return altitude_after(delta_time) + m_radius;
    }
    virtual double lower_altitude_bound_after(double delta_time) const {
        return altitude_after(delta_time) - m_radius;
    }
    virtual void process(double delta_time);
    double heading() const;
    double time_to_checkpoint() const;
};
