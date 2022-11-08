cmake_minimum_required(VERSION 3.12)

project(ELE4205_PROJECT)
set(COMMON_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/commun/)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(doxy_main_page README.md)
set (CMAKE_CXX_STANDARD 11)
include(make-documentation)
include_directories( ${COMMON_DATA_DIR})
list(APPEND CMAKE_PREFIX_PATH <PackageName>[version])
if(NOT ${USE_CROSS_COMPILE_ODROID_POKY})
    list(APPEND CMAKE_CXX_FLAGS "-DLOCAL")
endif()

add_subdirectory(client)
add_subdirectory(server)


