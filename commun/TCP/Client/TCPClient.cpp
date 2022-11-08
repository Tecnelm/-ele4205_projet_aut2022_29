/**
 * @file TCPClient.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "TCPClient.hpp"
#include "../Commun/LengthFramer/tcpLengthFramer.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

TCPClient::TCPClient(std::string serverIP, int serverPort, bool connectUpon)
    : serverConnected(false)
{

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);

    // Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, serverIP.c_str(), &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address or Address not supported \n");
        // todo handle error
    }

    if (connectUpon) {
        connectToServ();
        // handle error
    }
}

TCPClient::~TCPClient()
{

    if (serverConnected) {
        fclose(readCommFd);
        fclose(writeCommFd);
        close(commSocketFd);
    }
}

TCPStatus_t TCPClient::connectToServ()
{

    serverConnected = false;

    // attach to a socket
    if ((commSocketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\nSocket creation error \n");
        // todo handle error
        return TCP_ERROR_OPEN_SOCK;
    }

    if (connect(commSocketFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        // todo handle error
        return TCP_ERROR_CONNECT;
    }

    readCommFd = fdopen(commSocketFd, "r");
    writeCommFd = fdopen(commSocketFd, "w");

    serverConnected = true;
    return TCP_OK;
}

TCPStatus_t TCPClient::disconnectFromServ()
{

    fclose(readCommFd);
    fclose(writeCommFd);
    close(commSocketFd);
    // todo handleErrors

    serverConnected = false;
    return TCP_OK;
}

int32_t TCPClient::sendData(std::vector<uint8_t>& data)
{

    return TCPLengthFramer::sendData(writeCommFd, data);
}

int32_t TCPClient::readData(std::vector<uint8_t>& data)
{

    return TCPLengthFramer::getData(readCommFd, data);
}

const bool TCPClient::isConnected() const
{
    return serverConnected;
}
