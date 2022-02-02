cmake_minimum_required(VERSION 3.5)

project(opencvMagick)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_program(MAGICK_CONFIG "Magick++-config")

execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
# Remove trailing whitespace (CMAKE warns about this)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)
# Append all flags to CMAKE_CXX_FLAGS
#set(CMAKE_CXX_FLAGS "${CMAKE_CPP_FLAGS} -std=c++11 ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")

message("LDFlags: ${MAGICK_LD_FLAGS}")


# ======================== OPENCV
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

set(SOURCE_FILES ${PROJECT_NAME}.cpp)

# ImageMagick++
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${MAGICK_LD_FLAGS} ${ImageMagick_LIBRARIES})
