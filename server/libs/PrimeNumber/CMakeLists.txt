cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  PrimeNumber
)


set(LIB_INCLUDE_DIR 
  "include/PrimeNumber/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/PrimeNumber.h       
)
set(PROJECT_NAME 
  ${LIB_NAME}
)

set(LIB_SOURCE_FILES
src/PrimeNumber.cpp
)

add_library(${LIB_NAME}
OBJECT
   
  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
) 

target_include_directories(${LIB_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
