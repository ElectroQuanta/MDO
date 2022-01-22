cmake_minimum_required(VERSION 3.5)

project(LSApp VERSION 0.1 LANGUAGES CXX)

set(twitSrcs
  base64.cpp HMAC_SHA1.cpp oauthlib.cpp SHA1.cpp urlencode.cpp twitcurl.cpp)
FIND_PACKAGE(PkgConfig)
include_directories (${PKGS_INCLUDE_DIRS}) 
add_library(twitcurl STATIC ${twitSrcs})
