cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
# External toolchain( it must be set before project() )
#set(CROSS_COMPILE "RASP4_64")
#set(CROSS_COMPILE "Desktop")
if(CROSS_COMPILE STREQUAL "RASP4_64")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain/rasptoolchain.cmake)
  message(${CMAKE_TOOLCHAIN_FILE})
endif()

project(twitcurlstatic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CROSS_COMPILE STREQUAL "RASP4_64")
  set(CURL_INCLUDE_DIR ${HOST_PATH}/${TOOLS_PREFIX}/sysroot/usr/include/curl)
  set(CURL_LIBRARIES ${HOST_PATH}/${TOOLS_PREFIX}/sysroot/usr/lib/libcurl.so)
  message("CURL INCLUDE DIR: " ${CURL_INCLUDE_DIR})
  message("CURL LIBRARIES" ${CURL_LIBRARIES})
include_directories(${CURL_INCLUDE_DIR})
else()
endif()


# Build Twitter static library
set(twitSrcs
  ${CMAKE_SOURCE_DIR}/lib/src/base64.cpp
  ${CMAKE_SOURCE_DIR}/lib/src/HMAC_SHA1.cpp
  ${CMAKE_SOURCE_DIR}/lib/src/oauthlib.cpp
  ${CMAKE_SOURCE_DIR}/lib/src/SHA1.cpp
  ${CMAKE_SOURCE_DIR}/lib/src/urlencode.cpp
  ${CMAKE_SOURCE_DIR}/lib/src/twitcurl.cpp)
FIND_PACKAGE(PkgConfig)
include_directories (${PKGS_INCLUDE_DIRS}) 
add_library(twitcurl STATIC ${twitSrcs})

# ================ TWITCURL
#$(CC) twitterClient.cpp -I./include/ -L ./libtwitcurl.a -ltwitcurl -o twitterClient
#set(TWITCURL_LIB twitcurl)



include_directories({CMAKE_SOURCE_DIR}/include)
#set(TWITCURL_LIB "-L${CMAKE_SOURCE_DIR}/staticlibs/libtwitcurl.a")
#set(TWITCURL_LIB "-Llibtwitcurl.a")
#message("TWITCURL_LIB ${TWITCURL_LIB}")

set(PROJECT_SOURCES
  twitterClient.cpp
  twitterClient.h
)
add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE twitcurl ${CURL_LIBRARIES})
