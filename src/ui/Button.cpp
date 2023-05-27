#include "Button.hpp"
Button::Button(int x, int y, int width, int height, std::string text)
    : m_text(text) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}

void Button::process() {
    if (GuiButton(m_bounds, m_text.c_str())) m_signal_clicked.call();
}

void Button::change_text(std::string new_text) { m_text = std::move(new_text); }
