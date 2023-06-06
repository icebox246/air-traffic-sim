#include "../src/terrain/Terrain.hpp"

#include <string>

#include "../src/util.hpp"

int main() {
    Terrain terrain = Terrain::from_string_data(".u\nM~\n");

    ASSERT_EQ(terrain.width(), 2);
    ASSERT_EQ(terrain.height(), 2);

    auto const& tiles = terrain.tiles();

    ASSERT_EQ(tiles.size(), 4);
    ASSERT_EQ((size_t)tiles[0]->kind(), (size_t)TerrainTileKind::Meadow);
    ASSERT_EQ((size_t)tiles[1]->kind(), (size_t)TerrainTileKind::Urban);
    ASSERT_EQ((size_t)tiles[2]->kind(), (size_t)TerrainTileKind::Mountains);
    ASSERT_EQ((size_t)tiles[3]->kind(), (size_t)TerrainTileKind::Water);

    return EXIT_SUCCESS;
}
