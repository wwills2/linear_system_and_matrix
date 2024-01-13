cmake_minimum_required(VERSION 3.20)
project(Linear_System_Tool)

set(DEBUG ON) # compile with debugging

# required settings for QT compilation
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# project settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(THREADS_PREFER_PTHREAD_FLAG ON)

# project directories
set(GUI_DIR ./gui)
set(LIB_DIR ./lib)
set(LIBMATRIX_DIR ${LIB_DIR}/libmatrix)
set(TESTING_DIR test)
set(STATIC_LIBRARIES ${GMP_LIB} ${GMPXX_LIB} libmatrix)

add_definitions( -DWINDOW_NAME="Linear System Tool")

if (DEBUG)
    add_compile_options(-Wall -pedantic -g3)
else()
    add_compile_options(-Wall -pedantic -O3)
endif()

# declare and locate dependencies
find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_library(GMP_LIB NAMES gmp)
find_library(GMPXX_LIB NAMES gmpxx)

if(NOT GMP_LIB OR NOT GMPXX_LIB)
    message(FATAL_ERROR "GMP libraries not found. Please check your installation.")
endif()

# libmatrix compile config
add_library(libmatrix STATIC
        ${LIBMATRIX_DIR}/MatrixManager.h
        ${LIBMATRIX_DIR}/Matrix.h
        ${LIBMATRIX_DIR}/src/MatrixManager.cpp
        ${LIBMATRIX_DIR}/src/Matrix.cpp
)
target_include_directories(libmatrix PUBLIC ${LIBMATRIX_DIR})

# qt gui application compilation config
file(GLOB GUI_SOURCE ${GUI_DIR}/src/*.cpp)
file(GLOB GUI_HEADERS ${GUI_DIR}/include/*.h)
add_executable(qt_application gui/src/main.cpp ${GUI_HEADERS} ${GUI_SOURCE})
target_include_directories(qt_application PRIVATE ${GUI_DIR}/include lib)

# test program compilation config
add_executable(testLinearSystem
        ${TESTING_DIR}/TestLinearSystem.cpp
        ${TESTING_DIR}/TestLinearSystem.h
)
target_include_directories(testLinearSystem PRIVATE ${LIBMATRIX_DIR})

# linking settings
target_link_libraries(libmatrix ${GMP_LIB} ${GMPXX_LIB})
target_link_libraries(testLinearSystem ${STATIC_LIBRARIES} Threads::Threads)
target_link_libraries(qt_application ${STATIC_LIBRARIES} Threads::Threads Qt5::Widgets )
