cmake_minimum_required(VERSION 3.10.0)
project(homework VERSION 0.1.0)

# find required opencv
find_package(OpenCV REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(homography homography/homography.cpp)
add_executable(calibration calibration/calibration.cpp)

# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# opencv libraries
target_link_libraries(homography ${OpenCV_LIBS})
target_link_libraries(calibration ${OpenCV_LIBS})