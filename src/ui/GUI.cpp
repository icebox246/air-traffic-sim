#include "GUI.hpp"

#include <raylib.h>

#include "../radar_objects/MobileRadarObject.hpp"
#include "../util.hpp"

GUI::GUI(std::string title, RadarSystem& radar_system)
    : m_radar_system(radar_system) {
    InitWindow(WIDTH, HEIGHT, title.c_str());

    m_icon_textures[(size_t)RadarObjectKind::Plane] =
        LoadTexture("resources/icons_plane.png");
    m_icon_textures[(size_t)RadarObjectKind::Helicopter] =
        LoadTexture("resources/icons_helicopter.png");
    m_icon_textures[(size_t)RadarObjectKind::Glider] =
        LoadTexture("resources/icons_glider.png");
    m_icon_textures[(size_t)RadarObjectKind::HotAirBalloon] =
        LoadTexture("resources/icons_balloon.png");
    m_icon_textures[(size_t)RadarObjectKind::Skyscraper] =
        LoadTexture("resources/icons_skyscraper.png");
    m_icon_textures[(size_t)RadarObjectKind::Mountain] =
        LoadTexture("resources/icons_mountain.png");
    m_icon_textures[(size_t)RadarObjectKind::Windmill] =
        LoadTexture("resources/icons_windmill.png");

    for (auto i = 0; i < (size_t)RadarObjectKind::CountKinds; i++)
        SetTextureFilter(m_icon_textures[i], TEXTURE_FILTER_BILINEAR);
}

GUI::~GUI() {
    for (auto i = 0; i < (size_t)RadarObjectKind::CountKinds; i++)
        UnloadTexture(m_icon_textures[i]);

    CloseWindow();
}

void GUI::run() {
    while (!WindowShouldClose()) {
        m_radar_system.process(GetFrameTime());

        BeginDrawing();
        {
            auto& radar_objects = m_radar_system.radar_objects();
            // TODO: actually get the size from terrain
            auto sx = m_radar_system.terrain().width();
            auto sy = m_radar_system.terrain().height();

            for (auto& ro : radar_objects) {
                RealPosition pos = ro->position();
                float texture_scale = 0.4;
                double angle = 0;
                auto as_mobile = dynamic_cast<MobileRadarObject*>(ro.get());
                if (as_mobile) {
                    angle = as_mobile->heading() * RAD2DEG - 90;
                    RealPosition last_pos = pos;
                    for (auto& checkpoint : as_mobile->route().checkpoints()) {
                        RealPosition now_pos = checkpoint.point();
                        DrawLine(last_pos.x() / sx * HEIGHT,
                                 last_pos.y() / sy * HEIGHT,
                                 now_pos.x() / sx * HEIGHT,
                                 now_pos.y() / sy * HEIGHT, GRAY);
                        last_pos = now_pos;
                    }
                }
                double x = pos.x() / sx * HEIGHT;
                double y = pos.y() / sy * HEIGHT;
                Texture& tex = m_icon_textures[(size_t)ro->kind()];
                Rectangle srec;
                srec.x = 0;
                srec.y = 0;
                srec.width = tex.width;
                srec.height = tex.height;
                Rectangle drec;
                drec.x = x;
                drec.y = y;
                drec.width = tex.width * texture_scale;
                drec.height = tex.height * texture_scale;
                Vector2 origin;
                origin.x = tex.width * texture_scale * 0.5;
                origin.y = tex.height * texture_scale * 0.5;
                DrawTexturePro(tex, srec, drec, origin, angle, WHITE);
            }

            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
}
