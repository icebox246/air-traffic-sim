#include <iostream>

#include "RadarSystem.hpp"
#include "ui/GUI.hpp"

int main() {
    std::cout << "Hello, Ship Man!" << std::endl;

    RadarSystem radar_system;

    GUI gui("Air Traffic Simulator");

    gui.signal_process().connect(
        [&](double delta_time) { radar_system.process(delta_time); });

    gui.run();

    std::cout << "Bye, Ship Man!" << std::endl;

    return EXIT_SUCCESS;
}
