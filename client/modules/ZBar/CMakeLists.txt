cmake_minimum_required(VERSION 3.8.2)


find_package(PkgConfig REQUIRED)
pkg_check_modules(ZBar REQUIRED IMPORTED_TARGET zbar)

set(LIB_NAME
ZBar
)


set(LIB_INCLUDE_DIR 
  "include/ZBar/"
)

set(LIB_HEADER_FILES 
${LIB_INCLUDE_DIR}/ZBar.hpp
)

set(LIB_SOURCE_FILES
  src/ZBar.cpp
)

set(MODULE_LIBS
)

add_library(${LIB_NAME}
OBJECT

  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
  ) 
  
target_link_libraries(${LIB_NAME} ${MODULE_LIBS})
target_link_libraries(${LIB_NAME} ${OpenCV_LIBRARIES} ${MODULE_LIBS})
target_link_libraries(${LIB_NAME} PkgConfig::ZBar)

target_include_directories(${LIB_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Tell CMake to create the helloworld executable
add_executable(${LIB_NAME}_exec 
src/main.cpp
${LIB_SOURCE_FILES}
   
${LIB_HEADER_FILES}

)
target_include_directories(${LIB_NAME}_exec  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIB_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(${LIB_NAME}_exec ${OpenCV_LIBRARIES})
target_link_libraries(${LIB_NAME}_exec ${MODULE_LIBS})
target_link_libraries(${LIB_NAME}_exec PkgConfig::ZBar)

