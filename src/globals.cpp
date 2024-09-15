#include <globals.hpp>

HMODULE self_module = nullptr;
AddonDefinition addon_def{};
AddonAPI *api = nullptr;
char addon_name[] = "Mouse Overlay";
HWND game_handle = nullptr;
POINT diff;
POINT last_pos;
POINT current_pos;