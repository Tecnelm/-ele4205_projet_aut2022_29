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

#include "ZBar/ZBar.hpp"
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
#include <vector>

int Application::imageCount_ = 0;

Application::Application(int port, ConfigWindow& configWindow, std::string address)
    : port_(port)
    , configWindow_(configWindow)
    , resolution_(Resolution::resolutionsMessage.begin()->first)
    , format_(Resolution::formatMessage.begin()->first)
    , client_(address, port)
    , address_(address)
{
    configWindow_.setStatusLabel("Disconnected");
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
    configWindow_.updateSize();
    if (client_.isConnected()) {
        PacketEngine pEngine = PacketEngine(&client_);
        while (!quitApp_ && client_.isConnected()) {

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
    configWindow_.setStatusLabel("Disconnected");
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
    pEngine.sendMsg(createMessage(resolution_, format_));

    if (!getPacket(pEngine, dataTypes_t::APP_MESSAGE))
        return false;

    AppMsg_t message = pEngine.getMsg();

    if (message & AppMsgBit_t::ELE4205_PUSHB) {
        configWindow_.setStatusLabel("PUSHB");
    } else if (message & AppMsgBit_t::ELE4205_IDOWN) {
        configWindow_.setStatusLabel("IDOWN");
    } else if (message & AppMsgBit_t::ELE4205_READY) {
        configWindow_.setStatusLabel("READY");
    }

    if (message & (AppMsgBit_t::ELE4205_PUSHB | AppMsgBit_t::ELE4205_READY)) {
        pEngine.sendMsg(AppMsgBit_t::ELE4205_OK | AppMsgBit_t::ELE4205_ASK_IMAGE);

        if (!getPacket(pEngine, dataTypes_t::COMPRESS_IMG))
            return false;

        std::vector<uint8_t> tempData = pEngine.getImg();
        dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
        if (message & AppMsgBit_t::ELE4205_PUSHB) {
            buttonpushedProcess(dec_image);
        }
        return true;
    }
    return false;
}

void Application::buttonpushedProcess(cv::Mat& image)
{
    std::thread t([=]() {
        std::stringstream name;
        name << "image/image_" << imageCount_++ << ".";
        for (auto& c : format_)
            name << static_cast<char>(std::tolower(c));
        std::cout << "Save Image" << std::endl;
#ifndef LOCAL
        cv::imwrite(name.str(), image);
#endif
        std::vector<ZBar::decodedObject> decodedObjects;

        // Find and decode barcodes and QR codes
        ZBar::decode(image, decodedObjects);
        std::cout << "Button Pushed" << std::endl;

        if (decodedObjects.empty() == false) {

            TCPClient morseCLient = TCPClient(address_, 4100, true);

            if (morseCLient.isConnected()) {

                std::cout << "Envoie du code morse lu" << std::endl;
                PacketEngine morsePEngine = PacketEngine(&morseCLient);

                if (decodedObjects.empty() == false)
                    morsePEngine.sendStr(decodedObjects[0].data);

                morseCLient.disconnectFromServ();
            } else
                std::cout << "Echec de la connexion au serveur" << std::endl;
        }
    });
    t.detach();
}
std::thread& Application::getProcess()
{
    return mainThread_;
}

bool Application::getPacket(PacketEngine& pEngine, const dataTypes_t& type)
{
    if (pEngine.receivePacket() < 0) {
        printf("Error on read\n");
        client_.disconnectFromServ();
        return false;
    }

    if (pEngine.getType() != type) {
        printf("Bad dataType received\n");
        pEngine.sendMsg(AppMsgBit_t::ELE4205_QUIT);
        client_.disconnectFromServ();
        return false;
    }
    return true;
}