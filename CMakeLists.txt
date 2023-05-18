cmake_minimum_required(VERSION 3.14)
project(luke_game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(luke_game 
	src/main.cpp
	src/background.cpp
	src/sprite.cpp
	src/npc.cpp
	src/player.cpp
	src/grass_block.cpp
	src/input_state.cpp
)

target_include_directories(luke_game 
    PRIVATE 
    include
)

target_link_libraries(luke_game SDL2 SDL2_image SDL2_ttf SDL2_mixer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})