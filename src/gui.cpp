#include <globals.hpp>
#include <gui.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <settings.hpp>

void render_circle()
{
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 center = {window_size.x / 2 + window_pos.x, window_size.y / 2 + window_pos.y};
    ImGui::GetBackgroundDrawList()->AddCircle(center, 100, ImColor(255, 255, 255, 255));
}

void render_dot()
{
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 center = {window_size.x / 2 + window_pos.x + static_cast<float>(diff.x),
                     window_size.y / 2 + window_pos.y + static_cast<float>(diff.y)};
    // clamp to radius
    center.x = ImClamp(center.x, window_size.x / 2 + window_pos.x - 100, window_size.x / 2 + window_pos.x + 100);
    center.y = ImClamp(center.y, window_size.y / 2 + window_pos.y - 100, window_size.y / 2 + window_pos.y + 100);
    ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 5, ImColor(255, 0, 0, 255));
}

bool tmp_open = true;
void render_window()
{
    ImGui::SetNextWindowPos(ImVec2(300, 400), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;
    if (tmp_open && ImGui::Begin("Mouse Overlay##MouseOverlayMainWindow", &tmp_open, flags)) {
        render_circle();
        render_dot();
        ImGui::End();
    }
}
 
void render_options()
{
    if (ImGui::Checkbox("Enabled##MouseOverlayEnabled", &Settings::is_addon_enabled)) {
        Settings::json_settings[Settings::IS_ADDON_ENABLED] = Settings::is_addon_enabled;
        Settings::save(Settings::settings_path);
    }
}
