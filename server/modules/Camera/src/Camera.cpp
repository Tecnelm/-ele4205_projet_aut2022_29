/**
 * @file Camera.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Camera/Camera.hpp"
#include "GrabThread.hpp"
#include "Resolution/Resolution.hpp"
#include <iostream>
#include <thread>
#include <time.h>

using namespace Resolution;
using namespace cv;
Camera::Camera(int index)
    : indexCamera_(index)
    , capture_()
    , mutexFrame_()
    , threadGrabImage_(capture_, mutexFrame_),
    mutexCamera_()
{
}
Camera::Camera()
    : Camera(0) {};

bool Camera::startCamera(bool useThread)
{
    
    if (!this->capture_.isOpened()) {
        this->capture_.open(indexCamera_);
        if (!this->capture_.isOpened()) {
            std::cout << "ERROR: Failed to connect to the camera" << std::endl;
            return 0;
        }
    }
    this->capture_.set(CV_CAP_PROP_FRAME_WIDTH, resolution_.WIDTH);
    this->capture_.set(CV_CAP_PROP_FRAME_HEIGHT, resolution_.HEIGHT);
    if (this->capture_.get(CV_CAP_PROP_FRAME_WIDTH) != resolution_.WIDTH)
        std::cout << "Fail to set WIDTH resolution" << std::endl;
    if (this->capture_.get(CV_CAP_PROP_FRAME_HEIGHT) != resolution_.HEIGHT)
        std::cout << "Fail set HEIGHT resolution" << std::endl;

    cv::Mat frame;
    for (int i = 0; i < this->nImageBeforeDetectFPS_; i++) {
        this->capture_ >> frame;
    }
    if (useThread)
        threadGrabImage_.start();
    return 1;
}

void Camera::releaseCamera()
{
    threadGrabImage_.stop();
    this->capture_.release();
}

void Camera::setIndex(const int index)
{
    indexCamera_ = index;
}

void Camera::recordVideo(int time, const std::string& filename)
{
    bool stopThread = false;

    if (startCamera()) {
        Mat output;
        VideoWriter videoOutput(filename, this->fourcc_, this->resolution_.FPS, Size { this->resolution_.WIDTH, this->resolution_.HEIGHT });
        int nFrame = (time) * this->resolution_.FPS;
        for (int i = 0; i < nFrame; i++) {
            output << *this;
            if (output.empty()) {
                std::cout << "ERROR GET IMAGE" << std::endl;
                break;
            }
            videoOutput << output;
        }
        releaseCamera();
    }
}

void Camera::setFourcc(int fourcc)
{
    this->fourcc_ = fourcc;
}

std::ostream&
operator<<(std::ostream& os, const Camera& camera)
{
    os << camera.resolution_;
    return os;
}
cv::Mat& operator<<(cv::Mat& output, Camera& camera)
{
    if (camera.capture_.isOpened()) {
        camera.read(output);
    }
    return output;
}

void Camera::changeResolution(const Resolution_t& resolution, bool needDetectFPS)
{
    mutexCamera_.lock();
    this->resolution_ = resolution;
    if(needDetectFPS)
        this->resolution_.FPS = this->detectFps();
    mutexCamera_.unlock();
}

int Camera::detectFps()
{

    if (!this->startCamera(false)) {
        std::cout << "ERROR: Failed to connect to the camera" << std::endl;
        return 0;
    }
    threadGrabImage_.stop();

    cv::Mat frame;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < detectFpsFrame_; i++) {

        if (!capture_.grab()) {
            std::cout << "Failed to capture an image" << std::endl;
            return 0;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1000000000.0d;
    this->releaseCamera();
    return detectFpsFrame_ / difference;
}

bool Camera::read(cv::OutputArray array, int flag)
{
    mutexCamera_.lock(); // prevent that two thread ask for an image at the same time 
    bool read=false;
    while (!threadGrabImage_.isFrameAvailable() && threadGrabImage_.isAlive())
        ;
    mutexFrame_.lock(); // prevent against grab thread edit change the image during copy 
    if (threadGrabImage_.isFrameAvailable()) {
        threadGrabImage_.getFrame().copyTo(array);
        threadGrabImage_.resetFrame();
        read = true;
    }
    mutexFrame_.unlock();
    mutexCamera_.unlock();
    return read;;
}