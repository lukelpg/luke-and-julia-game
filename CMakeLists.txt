cmake_minimum_required(VERSION 3.14)
project(luke_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src/game)
add_subdirectory(src/input)
add_subdirectory(src/physics)
add_subdirectory(src/render)
add_subdirectory(src/sprite)
add_subdirectory(src/world)

# target_include_directories(game PUBLIC src/game)
# target_include_directories(input PUBLIC src/input)
# target_include_directories(physics PUBLIC src/physics)
# target_include_directories(render PUBLIC src/render)
# target_include_directories(sprite PUBLIC src/sprite)
# target_include_directories(world PUBLIC src/world)

add_executable(luke_game src/main.cpp)

target_link_libraries(
	luke_game 
	SDL2 
	SDL2_image 
	SDL2_ttf 
	SDL2_mixer
)

target_link_libraries(
	luke_game
	game
	input
	physics
	render
	sprite
	world
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})