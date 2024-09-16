#define NOMINMAX
#include <globals.hpp>
#include <gui.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <settings.hpp>

void render_circle()
{
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_pos = ImGui::GetWindowPos();
    float circle_radius = 80;
    ImVec2 circle_center = {window_size.x / 2 + window_pos.x, window_size.y / 2 + window_pos.y};
    ImVec2 dot_center = {window_size.x / 2 + window_pos.x + static_cast<float>(diff.x),
                         window_size.y / 2 + window_pos.y + static_cast<float>(diff.y)};
    bool inside =
        sqrt(pow(circle_center.x - dot_center.x, 2) + pow(circle_center.y - dot_center.y, 2)) <= circle_radius;
    if (!inside) {
        dot_center.x = dot_center.x - circle_center.x;
        dot_center.y = dot_center.y - circle_center.y;
        auto angle = atan2(dot_center.y, dot_center.x);
        dot_center.x = cos(angle) * circle_radius + circle_center.x;
        dot_center.y = sin(angle) * circle_radius + circle_center.y;
    }
    ImGui::GetBackgroundDrawList()->AddCircle(circle_center, circle_radius, ImColor(255, 255, 255, 255));
    ImGui::GetBackgroundDrawList()->AddCircleFilled(dot_center, 5, ImColor(255, 0, 0, 255));
}

bool tmp_open = true;
void render_window()
{
    ImGui::SetNextWindowPos(ImVec2(160, 160), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground |
                             ImGuiWindowFlags_NoResize;
    if (Settings::lock_position) {
        flags |= ImGuiWindowFlags_NoMove;
    }
    if (tmp_open && ImGui::Begin("Mouse Overlay##MouseOverlayMainWindow", &tmp_open, flags)) {
        render_circle();
        ImGui::End();
    }
}
 
void render_options()
{
    if (ImGui::Checkbox("Lock Position##MouseOverlayLockPosition", &Settings::lock_position)) {
        Settings::json_settings[Settings::LOCK_POSITION] = Settings::lock_position;
        Settings::save(Settings::settings_path);
    }
}
