add_library(sem_and_mutexes_exercise_lib STATIC sem_and_mut.c sem_and_mut.h)
target_include_directories(sem_and_mutexes_exercise_lib PUBLIC .)
target_link_libraries(sem_and_mutexes_exercise_lib PRIVATE app)