#include "ServerApplication.hpp"

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
    , cam_(),
    stop_(false)
{

}

void ServerApplication::ServerApplication::process()
{
    while (!stop_) {

        printf("Waiting for a client to connect...\n");

        int clientPort = server_.acceptClient();

        printf("Client connected on port : %d\n", clientPort);

        PacketEngine pEngine = PacketEngine(&server_);

        AppMsg_t clientAnswer = Resolution::resolutionsMessage.begin()->second|Resolution::formatMessage.begin()->second;

        cv::Mat tempImage;

        std::string oldRes = "";

        do {

            updateAcqConf(clientAnswer, imgConf_);

            // change resolution if needed
            if (imgConf_.res != oldRes) {
                cam_.releaseCamera();
                cam_.changeResolution(Resolution::resolutions.at(imgConf_.res), false);
                oldRes = imgConf_.res;
                cam_.startCamera();
            }

            // Take an image from the camera
            tempImage << cam_;

            // Compress the image as jpeg
            std::vector<uint8_t> mem_buffer;
            cv::imencode(imgConf_.compressionType, tempImage, mem_buffer, imgConf_.compressionSettings);

            // send the compressed image over tcp
            pEngine.sendImg(mem_buffer);

            // printf("Pic taken & sent\n");

            // waitAnswer from client
            if (pEngine.receivePacket() < 0) {
                perror("Error on read");
                exit(EXIT_FAILURE);
            }

            if (pEngine.getType() != dataTypes_t::APP_MESSAGE) {
                printf("Bad dataType received");
                exit(EXIT_FAILURE);
            }

            clientAnswer = pEngine.getMsg();

        } while (clientAnswer != AppMsgBit_t::ELE4205_QUIT);

        server_.disconnectClient();

        printf("Client disconnected !\n");

        cam_.releaseCamera();
    }
}

void ServerApplication::ServerApplication::updateAcqConf(AppMsg_t msg, imgAcqConf& imgConf)
{

    for (auto res: Resolution::resolutionsMessage) {
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