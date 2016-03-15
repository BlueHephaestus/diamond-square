cmake_minimum_required(VERSION 2.8.11)

project(dsquare)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

# Tell CMake to create the helloworld executable
add_executable(dsquare WIN32 dsquare.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(dsquare Qt5::Widgets)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
