cmake_minimum_required(VERSION 2.8.11)

project(QR-light)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# support C++11
set (CMAKE_CXX_STANDARD 11)

# sub folders
add_subdirectory(util)
add_subdirectory(gui)

include_directories(${CMAKE_SOURCE_DIR})

#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

