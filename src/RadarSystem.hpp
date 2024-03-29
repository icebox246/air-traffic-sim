#pragma once

#include <memory>
#include <vector>

#include "radar_objects/RadarObject.hpp"
#include "radar_objects/RadarObjectId.hpp"
#include "radar_objects/Route.hpp"
#include "terrain/Terrain.hpp"
#include "warnings/Warning.hpp"

class RadarSystem {
   private:
    std::vector<std::unique_ptr<RadarObject>> m_radar_objects;
    std::vector<std::unique_ptr<Warning>> m_warnings;
    Terrain m_terrain = Terrain::from_string_data("");

   public:
    class UnknownCommandException {
        std::string m_command;

       public:
        UnknownCommandException(std::string command) : m_command(command) {}
        std::string message() const {
            return "Encountered unknown command: `" + m_command + "`";
        }
    };

    RadarSystem();
    std::vector<std::unique_ptr<RadarObject>> const& radar_objects() const {
        return m_radar_objects;
    }
    std::vector<std::unique_ptr<Warning>> const& warnings() const {
        return m_warnings;
    }
    Terrain const& terrain() const { return m_terrain; }

    bool change_mobile_object_route(RadarObjectId id, Route new_route);
    void load_from_string_data(std::string data) noexcept(false);
    void process(double delta);

   private:
    void generate_random_mobile_radar_object();
};
