#include "GrabThread.hpp"
#include "Camera.hpp"
#include <mutex>

GrabThread::GrabThread(cv::VideoCapture& video, std::mutex& frameMutex)
    : grapThread_()
    , isAlive_(false)
    , videoCapture_(video)
    , frameMutex_(frameMutex)
{
}

GrabThread::~GrabThread()
{
}

void GrabThread::stop()
{
    if (this->isAlive_) {
        this->isAlive_ = false;
        grapThread_.join();
    }
}

void GrabThread::start()
{
    this->isAlive_ = true;
    this->frameAvailable_ = false;
    auto t = std::thread([&]() {
        while (this->isAlive_) {

            if (!videoCapture_.grab()) {
                this->isAlive_ = false;
                std::cout << "Error: when reading camera no image available" << std::endl;
            }

            frameMutex_.lock();
            videoCapture_.retrieve(currentFrame_);
            this->frameAvailable_ = true;
            frameMutex_.unlock();
        }
    });
    this->grapThread_ = move(t);
}

bool GrabThread::isFrameAvailable() const
{
    return frameAvailable_;
}

void GrabThread::resetFrame()
{
    frameAvailable_ = false;
}
bool GrabThread::isAlive() const
{
    return this->isAlive_;
}

cv::Mat& GrabThread::getFrame()
{
    return currentFrame_;
}
