#include <opencv2/opencv.hpp>
#include <tcpLengthFramer/tcpLengthFramer.hpp>
#include "Resolution/Resolution.hpp"
#include "Protocole/messageBitfield.h"

#include <iostream>
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
using namespace cv;

#define PORT 4099

int main(int argc, const char** argv)
{
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "192.168.7.2", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    client_fd = connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    if (client_fd < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("connected ! \n");

    FILE* FdServer = fdopen(sock, "r+");

    cv::Mat dec_image;

    std::vector<uint8_t> tempData = std::vector<uint8_t>();
    tcpLengthFramer::getData(FdServer, tempData);
    dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
    cv::imshow("pic", dec_image);

    while(cv::waitKey(30) != 27){

        uint32_t answer = ELE4205_OK;
        std::vector<uint8_t> packetAnswer = std::vector<uint8_t>(sizeof(uint32_t));
        memcpy(packetAnswer.data(), &answer, sizeof(uint32_t));
        tcpLengthFramer::sendData(FdServer, packetAnswer);

        tempData = std::vector<uint8_t>();
        tcpLengthFramer::getData(FdServer, tempData);
        dec_image = cv::imdecode(tempData, cv::IMREAD_ANYCOLOR);
        cv::imshow("pic", dec_image);
    }

    uint32_t answer = ELE4205_QUIT;
    std::vector<uint8_t> packetAnswer = std::vector<uint8_t>(sizeof(uint32_t));
    memcpy(packetAnswer.data(), &answer, sizeof(uint32_t));
    tcpLengthFramer::sendData(FdServer, packetAnswer);

    fclose(FdServer);

    close(client_fd);
}