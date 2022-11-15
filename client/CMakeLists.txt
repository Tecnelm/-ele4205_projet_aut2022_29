cmake_minimum_required(VERSION 3.12)

project(ELE4205_PROJECT_client)

if(NOT DEFINED CMAKE_MODULE_PATH)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)
endif()

if(NOT DEFINED COMMON_DATA_DIR)
    set(COMMON_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../commun/)
endif()



set(MODULE_NAME ${PROJECT_NAME})
set(MODULE_HEADER_FILES 
    
)

set(MODULE_SOURCE_FILES
    src/main.cpp
    src/Application.cpp
    include/Application.hpp
)

set(MODULE_LIBS    
    Resolution_${PROJECT_NAME}
    tcpLengthFramer_${PROJECT_NAME}
    TCPClient_${PROJECT_NAME}
    PacketEngine_${PROJECT_NAME}
    QtGui
    ZBar
)


include(unset-opencv-variables)
find_package(OpenCV 2.4 REQUIRED)
if(OpenCV_FOUND)
message( STATUS "OpenCV 2.4 library found in : ${OpenCV_DIR}")
else(OpenCV_FOUND)
message(FATAL ERROR "Librarie OpenCV introuvable!")
endif ()

add_subdirectory(${COMMON_DATA_DIR} commun/)
add_subdirectory(modules)

add_executable(${PROJECT_NAME} ${MODULE_SOURCE_FILES})
target_link_libraries(${MODULE_NAME} ${OpenCV_LIBRARIES} ${MODULE_LIBS})
target_include_directories(${MODULE_NAME}  PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${MODULE_NAME}  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)