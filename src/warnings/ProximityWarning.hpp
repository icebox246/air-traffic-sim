#pragma once

#include "Warning.hpp"

class ProximityWarning : public Warning {
   private:
    double m_distance;

   public:
    ProximityWarning(RealPosition point, RadarObjectId id1, RadarObjectId id2,
                     double time, double distance);

    virtual WarningKind kind() const;
    virtual std::string message() const;
};
