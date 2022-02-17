cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
# External toolchain( it must be set before project() )
set(CROSS_COMPILE "RASP4_64")
#set(CROSS_COMPILE "Desktop")
if(CROSS_COMPILE STREQUAL "RASP4_64")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain/rasptoolchain.cmake)
  message(${CMAKE_TOOLCHAIN_FILE})
endif()

project(testCmake LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src: http://amin-ahmadi.com/2018/02/23/how-to-use-cmake-with-qt5-and-opencv-3-projects/
# Specify OpenCV folder, and take care of dependenciesand includes
#set(OpenCV_DIR "path_to_folder_of_OpenCVConfig.cmake_file")
#set(OpenCV_DIR "usr/local/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(testCmake SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(testCmake
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
endif()

# src: http://amin-ahmadi.com/2018/02/23/how-to-use-cmake-with-qt5-and-opencv-3-projects/
# link required libs
#target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS})
target_link_libraries(testCmake PRIVATE Qt5::Widgets ${OpenCV_LIBS})
