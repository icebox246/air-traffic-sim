#include "GUI.hpp"

GUI::GUI(std::string title) { InitWindow(800, 600, title.c_str()); }

GUI::~GUI() { CloseWindow(); }

void GUI::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        { ClearBackground(RAYWHITE); }
        EndDrawing();
    }
}
