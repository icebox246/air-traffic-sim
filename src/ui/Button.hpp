#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "Signal.hpp"
#include "Widget.hpp"

class Button : public Widget {
   private:
    Rectangle m_bounds;
    std::string m_text;
    Signal<void> m_signal_clicked;

   public:
    Button(int x, int y, int width, int height, std::string text);
    Signal<void>& signal_clicked() { return m_signal_clicked; }
    virtual void process();
    void change_text(std::string new_text);
};
