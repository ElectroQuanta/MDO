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
#find_package(OpenCV REQUIRED PATHS "/usr/local/lib/")
#include_directories(${OpenCV_INCLUDE_DIRS})

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# ====================== Imagemagick
find_program(MAGICK_CONFIG "Magick++-config")
execute_process(COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
# Remove trailing whitespace (CMAKE warns about this)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)
# Append all flags to CMAKE_CXX_FLAGS
#set(CMAKE_CXX_FLAGS "${CMAKE_CPP_FLAGS} -std=c++11 ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")

message("LDFlags: ${MAGICK_LD_FLAGS}")

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})

# ============================ Qt
set(CMAKE_PREFIX_PATH "/home/zmpl/Qt/5.13.2/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets VirtualKeyboard Multimedia MultimediaWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets VirtualKeyboard Multimedia MultimediaWidgets REQUIRED)

#find_package(pthread REQUIRED)

#set(SRC_FILES )

# ================ TWITCURL
set(TWITCURL_LIB twitcurl)

file(GLOB RESOURCE_FILES *.qrc)
file(GLOB SRC_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

#message(RESOURCE_FILES: ${RESOURCE_FILES})
#message(SRC_FILES: ${SRC_FILES})
#message(HEADER_FILES: ${HEADER_FILES})

set(MQUEUE_LD_FLAGS -lrt)

set(PROJECT_SOURCES
  main.cpp
  # main window
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  resources.qrc
  # normal window
  normalwindow.h
  normalwindow.cpp
  normalwindow.ui
  # interaction window
  interwindow.h
  interwindow.cpp
  interwindow.ui
  # imgfilter window
  imgfiltwindow.h
  imgfiltwindow.cpp
  imgfiltwindow.ui
  # shar window
  sharwindow.h
  sharwindow.cpp
  sharwindow.ui
  # imgfilter
  imgfilter_defs.h
  imgfilter.h
  imgfilter.cpp
  # post
  post.h
  post.cpp
  #pEvent
  pEvent.h
  pEvent.cpp
  #Ad
  ad.h
  ad.cpp
  # Fragrance
  frag.h
  frag.cpp
  fragManager.h
  fragManager.cpp
  fragDiffuser.h
  fragDiffuser.cpp
  # Device Drivers
  ddDigitalOut.h
  ddDigitalOut.cpp
  # Message queue
  msgqueue.h
  msgqueue.cpp
#${HEADER_FILES}
#${SRC_FILES}
#${RESOURCES_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# CMAKE IS CASE SENSITIVE
# src: https://stackoverflow.com/a/60693001/17836786
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::VirtualKeyboard Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets pthread ${TWITCURL_LIB} ${MQUEUE_LD_FLAGS} ${MAGICK_LD_FLAGS} ${ImageMagick_LIBRARIES})

# my_tgt can be an executable, library, or module.
#target_link_options(${PROJECT_NAME} PRIVATE "LINKER:-lopencv_core -lopencv_video -lopencv_videoio")

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
