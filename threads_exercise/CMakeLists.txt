add_library(threads_exercise_lib STATIC threads.c threads.h)
target_include_directories(threads_exercise_lib PUBLIC .)
target_link_libraries(threads_exercise_lib PRIVATE app sem_and_mutexes_exercise_lib kernel)