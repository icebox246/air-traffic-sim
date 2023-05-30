#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "TerrainTile.hpp"

class Terrain {
   private:
    std::vector<std::unique_ptr<TerrainTile>> m_tiles;
    size_t m_width;
    size_t m_height;
    Terrain(std::vector<std::unique_ptr<TerrainTile>> tiles, size_t width,
            size_t height);

   public:
    static Terrain from_string_data(std::string data);
    std::vector<std::unique_ptr<TerrainTile>> const& tiles() const {
        return m_tiles;
    }
    size_t width() const { return m_width; }
    size_t height() const { return m_height; }
};
