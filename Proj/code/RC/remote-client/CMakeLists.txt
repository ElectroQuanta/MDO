cmake_minimum_required(VERSION 3.5)

project(remote-client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

#set(TS_FILES remote-client_en_150.ts)

set(CPP_CON_VERSION_MAJOR 8)
set(CPP_CON_VER "8.0.27")
set(CPP_CON_LIB mysqlcppconn${CPP_CON_VERSION_MAJOR})
find_package(CURL REQUIRED)

if (CURL_FOUND)
    list(APPEND Project_INCLUDE_DIRS ${CURL_INCLUDE_DIRS})
    message("CURL FOUND: ${CURL_LIBRARIES}")
endif()

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/include/mysqlcpp")
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/debug/)

message("Version major: ${CPP_CON_VERSION_MAJOR}")
message("Base Lib: ${CPP_CON_LIB_NAME_BASE}")

#include_directories(usr/local/include)
#link_directories(../include/curlpp-0.8.1/)

if(ANDROID)
  add_library(remote-client SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    adminwindow.cpp
    adminwindow.h
    adminwindow.ui
    brandwindow.cpp
    brandwindow.h
    brandwindow.ui
    #${TS_FILES}
  )
else()
  add_executable(remote-client
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    adminwindow.cpp
    adminwindow.h
    adminwindow.ui
    brandwindow.cpp
    brandwindow.h
    brandwindow.ui
    #${TS_FILES}
  )
endif()

set( CURLPP_LIBS curlpp)

#set(CURL_LIBRARIES /home/hugof37/Desktop/ESRG/Group_Repo/ESRG-Sem1/Proj/code/RC/include/curlpp-0.8.1/include/)

target_link_libraries(remote-client PRIVATE Qt5::Widgets ${CPP_CON_LIB} ${CURL_LIBRARIES} -lpthread ${CURLPP_LIBS})

#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
