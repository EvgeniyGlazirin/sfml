cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-5)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_subdirectory(ws2.1)
add_subdirectory(ws2.2)
add_subdirectory(ws2.3)