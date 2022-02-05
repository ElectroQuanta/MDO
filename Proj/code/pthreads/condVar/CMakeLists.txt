cmake_minimum_required(VERSION 3.5)

project(pEvent LANGUAGES CXX VERSION 1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME}
  main.cpp
  pEvent.h
  pEvent.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
