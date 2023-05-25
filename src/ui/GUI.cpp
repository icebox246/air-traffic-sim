#include "GUI.hpp"

#include <raylib.h>

#include "../radar_objects/MobileRadarObject.hpp"

GUI::GUI(std::string title) { InitWindow(WIDTH, HEIGHT, title.c_str()); }

GUI::~GUI() { CloseWindow(); }

void GUI::run(RadarSystem& radar_system) {
    while (!WindowShouldClose()) {
        radar_system.process(GetFrameTime());

        BeginDrawing();
        {
            auto& radar_objects = radar_system.radar_objects();
            // TODO: actually get the size from terrain
            auto sx = 32;
            auto sy = 32;

            for (auto& ro : radar_objects) {
                RealPosition pos = ro->position();
                int x = pos.x() / sx * HEIGHT;
                int y = pos.y() / sy * HEIGHT;
                auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
                if (as_mobile) {
                    double angle = as_mobile->heading();
                    Rectangle rec;
                    rec.x = x - 10;
                    rec.y = y - 15;
                    rec.width = 20;
                    rec.height = 30;
                    DrawRectanglePro(rec, Vector2{10, 15}, angle * RAD2DEG - 90,
                                     RED);
                } else {
                    DrawEllipseLines(x, y, 10, 10, RED);
                }
            }

            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
}
