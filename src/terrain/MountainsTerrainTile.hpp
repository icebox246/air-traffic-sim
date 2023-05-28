#pragma once

#include "TerrainTile.hpp"
#include "TerrainTileKind.hpp"

class MountainsTerrainTile : public TerrainTile {
   public:
    MountainsTerrainTile(IntegerPosition position) : TerrainTile(position) {}
    virtual TerrainTileKind kind() const { return TerrainTileKind::Mountains; }
};
