#include "RadarSystem.hpp"

#include "radar_objects/Plane.hpp"
#include "radar_objects/Route.hpp"
#include "radar_objects/Skyscraper.hpp"
#include "util.hpp"

RadarSystem::RadarSystem() {
    // TODO: don't do that
    auto building = std::make_unique<Skyscraper>(RealPosition(1, 2), 32);
    Route route = Route({
        RouteCheckpoint({2, 2}, 0.5, 1000),
        RouteCheckpoint({2, 4}, 0.5, 1000),
        RouteCheckpoint({0, 2}, 0.5, 1000),
    });
    auto plane = std::make_unique<Plane>(RealPosition(0, 0), std::move(route));

    m_radar_objects.push_back(std::move(building));
    m_radar_objects.push_back(std::move(plane));
}

bool RadarSystem::change_mobile_object_route(RadarObjectId id,
                                             Route new_route) {
    TODO();
}

void RadarSystem::load_from_string_data(std::string data) { TODO(); }

void RadarSystem::process(double delta_time) {
    for (auto& ro : m_radar_objects) {
        ro->process(delta_time);
    }
}
