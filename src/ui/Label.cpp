#include "Label.hpp"

Label::Label(int x, int y, int width, int height, std::string text)
    : m_text(text) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}
void Label::set_text(std::string new_text) { m_text = std::move(new_text); }

void Label::process() {
    Vector2 position;
    position.x = m_bounds.x;
    position.y =
        m_bounds.y + (m_bounds.height - GuiGetStyle(DEFAULT, TEXT_SIZE)) / 2;
    DrawTextEx(GuiGetFont(), m_text.c_str(), position,
               GuiGetStyle(DEFAULT, TEXT_SIZE),
               GuiGetStyle(DEFAULT, TEXT_SPACING),
               GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
}
