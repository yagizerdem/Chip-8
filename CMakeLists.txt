cmake_minimum_required(VERSION 3.28.3)
project(Chip_8 C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(Chip_8 ${SDL2_INCLUDE_DIRS})

add_executable(Chip_8 main.c
        chip8.h
        chip8.c
        instruction.h
        instruction.c
        emulator.h
        emulator.c
        screen.c
        screen.h)

target_include_directories(Chip_8 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Chip_8 PRIVATE ${SDL2_LIBRARIES})