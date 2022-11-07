/**
 * @file TCPClient.hpp
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
#include <string>

#include <netinet/in.h>

#include "../Commun/TCPInterface.hpp"

class TCPClient : public TCPreadWrite{

public:

    TCPClient(std::string serverIP ,int serverPort, bool connectUpon = false);
    ~TCPClient();

    TCPStatus_t connectToServ();

    TCPStatus_t disconnectFromServ();

    int32_t sendData(std::vector<uint8_t>& data) override;

    int32_t readData(std::vector<uint8_t>& data) override;

private:

    int commSocketFd;
    FILE* readCommFd;
    FILE* writeCommFd;
    
    struct sockaddr_in serv_addr;

    bool serverConnected;
};