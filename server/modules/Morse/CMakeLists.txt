cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  Morse
)


set(LIB_INCLUDE_DIR 
  "include/Morse/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/Server.hpp
  ${LIB_INCLUDE_DIR}/Alphabet.hpp
  ${LIB_INCLUDE_DIR}/Device.hpp
  )


set(LIB_SOURCE_FILES
src/Server.cpp
src/Alphabet.cpp
src/Device.cpp
)

set(MODULE_LIBS

tcpLengthFramer_${PROJECT_NAME}
TCPServer_${PROJECT_NAME}
PacketEngine_${PROJECT_NAME}
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


add_executable(${LIB_NAME}_exe   
  src/main.cpp
  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
) 

target_link_libraries(${LIB_NAME}_exe ${MODULE_LIBS})
target_include_directories(${LIB_NAME}_exe  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)