cmake_minimum_required(VERSION 2.8)
project(dagame)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(SOURCE_FILES main.cpp SDL.cpp Input.cpp Timer.cpp)

add_subdirectory(Characters)
add_subdirectory(Environment)
add_subdirectory(Information)

add_executable(dagame ${SOURCE_FILES})
target_link_libraries(dagame ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} Characters Environment Information)