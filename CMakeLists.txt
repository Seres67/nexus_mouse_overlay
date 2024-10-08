cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
if (UNIX)
    set(CMAKE_SYSTEM_NAME Windows)
    set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

    # cross compilers to use for C, C++ and Fortran
    set(PRIVATE_MINGW_PATH /usr/sbin)
    set(CMAKE_C_COMPILER ${PRIVATE_MINGW_PATH}/${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${PRIVATE_MINGW_PATH}/${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_Fortran_COMPILER ${PRIVATE_MINGW_PATH}/${TOOLCHAIN_PREFIX}-gfortran)
    set(CMAKE_RC_COMPILER /usr/bin/${TOOLCHAIN_PREFIX}-windres)

    # target environment on the build host system
    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

    # modify default behavior of FIND_XXX() commands
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -O2")
endif ()

project(nexus_mouse_overlay)

include_directories(include)

# load imgui as a cmake project
add_subdirectory(src/imgui)

add_library(nexus_mouse_overlay SHARED src/main.cpp src/globals.cpp src/gui.cpp src/settings.cpp)
target_link_libraries(nexus_mouse_overlay PRIVATE imgui)
set_property(TARGET nexus_mouse_overlay PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# copy dll to game directory
add_custom_command(TARGET nexus_mouse_overlay
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:nexus_mouse_overlay>
        "C:\\Games\\Guild Wars 2\\addons\\nexus_mouse_overlay.dll.update"
        COMMENT "Copying nexus_mouse_overlay.dll.update to game directory"
)
