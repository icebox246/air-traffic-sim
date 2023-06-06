#include <vector>

#include "../src/radar_objects/MobileRadarObject.hpp"
#include "../src/radar_objects/Plane.hpp"
#include "../src/radar_objects/Route.hpp"
#include "../src/util.hpp"

int main() {
    std::vector<RouteCheckpoint> checkpoints;
    checkpoints.push_back(RouteCheckpoint({1, 0}, 1, 0));
    checkpoints.push_back(RouteCheckpoint({1, 1}, 1, 1));

    Route route(checkpoints);

    Plane plane({0, 0}, route);

    auto pos = plane.position_after(1.5);

    ASSERT_EQ(pos.x(), 1);
    ASSERT_EQ(pos.y(), 0.5);

    ASSERT_EQ(plane.altitude_after(0), 0);
    ASSERT_EQ(plane.altitude_after(0.5), 0);
    ASSERT_EQ(plane.altitude_after(1.2), 1);
    ASSERT_EQ(plane.altitude_after(1.9), 1);

    return EXIT_SUCCESS;
}
