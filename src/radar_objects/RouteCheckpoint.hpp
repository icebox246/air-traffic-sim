#pragma once

#include "../RealPosition.hpp"

class RouteCheckpoint {
   private:
    RealPosition m_point;
    double m_velocity;
    double m_altitude;

   public:
    RouteCheckpoint(RealPosition point, double velocity, double altitude)
        : m_point(point), m_velocity(velocity), m_altitude(altitude) {}
    RealPosition point() const { return m_point; }
    double velocity() const { return m_velocity; }
    double altitude() const { return m_altitude; }
};
