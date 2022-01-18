cmake_minimum_required(VERSION 3.5)

project(sqlconn LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPP_CON_VERSION_MAJOR 8)
set(CPP_CON_VER "8.0.27")
set(CPP_CON_LIB mysqlcppconn${CPP_CON_VERSION_MAJOR})
#set(CPPCON_LIB_NAME_DYN "libmysqlcppconn${CONCPP_VERSION_MAJOR}.so.2.${CPP_CON_VER}")

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/local/mysql/connector-c++-${CPP_CON_VER}")
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/debug/)

message("Version major: ${CPP_CON_VERSION_MAJOR}")
message("Base Lib: ${CPP_CON_LIB_NAME_BASE}")


add_executable(${PROJECT_NAME}
  main.cpp
  )

target_link_libraries(${PROJECT_NAME} PRIVATE ${CPP_CON_LIB})
#target_link_libraries(${PROJECT_NAME} PRIVATE mysqlcppconn8)



