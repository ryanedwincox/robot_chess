cmake_minimum_required(VERSION 3.10)

# set the project name
project(perception)

find_package( OpenCV REQUIRED )
include_directories( src ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES 
    src/find_board.cpp
)

add_library(perception_lib ${SOURCE_FILES})

# add the executable
add_executable(perception src/main.cpp)

add_executable(perception_tests src/tests.cpp)

target_link_libraries( perception perception_lib ${OpenCV_LIBS} )

target_link_libraries( perception_tests perception_lib ${OpenCV_LIBS} )