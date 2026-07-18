cmake_minimum_required(VERSION 3.15)
project(GameEngineDev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# SOURCES (belangrijk: correct pad)
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/src/glad.c
    )

add_executable(GameEngineDev ${SOURCES})

# HEADERS
target_include_directories(GameEngineDev PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/Dependencies/SDL/include
    ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/include
    ${CMAKE_SOURCE_DIR}/Dependencies/stb
)

# SDL LIBS
target_link_directories(GameEngineDev PRIVATE
    ${CMAKE_SOURCE_DIR}/Dependencies/SDL/lib/x64
)

target_link_libraries(GameEngineDev
    SDL2
    SDL2main
    opengl32
)
