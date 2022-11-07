/**
 * @file Application.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-11-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Application.hpp"
#include "Resolution/Resolution.hpp"
#include <TCP/Client/TCPClient.hpp>

#include "Protocole/AppMessages.h"
#include "Protocole/PacketEngine/PacketEngine.hpp"

#include <arpa/inet.h>
#include <chrono>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <time.h>
#include <unistd.h>

Application::Application(int port, ConfigWindow& configWindow)
    : port_(port)
    , configWindow_(configWindow)
    , resolution_(Resolution::resolutionsMessage.begin()->first)
    , format_(Resolution::formatMessage.begin()->first)
{
}

void Application::setResolutionAndFormat(const std::string& resolution, const std::string& format)
{
    resolution_ = resolution;
    format_ = format;
}
void Application::quitApp()
{
    quitApp_ = true;
}

void Application::process()
{
    TCPClient client = TCPClient("127.0.0.1", port_, true);

    printf("connected ! \n");

    PacketEngine pEngine = PacketEngine(&client);

    if (pEngine.receivePacket() < 0) {
        perror("Error on read");
        exit(EXIT_FAILURE);
    }

    if (pEngine.getType() != dataTypes_t::COMPRESS_IMG) {
        perror("Bad dataType received");
        exit(EXIT_FAILURE);
    }

    std::vector<uint8_t> tempData = pEngine.getImg();
    cv::Mat dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
    showImg(dec_image);

    while (!quitApp_) {

        uint32_t message = createMessage(resolution_, format_);

        pEngine.sendMsg(message);

        if (pEngine.receivePacket() < 0) {
            perror("Error on read");
            exit(EXIT_FAILURE);
        }

        if (pEngine.getType() != dataTypes_t::COMPRESS_IMG) {
            perror("Bad dataType received");
            exit(EXIT_FAILURE);
        }

        tempData = pEngine.getImg();
        dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
        showImg(dec_image);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    pEngine.sendMsg(AppMsgBit_t::ELE4205_QUIT);
}

uint32_t Application::createMessage(const std::string& resolution, const std::string& format)
{
    uint32_t message = AppMsgBit_t::ELE4205_OK;
    static std::string lastResolution = Resolution::resolutionsMessage.begin()->first;
    static std::string lastFormat = Resolution::formatMessage.begin()->first;

    if (lastResolution != resolution) {
        message |= Resolution::resolutionsMessage.at(resolution);
        lastResolution = resolution;
        configWindow_.updateSize();
    }

    if (lastFormat != format) {
        message |= Resolution::formatMessage.at(format);
        lastFormat = format;
    }

    return message;
}

void Application::showImg(const cv::Mat& image)
{
    configWindow_.setImage( QImage(image.data, image.cols, image.rows, QImage::Format_RGB888).rgbSwapped());
}