cmake_minimum_required(VERSION 3.12)

set(LIB_NAME
  Morse
)


set(LIB_INCLUDE_DIR 
  "include/Morse/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/Morse.hpp
  ${LIB_INCLUDE_DIR}/MorseAlphabet.hpp
  )


set(LIB_SOURCE_FILES
src/Morse.cpp
src/MorseAlphabet.cpp
)

set(MODULE_LIBS
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
