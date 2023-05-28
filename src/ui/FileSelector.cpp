#include "FileSelector.hpp"

#include "GUI.hpp"

FileSelector::FileSelector(int x, int y, int width, int height)
    : m_text_field(x, y, width - height, height, 32),
      m_load_button(x + width - height, y, height, height, "#5#") {
    m_text_field.set_text("default.map");

    m_load_button.signal_clicked().connect([this]() {
        auto filename = m_text_field.get_text();
        if (FileExists(filename.c_str())) {
            m_signal_file_selected.call(std::move(filename));
        } else {
            GUI::show_error_box("Could not find: " + filename);
        }
    });
}

void FileSelector::process() {
    m_text_field.process();
    m_load_button.process();
}
