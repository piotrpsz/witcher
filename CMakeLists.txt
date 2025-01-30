cmake_minimum_required(VERSION 3.30)
project(witcher)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-static)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-static)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
message("-------------------------------------------------------")
message(STATUS "SDL3 version: ${SDL3_VERSION}")
message(STATUS "SDL3_ttf version: ${SDL3_ttf_VERSION}")
message(STATUS "SDL3_image version: ${SDL3_image_VERSION}")
message("-------------------------------------------------------")

set(CMAKE_CXX_STANDARD 23)

add_library(witcher
        point.h
        dummy.cpp
        dummy.h)


target_link_libraries(witcher PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
)
