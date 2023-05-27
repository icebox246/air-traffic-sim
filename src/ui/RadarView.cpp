#include "RadarView.hpp"

#include <raylib.h>

#include "../radar_objects/MobileRadarObject.hpp"
#include "../util.hpp"

RadarView::RadarView(int x, int y, int width, int height,
                     RadarSystem& radar_system)
    : m_radar_system(radar_system) {
    m_bounds.x = x;
    m_bounds.y = y;
    m_bounds.width = width;
    m_bounds.height = height;
}

void RadarView::load_textures() {
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

void RadarView::process() {
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
                DrawLine(last_pos.x() / sx * m_bounds.width,
                         last_pos.y() / sy * m_bounds.height,
                         now_pos.x() / sx * m_bounds.height,
                         now_pos.y() / sy * m_bounds.height, GRAY);
                last_pos = now_pos;
            }
        }
        double x = pos.x() / sx * m_bounds.width;
        double y = pos.y() / sy * m_bounds.height;
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
        DrawText(("#" + std::to_string(ro->id())).c_str(), x, y + 32, 10, BLACK);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        auto mouse_x = GetMouseX();
        auto mouse_y = GetMouseY();
        auto mouse_pos = RealPosition(mouse_x, mouse_y);

        for (auto& ro : radar_objects) {
            RealPosition pos = ro->position();
            double x = pos.x() / sx * m_bounds.width;
            double y = pos.y() / sy * m_bounds.height;

            if (RealPosition(x, y).distance_from(mouse_pos) > 32) continue;

            m_signal_radar_object_clicked.call(ro->id());
        }
    }
}
