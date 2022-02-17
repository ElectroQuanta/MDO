cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
# External toolchain( it must be set before project() )
set(CROSS_COMPILE "RASP4_64")
#set(CROSS_COMPILE "Desktop")
if(CROSS_COMPILE STREQUAL "RASP4_64")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain/rasptoolchain.cmake)
  message(${CMAKE_TOOLCHAIN_FILE})
endif()

project(daemon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MQUEUE_LD_FLAGS -lrt)

set(PROJECT_SOURCES
  ultrassonicsensor.cpp
  ussdaemon.cpp
#${HEADER_FILES}
#${SRC_FILES}
#${RESOURCES_FILES}
)
add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  )

# CMAKE IS CASE SENSITIVE
# src: https://stackoverflow.com/a/60693001/17836786
target_link_libraries(${PROJECT_NAME} PRIVATE ${MQUEUE_LD_FLAGS})
