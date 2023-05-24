#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "Signal.hpp"

class GUI {
   protected:
    Signal<double> m_signal_process;

   public:
    GUI(std::string title);
    ~GUI();
    Signal<double>& signal_process();

    void run();
};
