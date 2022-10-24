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
    void recordVideo(int time, const std::string& filename);
    void setFourcc(int fourcc);

private:
    Resolution::Resolution_t resolution_;
    int detectFps();
    int fourcc_;
    cv::VideoCapture capture_;
    const int detect_fps_frame_  = 2;
};
