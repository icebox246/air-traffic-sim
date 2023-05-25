#include <iostream>

#include "RadarSystem.hpp"
#include "ui/GUI.hpp"

int main() {
    std::cout << "Hello, Ship Man!" << std::endl;

    RadarSystem radar_system;

    GUI gui("Air Traffic Simulator");

    gui.signal_process().connect(
        [&](double delta_time) { radar_system.process(delta_time); });
    gui.signal_get_radar_objects().connect(
        [&]() -> auto& { return radar_system.radar_objects(); });
    gui.signal_get_sim_size_x().connect([&]() { return 32; });
    gui.signal_get_sim_size_y().connect([&]() { return 32; });

    gui.run();

    std::cout << "Bye, Ship Man!" << std::endl;

    return EXIT_SUCCESS;
}
