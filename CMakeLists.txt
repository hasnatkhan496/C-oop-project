cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(chess
    src/main.cpp
    src/game.cpp
    src/board.cpp
    src/pieces.cpp
)

target_include_directories(chess PRIVATE "C:/Users/Dell/Desktop/github/raylib-6.0_win64_mingw-w64/include")
target_link_directories(chess PRIVATE "C:/Users/Dell/Desktop/github/raylib-6.0_win64_mingw-w64/lib")
target_link_libraries(chess raylib opengl32 gdi32 winmm)