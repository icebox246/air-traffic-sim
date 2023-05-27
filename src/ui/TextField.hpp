#pragma once

#include <raygui.h>

#include <algorithm>
#include <cstring>
#include <memory>
#include <string>

#include "Widget.hpp"

class TextField : public Widget {
   protected:
    Rectangle m_bounds;
    size_t m_buffer_size;
    std::unique_ptr<char[]> m_buffer;
    size_t m_id;
    static size_t m_next_id;
    static size_t m_selected_id;

   public:
    TextField(int x, int y, int width, int height, size_t capacity);
    std::string get_text() const;
    void set_text(std::string new_text);
    virtual void process();
};
