#include "GUI.hpp"

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
                DrawEllipseLines(x, y, 10, 10, RED);
            }

            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
}
