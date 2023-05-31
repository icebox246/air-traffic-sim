#include "TerrainView.hpp"

#include <raygui.h>

#include <iostream>

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
    auto const& tiles = m_radar_system.terrain().tiles();

    double tile_size = m_bounds.width / sx;
    double radius = tile_size / 2 * 1.7;

    BeginScissorMode(m_bounds.x, m_bounds.y, m_bounds.width, m_bounds.height);
    for (auto const& tile : tiles) {
        auto tpos = tile->position();
        Vector2 center;
        center.x = m_bounds.x + tpos.x() * tile_size + tile_size * .5;
        center.y = m_bounds.y + tpos.y() * tile_size + tile_size * .5;
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
        DrawCircleSector(center, radius, 0, 360, 7, color);
    }
    EndScissorMode();
}
