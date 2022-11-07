cmake_minimum_required(VERSION 3.8.2)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ressources)

set(LIB_NAME
QtGui
)


set(LIB_INCLUDE_DIR 
  "include/QtGui/"
)

set(LIB_HEADER_FILES 
  ${LIB_INCLUDE_DIR}/ConfigWindow.hpp
  ${LIB_INCLUDE_DIR}/Worker.hpp
  ressources/ele4205.ui
)

set(LIB_SOURCE_FILES
src/ConfigWindow.cpp
src/Worker.cpp
)

set(MODULE_LIBS
Qt5::Widgets
Resolution_${PROJECT_NAME}

)

add_library(${LIB_NAME}
OBJECT

  ${LIB_SOURCE_FILES}
   
  ${LIB_HEADER_FILES}
  ) 
  
  target_link_libraries(${LIB_NAME} ${MODULE_LIBS})
target_link_libraries(${LIB_NAME} ${OpenCV_LIBRARIES} ${MODULE_LIBS})

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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${LIB_INCLUDE_DIR}>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add the Qt5 Widgets for linking
target_link_libraries(${LIB_NAME}_exec ${MODULE_LIBS})
