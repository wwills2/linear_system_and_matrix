cmake_minimum_required(VERSION 3.20)
project(matrix_operations)

set(DEBUG OFF) # compile with debugging

set(CMAKE_CXX_STANDARD 14)
set(STATIC_LIB_DIR "/usr/lib/x86_64-linux-gnu") # set to directory where static libaries are located
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(TESTING_DIR test)

if (DEBUG)
    add_compile_options(-Wall -pedantic -g3)
else()
    add_compile_options(-Wall -pedantic -O3)
endif()

find_package(Threads REQUIRED)
set(STATIC_LIBRARIES "${STATIC_LIB_DIR}/libgmpxx.a" "${STATIC_LIB_DIR}/libgmp.a" Threads::Threads)

add_executable(matrix_operations main.cpp LinearSystem.h LinearSystem.cpp Matrix.cpp Matrix.h)

add_executable(testLinearSystem LinearSystem.cpp LinearSystem.h ${TESTING_DIR}/TestLinearSystem.cpp
        ${TESTING_DIR}/TestLinearSystem.h Matrix.cpp Matrix.h)

target_link_libraries(testLinearSystem ${STATIC_LIBRARIES})
target_link_libraries(matrix_operations ${STATIC_LIBRARIES})

