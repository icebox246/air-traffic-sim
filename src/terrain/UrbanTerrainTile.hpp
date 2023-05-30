#pragma once

#include "TerrainTile.hpp"
#include "TerrainTileKind.hpp"

class UrbanTerrainTile : public TerrainTile {
   public:
    UrbanTerrainTile(IntegerPosition position) : TerrainTile(position) {}
    virtual TerrainTileKind kind() const { return TerrainTileKind::Urban; }
};
