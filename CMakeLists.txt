cmake_minimum_required(VERSION 3.16)
project(trabSO C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE) # nao compilar exemplos do raylib

add_subdirectory(raylib-master) # adiciona a pasta do raylib

include_directories(include)

add_executable(trabSO src/main.cpp
        src/jogo.cpp
        src/peixes.cpp
        src/render.cpp
        include/render.h
        include/jogo.h
        include/peixes.h)

target_link_libraries(trabSO raylib) # linka com o target 'raylib'

target_include_directories(trabSO PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/raylib-master/src) # inclui headers do raylib