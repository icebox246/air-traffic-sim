#pragma once

#include <raygui.h>
#include <raylib.h>

#include <string>
class GUI {
   public:
    GUI(std::string title);
    ~GUI();

    void run();
};
