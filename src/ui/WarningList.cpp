#include "WarningList.hpp"

#include <raygui.h>

#include "../util.hpp"

WarningList::WarningList(int x, int y, int width, int height,
                         RadarSystem const& radar_system)
    : m_radar_system(radar_system) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}

void WarningList::process() {
    const int warning_height = 24;
    auto& warnings = m_radar_system.warnings();
    Rectangle content_rec = {0};
    content_rec.width = m_bounds.width - GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);
    content_rec.height = warning_height * warnings.size();
    GuiScrollPanel(m_bounds, "Warnings:", content_rec, &m_scroll);

    Rectangle label_rec;
    label_rec.width = content_rec.width - 8;
    label_rec.height = warning_height;
    label_rec.x = m_bounds.x + 4;
    label_rec.y = m_bounds.y + 32 + m_scroll.y;

    BeginScissorMode(m_bounds.x, m_bounds.y + 24, m_bounds.width,
                     m_bounds.height - 32);
    {
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
            Vector2 position;
            position.x = label_rec.x;
            position.y = label_rec.y;
            DrawTextEx(GuiGetFont(), w->message().c_str(), position,
                       GuiGetStyle(DEFAULT, TEXT_SIZE),
                       GuiGetStyle(DEFAULT, TEXT_SPACING), color);
            label_rec.y += label_rec.height;
        }
    }
    EndScissorMode();

    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, DEFAULT);
}
