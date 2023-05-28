#include "CollisionWarning.hpp"

#include <iomanip>
#include <sstream>
#include <string>

CollisionWarning::CollisionWarning(RealPosition point, RadarObjectId id1,
                                   RadarObjectId id2, double time)
    : Warning(point, id1, id2, time) {}

WarningKind CollisionWarning::kind() const { return WarningKind::Collision; };

std::string CollisionWarning::message() const {
    std::stringstream ss;
    ss << "#" << m_id1 << " & #" << std::to_string(m_id2) << " collide (in "
       << std::setprecision(1) << std::fixed << m_time << "s)";
    return ss.str();
}
