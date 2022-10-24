cmake_minimum_required(VERSION 3.12)

project(ELE4205_PROJECT)
set(COMMON_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/commun/)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(doxy_main_page README.md)
set (CMAKE_CXX_STANDARD 11)
include(make-documentation)
include_directories( ${COMMON_DATA_DIR})
add_subdirectory(client)
add_subdirectory(server)



