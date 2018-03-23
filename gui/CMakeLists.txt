cmake_minimum_required(VERSION 2.8.11)

# Find the QtWidgets library
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Core)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# add include
include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# ui file
QT5_WRAP_UI(example_UIS ui/mainframe.ui)
QT5_WRAP_UI(example_UIS ui/OptionPanel.ui)

# find detail
aux_source_directory(detail qtgui_SRC)

# add executable
add_executable(Qt-Light ${qtgui_SRC} ${example_UIS} rc/mainframe.qrc rc/mainframe.rc)

# link libraries
target_link_libraries(Qt-Light PRIVATE Qt5::Widgets util)


