cmake_minimum_required(VERSION 2.8)

project(VOIDRAY)

add_executable(VOIDRAY 
				util/Vector3.hpp util/Vector3.cpp
				util/Transform.hpp util/Transform.cpp
				RenderManager.hpp RenderManager.cpp
				Timer.hpp Timer.cpp
				SteeringBehaviors.hpp SteeringBehaviors.cpp				
				BaseEntity.hpp BaseEntity.cpp 
				Sprite.hpp Sprite.cpp
				Ship.hpp Ship.cpp				
				ChildSprite.hpp ChildSprite.cpp
				Target.hpp Target.cpp
				GameController.hpp GameController.cpp
				main.cpp)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL_image_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})

target_link_libraries(VOIDRAY SDL ${OPENGL_LIBRARIES} SDL_image)
