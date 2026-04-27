cmake_minimum_required(VERSION 3.10)
project(spacesim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SDL2 core package
find_package(SDL2 REQUIRED)

# Find the SDL2_ttf package
find_package(SDL2_ttf REQUIRED)

include_directories(include)

set(SOURCES 
    src/main.cpp 
    src/Renderer.cpp 
    src/SpaceObject.cpp
    src/Input.cpp
)

add_executable(spacesim ${SOURCES})

# Link both SDL2 and SDL2_ttf to your executable
target_link_libraries(spacesim 
    SDL2::SDL2 
    SDL2_ttf::SDL2_ttf
)
