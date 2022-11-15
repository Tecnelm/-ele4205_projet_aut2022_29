#include "ServerApplication.hpp"

#include "Morse/Server.hpp"
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
using namespace cv;

ServerApplication::ServerApplication::ServerApplication(int imagePort)
    : imagePort_(imagePort)
    , server_(imagePort_)
    , cam_()
    , stop_(false)
{
    configGPIO_();
}

void ServerApplication::ServerApplication::process()
{
    const uint16_t adcThresholdValue = 1010;

    while (!stop_) {

        printf("Waiting for a client to connect...\n");

        int clientPort = server_.acceptClient();

        printf("Client connected on port : %d\n", clientPort);

        PacketEngine pEngine = PacketEngine(&server_);

        AppMsg_t clientAnswer = Resolution::resolutionsMessage.begin()->second | Resolution::formatMessage.begin()->second;
        updateAcqConf(clientAnswer, imgConf_);

        cv::Mat tempImage;

        std::string oldRes = "";

        // waitAnswer from client
        if (pEngine.receivePacket() < 0) {
            printf("Error on read\n");
            break;
        }

        if (pEngine.getType() != dataTypes_t::APP_MESSAGE) {
            printf("Bad dataType received\n");
            break;
        }

        clientAnswer = pEngine.getMsg();

        while ((clientAnswer & AppMsgBit_t::ELE4205_QUIT) == 0) {

            updateAcqConf(clientAnswer, imgConf_);

            // change resolution if needed
            if (imgConf_.res != oldRes) {
                cam_.releaseCamera();
                cam_.changeResolution(Resolution::resolutions.at(imgConf_.res), false);
                oldRes = imgConf_.res;
                cam_.startCamera();
            }

            if ((clientAnswer & AppMsgBit_t::ELE4205_OK) && (clientAnswer & AppMsgBit_t::ELE4205_ASK_IMAGE)) {
                // Take an image from the camera
                tempImage << cam_;

                // Compress the image as jpeg
                std::vector<uint8_t> mem_buffer;
                cv::imencode(imgConf_.compressionType, tempImage, mem_buffer, imgConf_.compressionSettings);

                // send the compressed image over tcp
                pEngine.sendImg(mem_buffer);

            } else if (clientAnswer & AppMsgBit_t::ELE4205_OK) {

                AppMsg_t serverAnswer = AppMsgBit_t::ELE4205_DEFAULT;

                if (getADCValue_() > adcThresholdValue) {
                    serverAnswer |= AppMsgBit_t::ELE4205_IDOWN;
                } else {

                    static bool previousButtonState = false;
                    bool buttonState = buttonPushed_();

                    if (buttonState && !previousButtonState) {
                        serverAnswer |= AppMsgBit_t::ELE4205_PUSHB;

                        static std::thread morsePlayerThread;
                        static bool end = true;
                        if (end) {
                            end = false;
                            std::cout << "Start new Thread Morse" << std::endl;
                            if (morsePlayerThread.joinable())
                                morsePlayerThread.join();

                            morsePlayerThread = std::thread([&]() {
                                Morse::serveurCodeMorse();
                                end = true;
                            });
                        }
                        // todo Start the morseCodeServer here
                    } else {
                        serverAnswer |= AppMsgBit_t::ELE4205_READY;
                    }

                    if (buttonState != previousButtonState) {
                        previousButtonState = buttonState;
                    }
                }

                pEngine.sendMsg(serverAnswer);
            }

            // waitAnswer from client
            if (pEngine.receivePacket() < 0) {
                printf("Error on read\n");
                break;
            }
            if (pEngine.getType() != dataTypes_t::APP_MESSAGE) {
                printf("Bad dataType received\n");
                break;
            }
            clientAnswer = pEngine.getMsg();
        }

        server_.disconnectClient();

        printf("Client disconnected !\n");

        cam_.releaseCamera();
    }
}

void ServerApplication::ServerApplication::configGPIO_(void)
{

    std::ofstream fileGpioSlct = std::ofstream("/sys/class/gpio/export");
    fileGpioSlct << "228";
    fileGpioSlct.close();

    std::ofstream fileGpioDir = std::ofstream("/sys/class/gpio/gpio228/direction");
    fileGpioDir << "in";
    fileGpioDir.close();
}

bool ServerApplication::ServerApplication::buttonPushed_(void)
{

    std::string strValue;
#ifdef LOCAL
    static int cnt = 0;
    cnt = (cnt + 1) % 30;
    strValue = cnt == 0 ? "1" : "0";

#else
    std::ifstream fileGpioValue = std::ifstream("/sys/class/gpio/gpio228/value");
    fileGpioValue >> strValue;
    fileGpioValue.close();

    // std::cout << "GPIO input = " << strValue << std::endl;
#endif

    return strValue == "1" ? false : true;
}

uint16_t ServerApplication::ServerApplication::getADCValue_(void)
{

    std::string strValue;
#ifdef LOCAL
    strValue = "100";
#else
    std::ifstream fileADCValue = std::ifstream("/sys/class/saradc/ch0");
    fileADCValue >> strValue;
    fileADCValue.close();

    // std::cout << "ADC input = " << strValue << std::endl;
#endif

    return stoi(strValue);
}

void ServerApplication::ServerApplication::updateAcqConf(AppMsg_t msg, imgAcqConf& imgConf)
{

    for (auto res : Resolution::resolutionsMessage) {
        if (msg & res.second) {
            imgConf.res = res.first;
            break;
        }
    }

    if (msg & AppMsgBit_t::ELE4205_JPEG) {
        imgConf.compressionType = ".jpeg";
        imgConf.compressionSettings = jpegSettings;
    } else if (msg & AppMsgBit_t::ELE4205_PNG) {
        imgConf.compressionType = ".png";
        imgConf.compressionSettings = pngSettings;
    }
}