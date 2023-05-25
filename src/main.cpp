#include <iostream>

#include "RadarSystem.hpp"
#include "ui/GUI.hpp"

int main() {
    std::cout << "Hello, Ship Man!" << std::endl;

    RadarSystem radar_system;

    GUI gui("Air Traffic Simulator");

    gui.run(radar_system);

    std::cout << "Bye, Ship Man!" << std::endl;

    return EXIT_SUCCESS;
}
