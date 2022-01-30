cmake_minimum_required(VERSION 3.5)

project(closedfist LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src: http://amin-ahmadi.com/2018/02/23/how-to-use-cmake-with-qt5-and-opencv-3-projects/
# Specify OpenCV folder, and take care of dependenciesand includes
#set(OpenCV_DIR "path_to_folder_of_OpenCVConfig.cmake_file")
set(OpenCV_DIR "usr/local/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
