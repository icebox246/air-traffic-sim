#include "ProximityWarning.hpp"

#include <string>

ProximityWarning::ProximityWarning(RealPosition point, RadarObjectId id1,
                                   RadarObjectId id2, double time,
                                   double distance)
    : Warning(point, id1, id2, time), m_distance(distance) {}

WarningKind ProximityWarning::kind() const { return WarningKind::Proximity; };

std::string ProximityWarning::message() const {
    return "#" + std::to_string(m_id1) + " & #" + std::to_string(m_id2) +
           " dangerously close at " + std::to_string(m_distance) + " (in " +
           std::to_string(m_time) + "s)";
};
