/**
 * @file Camera.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Resolution/Resolution.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma once
class Camera {
public:
    /**
     * @brief Change the resolution of camera input and output
     *
     * @param resolution const Resolution::Resolution_t used to redefine the definition
     */
    void changeResolution(const Resolution::Resolution_t& resolution);
    /**
     * @brief Construct a new Camera object
     *
     */
    Camera();
    /**
     * @brief Construct a new Camera object
     *
     * @param index int Index of the camera
     */
    Camera(int index);
    /**
     * @brief Define the behaviour of the operator << on stream
     *
     * @param os std::ostream& where to write the object
     * @param camera Camera containing the information
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);
    /**
     * @brief Record a video of a duration
     *
     * @param time int duration of the video in second
     * @param filename std::string of the path of the video (need to contain extension)
     */
    void recordVideo(int time, const std::string& filename);
    /**
     * @brief Set the Fourcc object
     *
     * @param fourcc int fourcc ID
     */
    void setFourcc(int fourcc);

private:
    Resolution::Resolution_t resolution_;
    /**
     * @brief Detect framerate of the camera on change resolution
     * @details Based on https://github.com/derekmolloy/boneCV/blob/master/boneCVtiming.cpp
     *
     * @return int The number of fps of the camera
     */
    int detectFps();
    /**
     * @brief Discribe the format of image of saved video
     *
     */
    int fourcc_;
    /**
     * @brief VideoCapture discribing the camera
     *
     */
    cv::VideoCapture capture_;
    /**
     * @brief Number of frames used to detect FPS of the camera
     *
     */
    const int detectFpsFrame_ = 10;

    /**
     * @brief Number of image to get to setup the camera and get the right amount of fps
     *
     */
    const int nImageBeforeDetectFPS_ = 2;
};
