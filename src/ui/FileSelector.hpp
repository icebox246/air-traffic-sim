#pragma once

#include <raygui.h>

#include "Button.hpp"
#include "TextField.hpp"
#include "Widget.hpp"

class FileSelector : public Widget {
   private:
    TextField m_text_field;
    Button m_load_button;
    Signal<void, std::string> m_signal_file_selected;

   public:
    FileSelector(int x, int y, int width, int height);
    Signal<void, std::string>& signal_file_selected() {
        return m_signal_file_selected;
    }
    virtual void process();
};
