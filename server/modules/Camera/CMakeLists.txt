cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  Camera
)


set(LIB_INCLUDE_DIR 
  "include/Camera/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/Camera.hpp
)
set(PROJECT_NAME 
  ${LIB_NAME}
)

set(LIB_SOURCE_FILES
src/Camera.cpp
)

set(MODULE_LIBS
    Resolution
    PrimeNumber
)

add_library(${LIB_NAME}
OBJECT
   
  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
) 
target_link_libraries(${LIB_NAME} ${MODULE_LIBS})
target_include_directories(${LIB_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
