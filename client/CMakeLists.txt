cmake_minimum_required(VERSION 3.12)
if(NOT DEFINED CMAKE_MODULE_PATH)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)
endif()
project(ELE4205_PROJECT_CLIENT)



include(unset-opencv-variables)

find_package(OpenCV 2.4 REQUIRED)
if(OpenCV_FOUND)
message( STATUS "OpenCV 2.4 library found in : ${OpenCV_DIR}")
else(OpenCV_FOUND)
message(FATAL ERROR "Librarie OpenCV introuvable!")
endif ()

add_executable(Hello main.cpp)


target_link_libraries(Hello ${OpenCV_LIBRARIES})
target_include_directories(Hello  PRIVATE ${OpenCV_INCLUDE_DIRS})
