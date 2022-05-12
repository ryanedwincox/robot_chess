cmake_minimum_required(VERSION 3.10)

# set the project name
project(perception)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# add the executable
add_executable(perception src/main.cpp)

target_link_libraries( perception ${OpenCV_LIBS} )