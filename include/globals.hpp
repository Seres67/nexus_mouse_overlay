#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <nexus/Nexus.h>

// handle to self hmodule
extern HMODULE self_module;
// addon definition
extern AddonDefinition addon_def;
// addon api
extern AddonAPI *api;

extern char addon_name[];

extern HWND game_handle;

extern POINT diff;
extern POINT last_pos;
extern POINT current_pos;

#endif // GLOBALS_HPP
