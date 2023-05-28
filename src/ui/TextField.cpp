#include "TextField.hpp"

#include <raylib.h>

#include <iostream>

size_t TextField::m_next_id = 0;
size_t TextField::m_selected_id = 0;

TextField::TextField(int x, int y, int width, int height, size_t capacity) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
    m_buffer_size = capacity;
    m_buffer = std::make_unique<char[]>(capacity);
    m_buffer[0] = 0;
    m_id = m_next_id++;
}

std::string TextField::get_text() const { return std::string(m_buffer.get()); }

void TextField::set_text(std::string new_text) {
    memcpy(m_buffer.get(), new_text.c_str(),
           std::min(new_text.size() + 1, m_buffer_size));
}

void TextField::process() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), m_bounds)) {
            m_selected_id = m_id;
        } else if (m_selected_id == m_id) {
            m_selected_id = -1;
        }
    }
    GuiTextBox(m_bounds, &m_buffer[0], m_buffer_size, m_id == m_selected_id);
}
