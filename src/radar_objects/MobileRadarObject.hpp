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
    virtual RealPosition position_after();
    virtual void process(double delta_time);
    double heading();
};
