#include "ProximityWarning.hpp"

#include <iomanip>
#include <sstream>
#include <string>

ProximityWarning::ProximityWarning(RealPosition point, RadarObjectId id1,
                                   RadarObjectId id2, double time,
                                   double distance)
    : Warning(point, id1, id2, time), m_distance(distance) {}

WarningKind ProximityWarning::kind() const { return WarningKind::Proximity; };

std::string ProximityWarning::message() const {
    std::stringstream ss;
    ss << "#" << m_id1 << " & #" << std::to_string(m_id2)
       << " dangerously close at "<< std::fixed << std::setprecision(1)  << m_distance
       << " (in " << std::setprecision(1) << m_time << "s)";
    return ss.str();
}
