cmake_minimum_required(VERSION 3.10)

project (engine)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sdl2)

IF(MINGW)
  set(ENV{SDL2DIR} "c:/SDL2-2.0.9")
  configure_file("../dlls/SDL2.dll" "." COPYONLY)

  # SDL image libs
  configure_file("../dlls/SDL2_image.dll" "." COPYONLY)
  configure_file("../dlls/libjpeg-9.dll" "." COPYONLY)
  configure_file("../dlls/libpng16-16.dll" "." COPYONLY)
  configure_file("../dlls/libtiff-5.dll" "." COPYONLY)
  configure_file("../dlls/libwebp-7.dll" "." COPYONLY)
  configure_file("../dlls/zlib1.dll" "." COPYONLY)

  # SDL mixer libs
  configure_file("../dlls/SDL2_mixer.dll" "." COPYONLY)
  configure_file("../dlls/libFLAC-8.dll" "." COPYONLY)
  configure_file("../dlls/libmodplug-1.dll" "." COPYONLY)
  configure_file("../dlls/libmpg123-0.dll" "." COPYONLY)
  configure_file("../dlls/libogg-0.dll" "." COPYONLY)
  configure_file("../dlls/libopus-0.dll" "." COPYONLY)
  configure_file("../dlls/libopusfile-0.dll" "." COPYONLY)
  configure_file("../dlls/libvorbis-0.dll" "." COPYONLY)
  configure_file("../dlls/libvorbisfile-3.dll" "." COPYONLY)

  # SDL ttf libs
  configure_file("../dlls/SDL2_ttf.dll" "." COPYONLY)
  configure_file("../dlls/libfreetype-6.dll" "." COPYONLY)

ENDIF(MINGW)

file(GLOB ASSETS_DIR "assets/*")
file(COPY ${ASSETS_DIR} DESTINATION "./assets")
configure_file("config.ini" "." COPYONLY)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(
  SOURCES
  ../src/include/real_point.hpp
  ../src/real_point.cpp
  ../src/include/util.hpp
  ../src/util.cpp
  ../src/include/config.hpp
  ../src/config.cpp
  ../src/include/dict.hpp
  ../src/dict.cpp
  ../src/include/game_manager.hpp
  ../src/game_manager.cpp
  ../src/include/path.hpp
  ../src/path.cpp
  ../src/include/controller.hpp
  ../src/controller.cpp
  ../src/include/sprite.hpp
  ../src/sprite.cpp
  src/piece.cpp
  ../src/include/screen_matrix.hpp
  ../src/screen_matrix.cpp
  ../src/include/matrix_of_sprites.hpp
  ../src/matrix_of_sprites.cpp
  ../src/include/textured_sprite.hpp
  ../src/textured_sprite.cpp
  ../src/include/primitive_sprite.hpp
  ../src/primitive_sprite.cpp
  ../src/include/rectangular_primitive_sprite.hpp
  ../src/rectangular_primitive_sprite.cpp
  ../src/include/level.hpp
  ../src/level.cpp
  ../src/include/ui_text.hpp
  ../src/ui_text.cpp
  ../src/include/ui_static_text_box.hpp
  ../src/ui_static_text_box.cpp
  ../src/include/ui_dynamic_text_box.hpp
  ../src/ui_dynamic_text_box.cpp
  ../src/include/score_text_box.hpp
  ../src/score_text_box.cpp
  src/piece_controller.cpp
  src/levels/puzzle_level.cpp
  ../src/include/level_controller.hpp
  ../src/level_controller.cpp
  src/puzzle_level_controller.cpp
  src/o_piece.cpp
  src/puzzle_background_hole.cpp
  src/puzzle_background_hole_controller.cpp
  src/death_timer_puzzle_background_hole_controller.cpp
  src/oscillate_right_left_puzzle_background_hole_controller.cpp
  src/falling_piece_puzzle_background_hole_controller.cpp

)

add_executable(main src/main.cpp ${SOURCES})

target_include_directories(main PUBLIC
  #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src/include/>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src/>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>
  #${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_link_libraries(main SDL2::Main SDL2::Image SDL2::Mixer SDL2::TTF)

IF(MINGW)
  # this increased main.exe by .1M. I have no idea what it included
  # was it libmain.dll?
  # TODO: figure out if this is needed
  set(CMAKE_EXE_LINKER_FLAGS " -static")
  target_link_libraries(main -static-libgcc -static-libstdc++)
ENDIF(MINGW)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_C_FLAGS_DEBUG}")
