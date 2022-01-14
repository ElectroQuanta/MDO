cmake_minimum_required(VERSION 3.5)

project(LSApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set(CMAKE_PREFIX_PATH "/home/zmpl/Qt/5.13.2/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets VirtualKeyboard REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets VirtualKeyboard REQUIRED)

#find_package(pthread REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    normalwindow.h
    normalwindow.cpp
    normalwindow.ui
    interwindow.h
    interwindow.cpp
    interwindow.ui
    imgfiltwindow.h
    imgfiltwindow.cpp
    imgfiltwindow.ui
    sharwindow.h
    sharwindow.cpp
    sharwindow.ui
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
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::VirtualKeyboard pthread)

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
