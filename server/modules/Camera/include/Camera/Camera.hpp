#include "Resolution/Resolution.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma once
class Camera {
public:
    void changeResolution(const Resolution::Resolution_t& resolution);
    Camera();
    Camera(int index);
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

private:
    Resolution::Resolution_t resolution_;
    int detectFps();
    cv::VideoCapture capture_;
};