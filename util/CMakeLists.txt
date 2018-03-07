cmake_minimum_required(VERSION 2.8.11)
aux_source_directory(detail util_SRC)
include_directories(${CMAKE_SOURCE_DIR})
add_library(util ${util_SRC})
