#include "RadarSystem.hpp"

#include <sstream>

#include "radar_objects/CollisionComputer.hpp"
#include "radar_objects/Glider.hpp"
#include "radar_objects/Helicopter.hpp"
#include "radar_objects/HotAirBalloon.hpp"
#include "radar_objects/Mountain.hpp"
#include "radar_objects/Plane.hpp"
#include "radar_objects/Route.hpp"
#include "radar_objects/Skyscraper.hpp"
#include "radar_objects/Windmill.hpp"
#include "util.hpp"

RadarSystem::RadarSystem() {}

bool RadarSystem::change_mobile_object_route(RadarObjectId id,
                                             Route new_route) {
    for (auto& ro : m_radar_objects) {
        if (ro->id() != id) continue;
        auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
        if (!as_mobile) return false;
        as_mobile->change_route(std::move(new_route));
        return true;
    }
    return false;
}

void RadarSystem::load_from_string_data(std::string data) {
    m_radar_objects.clear();
    std::stringstream ss(data);

    while (!ss.eof()) {
        std::string command;
        ss >> command;

        if (command == "terrain") {
            std::string data;
            std::string line;
            while (line != "endterrain\n") {
                data += line;
                ss >> line;
                line += "\n";
            }
            m_terrain = Terrain::from_string_data(data);
        } else if (command == "skyscraper") {
            double x, y, height;
            ss >> x >> y >> height;
            m_radar_objects.emplace_back(
                std::make_unique<Skyscraper>(RealPosition(x, y), height));
        } else if (command == "mountain") {
            double x, y, height;
            ss >> x >> y >> height;
            m_radar_objects.emplace_back(
                std::make_unique<Mountain>(RealPosition(x, y), height));
        } else if (command == "windmill") {
            double x, y, height;
            ss >> x >> y >> height;
            m_radar_objects.emplace_back(
                std::make_unique<Windmill>(RealPosition(x, y), height));
        } else if (command == "mobiles") {
            size_t n;
            ss >> n;
            for (size_t i = 0; i < n; i++)
                generate_random_mobile_radar_object();
        } else {
            std::cerr << "[WARN] Unknown command during file load: " << command
                      << std::endl;
        }
    }
}

void RadarSystem::process(double delta_time) {
    int erased_count = 0;
    for (size_t i = 0; i < m_radar_objects.size(); i++) {
        auto& ro = m_radar_objects[i];
        ro->process(delta_time);
        auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
        if (as_mobile && as_mobile->route().checkpoints().empty()) {
            m_radar_objects.erase(m_radar_objects.begin() + i);
            i--;
            erased_count++;
        }
    }

    for (auto i = 0; i < erased_count; i++) {
        generate_random_mobile_radar_object();
    }

    m_warnings.clear();

    for (size_t i = 0; i < m_radar_objects.size(); i++) {
        for (size_t j = i + 1; j < m_radar_objects.size(); j++) {
            // TODO: parameterize proximity warning threshold
            CollisionComputer cc(*m_radar_objects[i], *m_radar_objects[j], 4);

            if (!cc.should_warn()) continue;

            auto warning = cc.generate_warning();
            m_warnings.push_back(std::move(warning));
        }
    }
}

void RadarSystem::generate_random_mobile_radar_object() {
    auto spread_position_around = [](RealPosition origin, double range) {
        return origin.moved((rand() / (double)(RAND_MAX >> 1) - 1) * range,
                            (rand() / (double)(RAND_MAX >> 1) - 1) * range);
    };
    std::vector<RouteCheckpoint> checkpoints = {};
    int checkpoint_count = rand() % 2 + 1;
    RealPosition origin;
    if (rand() & 1)
        origin = RealPosition((rand() & 1) * int(m_terrain.width() + 2) - 1,
                              (rand() / (double)RAND_MAX) * m_terrain.height());
    else
        origin = RealPosition((rand() / (double)RAND_MAX) * m_terrain.width(),
                              (rand() & 1) * int(m_terrain.height() + 2) - 1);

    {
        RealPosition last_pos = origin;
        for (auto i = 0; i < checkpoint_count; i++) {
            RealPosition pos;
            do {
                pos = spread_position_around(last_pos, m_terrain.width() / 1.5);
            } while (pos.x() <= 0 || pos.y() <= 0 ||
                     pos.x() > m_terrain.width() ||
                     pos.y() > m_terrain.height());

            double velocity = (rand() % 15 + 10) / 10.;
            double altitude = (rand() & 1) * 100 + 100;
            checkpoints.emplace_back(pos, velocity, altitude);
            last_pos = pos;
        }
    }

    {
        RealPosition pos;
        if (rand() & 1)
            pos =
                RealPosition((rand() & 1) * int(m_terrain.width() + 2) - 1,
                             (rand() / (double)RAND_MAX) * m_terrain.height());
        else
            pos = RealPosition((rand() / (double)RAND_MAX) * m_terrain.width(),
                               (rand() & 1) * int(m_terrain.height() + 2) - 1);
        double velocity = (rand() % 15 + 10) / 10.;
        double altitude = (rand() & 1) * 100 + 100;
        checkpoints.emplace_back(pos, velocity, altitude);
    }

    Route route(std::move(checkpoints));

    std::unique_ptr<RadarObject> new_object;

    switch (rand() % 4) {
        case 0:
            new_object = std::make_unique<Plane>(origin, route);
            break;
        case 1:
            new_object = std::make_unique<Helicopter>(origin, route);
            break;
        case 2:
            new_object = std::make_unique<Glider>(origin, route);
            break;
        case 3:
            new_object = std::make_unique<HotAirBalloon>(origin, route);
            break;
    }

    m_radar_objects.push_back(std::move(new_object));
}
