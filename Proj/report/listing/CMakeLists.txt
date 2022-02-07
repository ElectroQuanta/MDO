cmake_minimum_required(VERSION 3.5)

project(LSApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================== OPENCV
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
find_package(OpenCV REQUIRED PATHS "/usr/local/lib/")
include_directories(${OpenCV_INCLUDE_DIRS})

# ====================== Imagemagick
find_program(MAGICK_CONFIG "Magick++-config")
execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
# Remove trailing whitespace (CMAKE warns about this)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})

# ============================ Qt
set(CMAKE_PREFIX_PATH "/home/zmpl/Qt/5.13.2/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets VirtualKeyboard Multimedia MultimediaWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets VirtualKeyboard Multimedia MultimediaWidgets REQUIRED)

# ================ TWITCURL
set(TWITCURL_LIB twitcurl)

# SRC files
file(GLOB RESOURCE_FILES *.qrc)
file(GLOB SRC_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

# Message Queue flags
set(MQUEUE_LD_FLAGS -lrt)

# set project sources
set(PROJECT_SOURCES
${HEADER_FILES}
${SRC_FILES}
${RESOURCES_FILES}
)

# Add executable
add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  )

# Link to libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${OpenCV_LIBS}
  Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::VirtualKeyboard Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets pthread ${TWITCURL_LIB} ${MQUEUE_LD_FLAGS} ${MAGICK_LD_FLAGS} ${ImageMagick_LIBRARIES})
