#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "Signal.hpp"

class GUI {
   protected:
    Signal<void, double> m_signal_process;

   public:
    GUI(std::string title);
    ~GUI();
    Signal<void, double>& signal_process() { return m_signal_process; };

    void run();
};
