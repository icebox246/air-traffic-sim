#include <vector>

#include "../src/radar_objects/CollisionComputer.hpp"
#include "../src/radar_objects/MobileRadarObject.hpp"
#include "../src/radar_objects/Plane.hpp"
#include "../src/radar_objects/Route.hpp"
#include "../src/radar_objects/Skyscraper.hpp"
#include "../src/util.hpp"

int main() {
    std::vector<RouteCheckpoint> checkpoints;
    checkpoints.push_back(RouteCheckpoint({1, 0}, 1, 0));
    checkpoints.push_back(RouteCheckpoint({1, 1}, 1, 1));
    Route route(checkpoints);
    Plane plane({0, 0}, route);

    Skyscraper skyscraper1({1, 1}, 100);

    {
        CollisionComputer cc(plane, skyscraper1, 2);

        ASSERT_EQ(cc.should_warn(), true);

        auto w = cc.generate_warning();

        ASSERT_EQ(w->message(), "#0 & #1 collide (in 1.4s)");
    }

    Skyscraper skyscraper2({1, 2}, 100);

    {
        CollisionComputer cc(plane, skyscraper2, 2);

        ASSERT_EQ(cc.should_warn(), true);

        auto w = cc.generate_warning();

        ASSERT_EQ(w->message(), "#0 & #2 dangerously close at 2.0 (in 1.0s)");
    }

    Skyscraper skyscraper3({3, 2}, 100);

    {
        CollisionComputer cc(plane, skyscraper3, 2);

        ASSERT_EQ(cc.should_warn(), false);
    }

    return EXIT_SUCCESS;
}
