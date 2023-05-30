#pragma once

#include "TerrainTile.hpp"
#include "TerrainTileKind.hpp"

class WaterTerrainTile : public TerrainTile {
   public:
    WaterTerrainTile(IntegerPosition position) : TerrainTile(position) {}
    virtual TerrainTileKind kind() const { return TerrainTileKind::Water; }
};
