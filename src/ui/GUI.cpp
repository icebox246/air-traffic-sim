#include "GUI.hpp"

GUI::GUI(std::string title) { InitWindow(WIDTH, HEIGHT, title.c_str()); }

GUI::~GUI() { CloseWindow(); }

void GUI::run() {
    while (!WindowShouldClose()) {
        m_signal_process.call(GetFrameTime());

        BeginDrawing();
        {
            auto radar_objects = m_signal_get_radar_objects.call();
            auto sx = m_signal_get_sim_size_x.call();
            auto sy = m_signal_get_sim_size_y.call();

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
