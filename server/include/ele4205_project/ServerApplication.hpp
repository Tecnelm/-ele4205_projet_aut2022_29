#pragma once
#include "Protocole/AppMessages.h"
#include "Protocole/PacketEngine/PacketEngine.hpp"
#include <Camera/Camera.hpp>
#include <TCP/Server/TCPServer.hpp>
#include <string>

namespace ServerApplication {
const std::vector<int> jpegSettings = { cv::IMWRITE_JPEG_QUALITY, 30 };
const std::vector<int> pngSettings = { cv::IMWRITE_PNG_COMPRESSION, 2 };

struct imgAcqConf {
    std::string compressionType;
    std::vector<int> compressionSettings;
    std::string res;
};

class ServerApplication {

public:
    ServerApplication(int imagePort);
    ~ServerApplication() = default;
    void process();

private:
    void updateAcqConf(AppMsg_t msg, imgAcqConf& imgConf);

    void configGPIO_(void);
    bool buttonPushed_(void);
    uint16_t getADCValue_(void);


    const int imagePort_;
    struct imgAcqConf imgConf_;
    TCPServer server_;
    Camera cam_;
    bool stop_;
};
}
