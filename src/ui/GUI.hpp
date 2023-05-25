#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>

#include "Signal.hpp"

class GUI {
    static const size_t WIDTH = 1000;
    static const size_t HEIGHT = 800;
   protected:
    Signal<void, double> m_signal_process;

   public:
    GUI(std::string title);
    ~GUI();
    Signal<void, double>& signal_process() { return m_signal_process; };

    void run();
};
