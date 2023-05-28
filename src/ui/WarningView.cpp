#include "WarningView.hpp"

#include "raygui.h"

WarningView::WarningView(int x, int y, int width, int height,
                         const RadarSystem& m_radar_system)
    : m_radar_system(m_radar_system) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}

void WarningView::process() {
    auto& warnings = m_radar_system.warnings();

    int sx = m_radar_system.terrain().width();
    int sy = m_radar_system.terrain().height();

    auto world_to_screen = [&](RealPosition wpos) {
        Vector2 v;
        v.x = wpos.x() / sx * m_bounds.width + m_bounds.x;
        v.y = wpos.y() / sy * m_bounds.height + m_bounds.y;
        return v;
    };

    for (auto const& w : warnings) {
        Color color;
        switch (w->kind()) {
            case WarningKind::Collision:
                color = RED;
                break;
            case WarningKind::Proximity:
                color = ORANGE;
                break;
        }
        auto pos = world_to_screen(w->point());
        GuiDrawIcon(ICON_CRACK_POINTS, pos.x, pos.y, 1, color);
        std::string msg = w->short_message();
        DrawText(msg.c_str(), pos.x, pos.y + 12, 10, BLACK);
    }
}
