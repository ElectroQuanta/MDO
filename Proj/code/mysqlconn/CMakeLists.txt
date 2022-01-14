cmake_minimum_required(VERSION 3.5)

project(sqlconn LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#if(CONCPP_PACKAGE_BASE_VERSION)
#  set(CPP_CON_VER ${CONCPP_PACKAGE_BASE_VERSION})
#else()
#  set(CPP_CON_VER ${CONCPP_VERSION})
#endif()
set(CPP_CON_VER "8.0.27")

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "/usr/local/mysql/connector-c++-${CPP_CON_VER}")
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/)

#find_library(mysqlcppconn_LIB 
#    libmysqlcppconn8 
#    HINTS ${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/)

message("Version major: ${CONCPP_VERSION_MAJOR}")
set(CONCPP_VERSION_MAJOR 8)
message("Version major: ${CONCPP_VERSION_MAJOR}")
set(CPPCON_LIB_NAME_BASE "libmysqlcppconn${CONCPP_VERSION_MAJOR}")
message("Base Lib: ${CPPCON_LIB_NAME_BASE}")
set(CPPCON_LIB_NAME_DYN "libmysqlcppconn${CONCPP_VERSION_MAJOR}.so.2.${CPP_CON_VER}")

#target_link_libraries(main curl mysqlcppconn)
#target_compile_features(main PRIVATE cxx_range_for) 

#file(GLOB HEADERS *.h)
#
#add_library(devapi STATIC 
#  session.cc
#  result.cc
#  document.cc
#  crud.cc
#  ${HEADERS}
#)
#
#target_link_libraries(devapi PUBLIC common)
#
#add_coverage(devapi)
#
#
#add_subdirectory(tests)

#set(SQL_INCL_DIRS
#  )

if(ANDROID)
  add_library(${PROJECT_NAME} SHARED
    main.cpp
  )
else()
  add_executable(${PROJECT_NAME}
    main.cpp
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${CPP_CONN_LIB_NAME_BASE})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${mysqlcppconn_LIB})



#add_coverage(devapi)
