cmake_minimum_required(VERSION 3.10)

project (engine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

IF(MINGW)
  set(ENV{SDL2DIR} "c:/SDL2-2.0.9")
  configure_file("dlls/SDL2.dll" "." COPYONLY)

  # SDL image libs
  configure_file("dlls/SDL2_image.dll" "." COPYONLY)
  configure_file("dlls/libjpeg-9.dll" "." COPYONLY)
  configure_file("dlls/libpng16-16.dll" "." COPYONLY)
  configure_file("dlls/libtiff-5.dll" "." COPYONLY)
  configure_file("dlls/libwebp-7.dll" "." COPYONLY)
  configure_file("dlls/zlib1.dll" "." COPYONLY)

  # SDL mixer libs
  configure_file("dlls/SDL2_mixer.dll" "." COPYONLY)
  configure_file("dlls/libFLAC-8.dll" "." COPYONLY)
  configure_file("dlls/libmodplug-1.dll" "." COPYONLY)
  configure_file("dlls/libmpg123-0.dll" "." COPYONLY)
  configure_file("dlls/libogg-0.dll" "." COPYONLY)
  configure_file("dlls/libopus-0.dll" "." COPYONLY)
  configure_file("dlls/libopusfile-0.dll" "." COPYONLY)
  configure_file("dlls/libvorbis-0.dll" "." COPYONLY)
  configure_file("dlls/libvorbisfile-3.dll" "." COPYONLY)

  configure_file("config.ini" "." COPYONLY)
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

IF(MINGW)
  # this increased main.exe by .1M. I have no idea what it included
  # was it libmain.dll?
  # TODO: figure out if this is needed
  set(CMAKE_EXE_LINKER_FLAGS " -static")
  target_link_libraries(main -static-libgcc -static-libstdc++)
ENDIF(MINGW)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
