#include "Terrain.hpp"

#include <memory>
#include <string>

#include "MeadowTerrainTile.hpp"
#include "MountainsTerrainTile.hpp"
#include "UrbanTerrainTile.hpp"
#include "WaterTerrainTile.hpp"

Terrain::Terrain(std::vector<std::unique_ptr<TerrainTile>> tiles, size_t width,
                 size_t height)
    : m_tiles(std::move(tiles)), m_width(width), m_height(height) {}

Terrain Terrain::from_string_data(std::string data) {
    std::vector<std::unique_ptr<TerrainTile>> tiles;
    int tx = 0, ty = 0;
    int width = -1, height = -1;
    for (auto c : data) {
        auto position = IntegerPosition(tx, ty);
        switch (c) {
            case '.':  // meadow
                tiles.push_back(std::make_unique<MeadowTerrainTile>(position));
                tx++;
                break;
            case 'u':  // urban
                tiles.push_back(std::make_unique<UrbanTerrainTile>(position));
                tx++;
                break;
            case 'M':  // mountains
                tiles.push_back(
                    std::make_unique<MountainsTerrainTile>(position));
                tx++;
                break;
            case '~':  // water
                tiles.push_back(std::make_unique<WaterTerrainTile>(position));
                tx++;
                break;
            case '\n':  // go to next row
                width = tx;
                height = ty + 1;
                ty++;
                tx = 0;
                break;
        }
    }
    if (width == -1) width = data.size();
    if (height == -1) height = 1;

    return Terrain(std::move(tiles), width, height);
}
