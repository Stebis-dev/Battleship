# Setthe minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version

# To build
# cmake -G "MinGW Makefiles" -S . -B ./build
cmake_minimum_required(VERSION "3.19.6")

project("BattleShip")

set(SOURCES
    src/main.cpp
    src/coordinates.cpp
    src/states.cpp
    src/ship.cpp
    src/map.cpp
    src/cell.cpp)

add_executable("BattleShip" ${SOURCES})

target_include_directories("BattleShip"
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)