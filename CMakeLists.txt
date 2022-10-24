cmake_minimum_required(VERSION 3.12)

project(ELE4205_PROJECT)
set(COMMON_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/commun/)
set(CONFIG_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set (CMAKE_CXX_STANDARD 11)
include_directories( ${COMMON_DATA_DIR})
add_subdirectory(client)
add_subdirectory(server)


