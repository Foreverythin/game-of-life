cmake_minimum_required(VERSION 3.22)
project(game_of_life C)

include_directories("/opt/homebrew/Cellar/sdl2/2.0.20/include")

set(CMAKE_C_STANDARD 11)

add_executable(game_of_life
        main.c)
