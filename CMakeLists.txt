cmake_minimum_required(VERSION 3.7)
project(user_shell)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c user_shell.h user_shell.c)
add_executable(user_shell ${SOURCE_FILES})