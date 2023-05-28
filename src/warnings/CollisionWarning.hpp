#pragma once

#include "Warning.hpp"

class CollisionWarning : public Warning {
   public:
    CollisionWarning(RealPosition point, RadarObjectId id1, RadarObjectId id2,
                     double time);

    virtual WarningKind kind() const;
    virtual std::string message() const;
};
