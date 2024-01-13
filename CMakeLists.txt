cmake_minimum_required(VERSION 3.20)
project(matrix_operations)

set(DEBUG ON) # compile with debugging

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(STATIC_LIB_DIR /usr/lib/x86_64-linux-gnu) # set to directory where static libaries are located
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(GUI_DIR gui)
set(LIBMATRIX_DIR libmatrix)
set(TESTING_DIR test)

file(GLOB GUI_SOURCE ${GUI_DIR}/src/*.cpp)
file(GLOB GUI_HEADERS ${GUI_DIR}/include/*.h)

add_definitions( -DWINDOW_NAME="Linear System Tool")

if (DEBUG)
    add_compile_options(-Wall -pedantic -g3)
else()
    add_compile_options(-Wall -pedantic -O3)
endif()


find_library(GMP_LIB NAMES gmp)
find_library(GMPXX_LIB NAMES gmpxx)

if(NOT GMP_LIB OR NOT GMPXX_LIB)
    message(FATAL_ERROR "GMP libraries not found. Please check your installation.")
endif()

find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(libmatrix STATIC
        ${LIBMATRIX_DIR}/MatrixManager.h
        ${LIBMATRIX_DIR}/Matrix.h
        ${LIBMATRIX_DIR}/src/MatrixManager.cpp
        ${LIBMATRIX_DIR}/src/Matrix.cpp
)

set(STATIC_LIBRARIES
        ${GMP_LIB}
        ${GMPXX_LIB}
        libmatrix
)

add_executable(qt_application
        main.cpp
        ${GUI_HEADERS}
        ${GUI_SOURCE}
)

add_executable(testLinearSystem
        ${TESTING_DIR}/TestLinearSystem.cpp
        ${TESTING_DIR}/TestLinearSystem.h
)

target_link_libraries(libmatrix ${GMP_LIB} ${GMPXX_LIB})
target_link_libraries(testLinearSystem ${STATIC_LIBRARIES} Threads::Threads)
target_link_libraries(qt_application ${STATIC_LIBRARIES} Threads::Threads Qt5::Widgets )

