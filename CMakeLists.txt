cmake_minimum_required(VERSION 3.10)

project (engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

set(
  SOURCES
  util.cpp
  game_manager.cpp
  path.cpp
  controller.cpp
  path_controller.cpp
  sprite.cpp
  hero_controller.cpp
  hero_sprite.cpp
  textured_sprite.cpp
  primitive_sprite.cpp
  rectangular_primitive_sprite.cpp
  level.cpp
)

add_executable(main main.cpp ${SOURCES})
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})
