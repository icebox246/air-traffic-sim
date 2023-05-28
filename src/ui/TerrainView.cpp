#include "TerrainView.hpp"

#include <raygui.h>

TerrainView::TerrainView(int x, int y, int width, int height,
                         const RadarSystem& radar_system)
    : m_radar_system(radar_system) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}

void TerrainView::process() {
    auto sx = m_radar_system.terrain().width();
    auto sy = m_radar_system.terrain().height();
    auto const& tiles = m_radar_system.terrain().tiles();

    Rectangle tile_rec;
    tile_rec.width = m_bounds.width / sx;
    tile_rec.height = m_bounds.height / sy;

    for (auto const& tile : tiles) {
        auto tpos = tile->position();
        tile_rec.x = m_bounds.x + tpos.x() * tile_rec.width;
        tile_rec.y = m_bounds.y + tpos.y() * tile_rec.height;
        Color color;
        switch (tile->kind()) {
            case TerrainTileKind::Meadow:
                color = GetColor(0xb8fd9bff);
                break;
            case TerrainTileKind::Urban:
                color = GetColor(0xbac5c5ff);
                break;
            case TerrainTileKind::Mountains:
                color = GetColor(0xd1bfadff);
                break;
            case TerrainTileKind::Water:
                color = GetColor(0x8bd8feff);
                break;
        }
        DrawRectangleRec(tile_rec, color);
    }
}
