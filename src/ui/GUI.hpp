#pragma once

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "../radar_objects/RadarObject.hpp"
#include "Signal.hpp"

class GUI {
    static const size_t WIDTH = 1000;
    static const size_t HEIGHT = 800;

   protected:
    Signal<void, double> m_signal_process;
    Signal<std::vector<std::shared_ptr<RadarObject>>>
        m_signal_get_radar_objects;
    Signal<double> m_signal_get_sim_size_x;
    Signal<double> m_signal_get_sim_size_y;

   public:
    GUI(std::string title);
    ~GUI();
    Signal<void, double>& signal_process() { return m_signal_process; }
    Signal<std::vector<std::shared_ptr<RadarObject>>>&
    signal_get_radar_objects() {
        return m_signal_get_radar_objects;
    }
    Signal<double>& signal_get_sim_size_x() { return m_signal_get_sim_size_x; }
    Signal<double>& signal_get_sim_size_y() { return m_signal_get_sim_size_y; }

    void run();
};
