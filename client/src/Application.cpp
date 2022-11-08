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

#include "Protocole/AppMessages.h"

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

Application::Application(int port, ConfigWindow& configWindow, std::string address)
    : port_(port)
    , configWindow_(configWindow)
    , resolution_(Resolution::resolutionsMessage.begin()->first)
    , format_(Resolution::formatMessage.begin()->first)
    , client_(address, port)
    , address_(address)
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
    if (client_.isConnected()) {
        PacketEngine pEngine = PacketEngine(&client_);
        cv::Mat dec_image;
        if (readImage(pEngine, dec_image)) {
            showImg(dec_image);
        }
        dec_image.~Mat();
        while (!quitApp_ && client_.isConnected()) {

            uint32_t message = createMessage(resolution_, format_);

            pEngine.sendMsg(message);
            cv::Mat dec_image;
            if (readImage(pEngine, dec_image)) {
                showImg(dec_image);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        if (quitApp_) {
            pEngine.sendMsg(AppMsgBit_t::ELE4205_QUIT);
            client_.disconnectFromServ();
        }
    }
}

uint32_t Application::createMessage(const std::string& resolution, const std::string& format)
{
    uint32_t message = AppMsgBit_t::ELE4205_OK;
    static std::string lastResolution = Resolution::resolutionsMessage.begin()->first;
    static std::string lastFormat = Resolution::formatMessage.begin()->first;
    if (resolution == "" && format == "") {
        lastResolution = Resolution::resolutionsMessage.begin()->first;
        lastFormat = Resolution::formatMessage.begin()->first;

    } else {
        if (lastResolution != resolution) {
            message |= Resolution::resolutionsMessage.at(resolution);
            lastResolution = resolution;
            configWindow_.updateSize();
        }

        if (lastFormat != format) {
            message |= Resolution::formatMessage.at(format);
            lastFormat = format;
        }
    }

    return message;
}

void Application::showImg(const cv::Mat& image)
{
    configWindow_.setImage(QImage(image.data, image.cols, image.rows, QImage::Format_RGB888).rgbSwapped().copy());
}

void Application::connect()
{
    if (!client_.isConnected()) {
        client_.connectToServ();
        if (client_.isConnected()) {
            printf("connected ! \n");
            createMessage("", "");
            if (mainThread_.joinable()) {
                mainThread_.join();
            }
            mainThread_ = std::thread([&]() {
                process();
            });

        } else {
            std::string messageError("Cannot connect to server : ");
            messageError.append(address_);
            emit configWindow_.showError(messageError);
        }
    }
}

bool Application::readImage(PacketEngine& pEngine, cv::Mat& dec_image)
{
    if (pEngine.receivePacket() < 0) {
        printf("Error on read\n");
        client_.disconnectFromServ();
        return false;
        // exit(EXIT_FAILURE);
    }

    if (pEngine.getType() != dataTypes_t::COMPRESS_IMG) {
        printf("Bad dataType received\n");
        pEngine.sendMsg(AppMsgBit_t::ELE4205_QUIT);
        client_.disconnectFromServ();
        return false;
        // exit(EXIT_FAILURE);
    }

    std::vector<uint8_t> tempData = pEngine.getImg();
    dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
    return true;
}

std::thread& Application::getProcess()
{
    return mainThread_;
}