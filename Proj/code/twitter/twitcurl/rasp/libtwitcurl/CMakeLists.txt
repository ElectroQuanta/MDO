cmake_minimum_required(VERSION 3.5)


# External toolchain( it must be set before project() )
set(CROSS_COMPILE "RASP4_64")
#set(CROSS_COMPILE "Desktop")
if(CROSS_COMPILE STREQUAL "RASP4_64")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain/rasptoolchain.cmake)
  message(${CMAKE_TOOLCHAIN_FILE})
endif()

project(LSApp VERSION 0.1 LANGUAGES CXX)

set(twitSrcs
  base64.cpp HMAC_SHA1.cpp oauthlib.cpp SHA1.cpp urlencode.cpp twitcurl.cpp)
FIND_PACKAGE(PkgConfig)
include_directories (${PKGS_INCLUDE_DIRS}) 
add_library(twitcurl STATIC ${twitSrcs})
