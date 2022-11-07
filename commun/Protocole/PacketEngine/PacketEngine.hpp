/**
 * @file PacketEngine.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../../TCP/Commun/TCPInterface.hpp"
#include "../AppMessages.h"
#include "TypesEnum.h"
#include <cstring>
#include <vector>

class PacketEngine {

public:
    PacketEngine(TCPreadWrite* tcpIf);
    ~PacketEngine() = default;

    int32_t sendMsg(AppMsg_t msg);
    int32_t sendImg(std::vector<uint8_t>& image);

    int32_t receivePacket();
    dataTypes_t getType();
    
    AppMsg_t getMsg();
    std::vector<uint8_t>& getImg();

private:
    TCPreadWrite* tcpIf;
    dataTypes_t dataType;
    std::vector<uint8_t> dataBuff;

    int32_t _send(dataTypes_t type, std::vector<uint8_t>& rawBuf);
};
