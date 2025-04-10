cmake_minimum_required(VERSION 3.30)
project(witcher)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
message("-------------------------------------------------------")
message(STATUS "SDL3 version: ${SDL3_VERSION}")
message(STATUS "SDL3_ttf version: ${SDL3_ttf_VERSION}")
message(STATUS "SDL3_image version: ${SDL3_image_VERSION}")
message("-------------------------------------------------------")

set(CMAKE_CXX_STANDARD 23)

add_library(witcher
        types.h
        widgets/widget/widget.cpp
        widgets/widget/widget.h
        widgets/widget/object.cpp
        widgets/widget/object.h
        widgets/button/button.cpp
        widgets/button/button.h
        widgets/button/action.h
        layout.h
        witcher.hpp
        mouse_event.h
        font.cpp
        font.h
        font_store.h
        text.cpp
        text.h
        thema.h
        helpers/draw.cpp
        helpers/draw.h
        window.cpp
        window.h
        application.cpp
        application.h
        sdl_event.h
        sdl_event.cpp
        layout.cpp
        menu/menu_bar.cpp
        menu/menu_bar.h
        menu/menu_button.cpp
        menu/menu_button.h
        event/user_event.h
        event/event_controller.h
        menu/menu.cpp
        menu/menu.h
        widgets/dialog/dialog.cpp
        widgets/dialog/dialog.h)

add_subdirectory(toolbox)

target_link_libraries(witcher PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        toolbox
)
