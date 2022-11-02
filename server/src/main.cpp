/**
 * @file main.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Protocole/messageBitfield.h"
#include "Resolution/Resolution.hpp"
#include <Camera/Camera.hpp>
#include <opencv2/opencv.hpp>
#include <tcpLengthFramer/tcpLengthFramer.hpp>

#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <time.h>
#include <unistd.h>

using namespace std;
using namespace cv;

#define PORT 4099

int main(int argc, char const* argv[]) {

    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;

    printf("Opening the server on port : %d\n", PORT);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 4099
    /* THIS SECTION IS OPTIONAL TO FORCE REUSE THE PORT */
    if (setsockopt(server_fd, SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT, &opt,
            sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    /* --------------------------------------------------*/
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Attaching socket to the port 4099
    if (bind(server_fd, (struct sockaddr*)&address,
            sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    Camera cam;
    cam.changeResolution(Resolution::resolutions.at("800x600"));

    while (true) {

        printf("Waiting for a client to connect...\n");
        int clientSocket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

        if (clientSocket < 0) {
            perror("Error on accept");
            exit(EXIT_FAILURE);
        }

        printf("Client connected! Exchanging on port : %d\n", address.sin_port);

        FILE* FdClient = fdopen(clientSocket, "r+");

        uint32_t clientAnswer;

        cam.startCamera();
        Mat tempImage;

        do {
            // Take an image from the camera
            tempImage << cam;

            // Compress the image as jpeg
            std::vector<int> encoder_settings = { cv::IMWRITE_JPEG_QUALITY, 30 };
            std::vector<uint8_t> mem_buffer;
            cv::imencode(".jpeg", tempImage, mem_buffer, encoder_settings);

            // send the compressed image over tcp
            tcpLengthFramer::sendData(FdClient, mem_buffer);

            // printf("Pic taken & sent\n");

            // waitAnswer from client
            std::vector<uint8_t> clientAnswerBuff;
            do {
                if (tcpLengthFramer::getData(FdClient, clientAnswerBuff) != 4) {
                    perror("Error on accept");
                    exit(EXIT_FAILURE);
                }

                clientAnswer = *((uint32_t*)clientAnswerBuff.data());

            } while (clientAnswer != ELE4205_OK && clientAnswer != ELE4205_QUIT);

        } while (clientAnswer == ELE4205_OK);

        fclose(FdClient);

        close(clientSocket);

        printf("Client deconnected !\n");

        cam.releaseCamera();
    }

    shutdown(server_fd, SHUT_RDWR);
    return 0;
}