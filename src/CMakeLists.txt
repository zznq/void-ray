cmake_minimum_required(VERSION 2.8)

project(VOIDRAY)

add_subdirectory(util)

include_directories(${VOIDRAY_SOURCE_DIR}/util)

link_directories(${VOIDRAY_BINARY_DIR}/util)

add_executable(VOIDRAY RenderManager.cpp Entity.hpp SteeringBehaviors.cpp Sprite.hpp Ship.cpp GameController.cpp main.cpp)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL_image_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

target_link_libraries(VOIDRAY SDL ${OPENGL_LIBRARIES} SDL_image)
