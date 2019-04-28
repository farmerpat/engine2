cmake_minimum_required(VERSION 3.10)

project (engine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

IF(MINGW)
  set(ENV{SDL2DIR} "c:/SDL2-2.0.9")
ENDIF(MINGW)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(
  SOURCES
  real_point.cpp
  util.cpp
  game_manager.cpp
  path.cpp
  controller.cpp
  path_controller.cpp
  function_controller.cpp
  parametric_function_controller.cpp
  sine_function_of_x_controller.cpp
  archimedes_spiral_parametric_function_controller.cpp
  ellipse_parametric_function_controller.cpp
  involute_of_a_circle_parametric_function_controller.cpp
  sprite.cpp
  hero_controller.cpp
  hero_sprite.cpp
  enemy_sprite.cpp
  textured_sprite.cpp
  primitive_sprite.cpp
  rectangular_primitive_sprite.cpp
  level.cpp
)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(main SDL2::Main SDL2::Image)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
