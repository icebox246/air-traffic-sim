#include "RadarView.hpp"

#include <raygui.h>

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

    for (size_t i = 0; i < (size_t)RadarObjectKind::CountKinds; i++)
        SetTextureFilter(m_icon_textures[i], TEXTURE_FILTER_BILINEAR);
}

void RadarView::unload_textures() {
    for (size_t i = 0; i < (size_t)RadarObjectKind::CountKinds; i++)
        UnloadTexture(m_icon_textures[i]);
}

void RadarView::process() {
    process_drawing();
    process_mouse_clicking();
}

void RadarView::process_drawing() {
    auto& radar_objects = m_radar_system.radar_objects();
    auto sx = m_radar_system.terrain().width();
    auto sy = m_radar_system.terrain().height();

    BeginScissorMode(m_bounds.x, m_bounds.y, m_bounds.width, m_bounds.height);
    for (auto& ro : radar_objects) {
        RealPosition pos = ro->position();
        float texture_scale = ro->radius() + 0.05;
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
        Vector2 position;
        position.x = x;
        position.y = y + 20;
        DrawTextEx(GuiGetFont(), ("#" + std::to_string(ro->id())).c_str(),
                   position, GuiGetStyle(DEFAULT, TEXT_SIZE),
                   GuiGetStyle(DEFAULT, TEXT_SPACING), BLACK);
        position.y += GuiGetStyle(DEFAULT, TEXT_SIZE) +
                      GuiGetStyle(DEFAULT, TEXT_SPACING);
        DrawTextEx(
            GuiGetFont(),
            ("^" + std::to_string((int)ro->upper_altitude_bound_after(0)))
                .c_str(),
            position, GuiGetStyle(DEFAULT, TEXT_SIZE),
            GuiGetStyle(DEFAULT, TEXT_SPACING), BLACK);
    }
    EndScissorMode();
}

void RadarView::process_mouse_clicking() {
    auto& radar_objects = m_radar_system.radar_objects();
    auto sx = m_radar_system.terrain().width();
    auto sy = m_radar_system.terrain().height();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        auto mouse_x = GetMouseX();
        auto mouse_y = GetMouseY();
        auto mouse_pos = RealPosition(mouse_x, mouse_y);

        for (auto& ro : radar_objects) {
            RealPosition pos = ro->position();
            double x = pos.x() / sx * m_bounds.width;
            double y = pos.y() / sy * m_bounds.height;

            if (RealPosition(x, y).distance_from(mouse_pos) > 20) continue;

            m_signal_radar_object_clicked.call(ro->id());
        }
    }
}
