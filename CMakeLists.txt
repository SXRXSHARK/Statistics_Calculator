cmake_minimum_required(VERSION 3.10)
project(Calculator)

# Specify the installation paths for OpenCV and Tesseract
set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.1/share/opencv4")  # Update as per your installation
set(Tesseract_DIR "/usr/local/Cellar/tesseract/5.5.0/share/cmake/tesseract")  # Update with correct path

# Find required packages
find_package(OpenCV REQUIRED)
find_package(Tesseract REQUIRED CONFIG)

# Add the executable
add_executable(Calculator main.cpp
        funcs.h
        funcs.cpp
        main.cpp
        funcs.cpp
        funcs.h
        funcs.h
)

# Include directories and link libraries
target_include_directories(Calculator PRIVATE ${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})
target_link_libraries(Calculator PRIVATE ${OpenCV_LIBS} Tesseract::libtesseract)

message(STATUS "OpenCV Path: ${OpenCV_DIR}")
message(STATUS "Tesseract Path: ${Tesseract_DIR}")

set(ENV{TESSDATA_PREFIX} "/users/slayra/desktop/CLionProjects/Calculator/cmake-build-debug/tesseract/")




