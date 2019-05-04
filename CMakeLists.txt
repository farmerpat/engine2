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
find_package(SDL2_mixer REQUIRED)

set(
  SOURCES
  real_point.cpp
  util.cpp
  config.cpp
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
  piece.cpp
  hero_controller.cpp
  hero_sprite.cpp
  enemy_sprite.cpp
  enemy_sprite_ellipsis.cpp
  enemy_sprite_sine.cpp
  enemy_bullet_sprite.cpp
  enemy_bullet_controller.cpp
  shoot_if_hero_in_range_ai_controller.cpp
  player_bullet_controller.cpp
  player_bullet_sprite.cpp
  textured_sprite.cpp
  primitive_sprite.cpp
  rectangular_primitive_sprite.cpp
  level.cpp
)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(main SDL2::Main SDL2::Image SDL2::Mixer)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
