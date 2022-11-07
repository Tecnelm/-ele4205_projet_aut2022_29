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
#pragma once

#include "GrabThread.hpp"
#include "Resolution/Resolution.hpp"
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>

class Camera {

public:
    /**
     * @brief Change the resolution of camera input and output
     *
     * @param resolution const Resolution::Resolution_t used to redefine the definition
     */
    void changeResolution(const Resolution::Resolution_t& resolution, bool needDetectFPS = true);
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

    /**
     * @brief function ton start and acurate the frame and fps of the camera
     *
     * @param useThread Bool To tel if we are using or not multithreading read with defaukt value to true
     * @return true if successfully start the camera
     * @return false In case of error during opening camera
     */
    bool startCamera(bool useThread = true);

    /**
     * @brief Stop the camera record
     *
     */
    void releaseCamera();

    /**
     * @brief Set the Index of the camera to open
     *
     * @param index
     */
    void setIndex(int index);

    /**
     * @brief Grab an image on the camera
     * @details /!\ The camera MUST be allready opened
     * @param output cv::Mat openCv matrix where to put the image
     * @param camera Camera where to get the image
     * @return cv::Mat The matrix where the image where put;
     */
    friend cv::Mat& operator<<(cv::Mat& output, Camera& camera);

    /**
     * @brief Read the current frame on the camera
     * 
     * @param image Image where copy the data 
     * @param flag 
     * @return true If a frame has been read
     * @return false If no frame has been read
     */
    bool read(cv::OutputArray image, int flag = 0);

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

    /**
     * @brief Index of the camera to open with OpenCV
     *
     */
    int indexCamera_;
    /**
     * @brief Mutex to synchronyse frame generate in GrabThread to make a sage copy
     * 
     */
    std::mutex mutexFrame_;
    /**
     * @brief GrabThread in charge of read in continue frame of the camera
     * 
     */
    GrabThread threadGrabImage_;
    /**
     * @brief Mutex to prevent asking at the same time for an image or editing function
     * 
     */
    std::mutex mutexCamera_;
};
