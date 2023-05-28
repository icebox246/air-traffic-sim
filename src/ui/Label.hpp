#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "Widget.hpp"

class Label : public Widget {
   private:
    Rectangle m_bounds;
    std::string m_text;

   public:
    Label(int x, int y, int width, int height, std::string text);
    void set_text(std::string new_text);
    virtual void process();
};
