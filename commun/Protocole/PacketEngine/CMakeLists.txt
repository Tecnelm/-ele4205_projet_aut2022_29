cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  PacketEngine_${PROJECT_NAME}
)


set(LIB_INCLUDE_DIR 
  ./
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/PacketEngine.hpp
  ${LIB_INCLUDE_DIR}/../../TCP/Commun/TCPInterface.hpp
)

set(LIB_SOURCE_FILES
  PacketEngine.cpp
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
