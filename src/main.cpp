#include <iostream>

#include "RadarSystem.hpp"
#include "ui/GUI.hpp"

int main() {
    std::cout << "Hello, Ship Man!" << std::endl;

    RadarSystem radar_system;

    GUI gui("Air Traffic Simulator", radar_system);

    gui.run();

    std::cout << "Bye, Ship Man!" << std::endl;

    return EXIT_SUCCESS;
}
