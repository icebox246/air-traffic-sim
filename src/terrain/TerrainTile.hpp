#pragma once

#include "../IntegerPosition.hpp"
#include "TerrainTileKind.hpp"

class TerrainTile {
   protected:
    IntegerPosition m_position;
    TerrainTile(IntegerPosition position) : m_position(position) {}

   public:
    IntegerPosition position() const { return m_position; }
    virtual TerrainTileKind kind() const = 0;
};
