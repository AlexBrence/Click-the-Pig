cmake_minimum_required(VERSION 3.20)
project(Click-the-Pig)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/usr/include/SFML/include")
set(SFML_LIBRARY_DIR "/usr/lib")
set(SFML_DIR "/usr/lib/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(Click_the_Pig main.cpp Game.cpp Game.h)
target_link_libraries (Click_the_Pig sfml-graphics sfml-window sfml-system)
