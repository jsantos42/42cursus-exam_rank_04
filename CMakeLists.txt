cmake_minimum_required(VERSION 3.21)
get_filename_component(ProjectDir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ProjectDir})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
file(GLOB SRC *.c)
file(GLOB INC *.h)

add_executable(${ProjectDir} ${SRC} ${INC})
