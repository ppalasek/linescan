CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project (LineScan)

find_package (OpenCV REQUIRED)

add_executable(lineScan linescan.cpp)
target_link_libraries (lineScan ${OpenCV_LIBS})
