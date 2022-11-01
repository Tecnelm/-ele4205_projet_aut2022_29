#pragma once
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>
class Camera;
class GrabThread  {
public:
    GrabThread(cv::VideoCapture& video,std::mutex& frameMutex);
    ~GrabThread();
    void stop();
    void start();
    bool isFrameAvailable() const;
    bool isAlive() const;
    void resetFrame();
    cv::Mat& getFrame();

private:
    std::thread grapThread_;
    bool isAlive_;
    bool frameAvailable_;
    cv::VideoCapture& videoCapture_;
    std::mutex& frameMutex_;
    cv::Mat currentFrame_;
};


