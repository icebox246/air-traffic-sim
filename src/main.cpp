#include <iostream>
#include "ui/GUI.hpp"

int main() {
    std::cout << "Hello, Ship Man!" << std::endl;

    GUI gui("Air Traffic Simulator");
    gui.run();

    std::cout << "Bye, Ship Man!" << std::endl;

    return EXIT_SUCCESS;
}
