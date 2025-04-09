# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

message("Zephyr base is: $ENV{ZEPHYR_BASE}")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(own_project)

add_subdirectory(semaphores_and_mutexes_exercise)
add_subdirectory(threads_exercise)

target_sources(app PRIVATE src/main.c)
target_link_libraries(app PRIVATE threads_exercise_lib)

target_link_libraries(app PRIVATE sem_and_mutexes_exercise_lib)
target_compile_options(app PRIVATE -Os -g)
