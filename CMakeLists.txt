cmake_minimum_required(VERSION 3.23)
project(example C)
add_executable(example main.c)

# Статическая библиотека
add_library(example_list STATIC list.c)
target_link_libraries(example PRIVATE example_list)

# Динамическая библиотека
add_library(example_password SHARED password.c)