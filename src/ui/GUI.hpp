#pragma once

#include <raygui.h>
#include <raylib.h>

#include <memory>
#include <string>
#include <vector>

#include "../RadarSystem.hpp"
#include "../radar_objects/RadarObject.hpp"
#include "Signal.hpp"

class GUI {
    static const size_t WIDTH = 1000;
    static const size_t HEIGHT = 800;

    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];

   protected:
   public:
    GUI(std::string title);
    ~GUI();

    void run(RadarSystem& radar_system);
};
