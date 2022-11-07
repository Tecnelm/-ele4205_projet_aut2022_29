/**
 * @file TCPServer.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <vector>
#include <stdio.h>
#include <stdint.h>

#include <netinet/in.h>

#include "../Commun/TCPInterface.hpp"

class TCPServer : public TCPreadWrite{

    public:

    TCPServer(int listeningPort, int reuseAddr = true, int connectionQueueSize = 1);
    ~TCPServer();

    int32_t acceptClient();

    TCPStatus_t disconnectClient();

    int32_t sendData(std::vector<uint8_t>& data) override;

    int32_t readData(std::vector<uint8_t>& data) override;

    private:
    
    struct sockaddr_in address;
    
    int listeningSocketFd; 

    bool clientConnected;

    int commSocketFd;
    FILE* readCommFd;
    FILE* writeCommFd;
};