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
   private:
    static const size_t WIDTH = 1000;
    static const size_t HEIGHT = 800;
    RadarSystem& m_radar_system;

    Texture m_icon_textures[(size_t)RadarObjectKind::CountKinds];

   public:
    GUI(std::string title, RadarSystem& radar_system);
    ~GUI();

    void run();
};
