#pragma once

#include "TerrainTile.hpp"
#include "TerrainTileKind.hpp"

class MeadowTerrainTile : public TerrainTile {
   public:
    MeadowTerrainTile(IntegerPosition position) : TerrainTile(position) {}
    virtual TerrainTileKind kind() const { return TerrainTileKind::Meadow; }
};
