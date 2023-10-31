cmake_minimum_required(VERSION 3.20)
project(matrix_operations)

set(DEBUG ON) # compile with debugging

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(STATIC_LIB_DIR /usr/lib/x86_64-linux-gnu) # set to directory where static libaries are located
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(GUI_DIR gui)
set(TESTING_DIR test)
file(GLOB GUI_SOURCE ${GUI_DIR}/*.cpp)
file(GLOB GUI_HEADERS ${GUI_DIR}*.h)

add_definitions( -DWINDOW_NAME="Linear System Tool")

if (DEBUG)
    add_compile_options(-Wall -pedantic -g3)
else()
    add_compile_options(-Wall -pedantic -O3)
endif()

find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(STATIC_LIBRARIES
        ${STATIC_LIB_DIR}/libgmpxx.a
        ${STATIC_LIB_DIR}/libgmp.a
        Threads::Threads
        Qt5::Widgets)

add_executable(qt_application
        main.cpp
        MatrixManager.h
        MatrixManager.cpp
        Matrix.cpp
        Matrix.h
        ${GUI_SOURCE}
        ${GUI_HEADERS}
        gui/IntfDataEntry.cpp
        gui/IntfDataEntry.h
)

add_executable(testLinearSystem
        ${TESTING_DIR}/TestLinearSystem.cpp
        ${TESTING_DIR}/TestLinearSystem.h
        MatrixManager.cpp
        MatrixManager.h
        Matrix.cpp
        Matrix.h)

target_link_libraries(testLinearSystem ${STATIC_LIBRARIES})
target_link_libraries(qt_application ${STATIC_LIBRARIES})

