# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

message("Zephyr base is: $ENV{ZEPHYR_BASE}")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
# set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker.ld")
# set_target_properties(app PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
project(own_project)
target_sources(app PRIVATE src/main.c)

add_subdirectory(semaphores_and_mutexes_exercise)
target_link_libraries(app PRIVATE sem_and_mutexes_exercise_lib)

add_subdirectory(threads_exercise)
target_link_libraries(app PRIVATE threads_exercise_lib kernel)

target_compile_options(app PRIVATE -Og)
