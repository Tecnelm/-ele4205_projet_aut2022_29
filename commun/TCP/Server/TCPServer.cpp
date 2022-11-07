/**
 * @file TCPServer.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "TCPServer.hpp"
#include "../Commun/LengthFramer/tcpLengthFramer.hpp"

#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

TCPServer::TCPServer(int listeningPort, int reuseAddr, int connectionQueueSize) {

    // Creating socket file descriptor
    listeningSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listeningSocketFd < 0) {
        perror("socket failed");
        //ToDO handle error
    }

    if(reuseAddr){
        if (setsockopt(listeningSocketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuseAddr, sizeof(reuseAddr))) {
            perror("setsockopt");
            //ToDO handle error
        }
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(listeningPort);

    if (bind(listeningSocketFd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        //ToDO handle error
    }

    if (listen(listeningSocketFd, connectionQueueSize) < 0) {
        perror("listen");
        //ToDO handle error
    }

}

TCPServer::~TCPServer(){

    if(clientConnected)
        disconnectClient();

    shutdown(listeningSocketFd, SHUT_RDWR);
}

int32_t TCPServer::acceptClient(){

    socklen_t addrLen = sizeof(address);
    commSocketFd = accept(listeningSocketFd, (struct sockaddr*)&address, (socklen_t*) &addrLen);

    if (commSocketFd < 0) {
        perror("Error on accept");
        //ToDO handle error
        return TCPStatus_t::TCP_ERROR_ACCEPT;
    }

    readCommFd = fdopen(commSocketFd, "r");
    writeCommFd = fdopen(commSocketFd, "w");

    clientConnected = true;

    return address.sin_port;
}

TCPStatus_t TCPServer::disconnectClient(){

    fclose(readCommFd);
    fclose(writeCommFd);
    close(commSocketFd);
    //ToDO handle error

    clientConnected = false;

    return TCP_OK;
}

int32_t TCPServer::sendData(std::vector<uint8_t>& data){

    return TCPLengthFramer::sendData(writeCommFd, data);
}

int32_t TCPServer::readData(std::vector<uint8_t>& data){

    return TCPLengthFramer::getData(readCommFd, data);
}