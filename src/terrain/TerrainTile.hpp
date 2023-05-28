#pragma once

#include "../IntegerPosition.hpp"
#include "TerrainTileKind.hpp"

class TerrainTile {
   protected:
    IntegerPosition m_position;
    TerrainTile(IntegerPosition position) : m_position(position) {}

   public:
    virtual TerrainTileKind kind() const = 0;
};
