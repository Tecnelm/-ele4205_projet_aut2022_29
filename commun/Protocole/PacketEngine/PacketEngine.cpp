/**
 * @file PacketEngine.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "PacketEngine.hpp"
#include "TypesEnum.h"

PacketEngine::PacketEngine(TCPreadWrite* tcpIf) : tcpIf(tcpIf) {};

/**
 * @brief a general function to append the type of data being sent on an existing rawData packet
 * @param type any member of dataTypes_t enum
 * @param rawBuf a buffer of bytes rerensenting the type of the type parameter
 * @return a value < 0, that can be interpreted as a TCPStatus_t flag, if an error occured 
 * or the number of "Application" bytes sent when successful
 */
int32_t PacketEngine::_send(dataTypes_t type, std::vector<uint8_t>& rawBuf){

    uint32_t packetType = type;

    std::vector<uint8_t> packet = std::vector<uint8_t>(sizeof(uint32_t));
    memcpy(packet.data(), &packetType, sizeof(uint32_t));

    packet.insert(packet.end(), rawBuf.begin(), rawBuf.end());

    int32_t ret = tcpIf->sendData(packet);
    
    return (ret>=sizeof(uint32_t) ? ret-sizeof(uint32_t) : ret);
}

int32_t PacketEngine::receivePacket(){

    std::vector<uint8_t> rawDataBuff;

    int32_t retValue = tcpIf->readData(rawDataBuff);

    if(retValue >= (int32_t) sizeof(uint32_t)){
        dataType = (dataTypes_t) (*((uint32_t*)rawDataBuff.data()));

        dataBuff.clear();
        dataBuff.insert(dataBuff.cend(), rawDataBuff.begin()+sizeof(uint32_t), rawDataBuff.end());
   
        return retValue-sizeof(uint32_t);
    }
    
    return retValue;
}

dataTypes_t PacketEngine::getType(){

    return dataType;
}

/* SEND DATA WITH TYPES HERE*/

int32_t PacketEngine::sendMsg(AppMsg_t msg){

    std::vector<uint8_t> packetMessage = std::vector<uint8_t>(sizeof(AppMsg_t));
    memcpy(packetMessage.data(), &msg, sizeof(AppMsg_t));

    return _send(dataTypes_t::APP_MESSAGE, packetMessage);
}

int32_t PacketEngine::sendImg(std::vector<uint8_t>& image){

    return _send(dataTypes_t::COMPRESS_IMG, image);
}

/* GET DATA WITH TYPES HERE*/

AppMsg_t PacketEngine::getMsg(){

    return (*((AppMsg_t*)dataBuff.data()));
}

std::vector<uint8_t> PacketEngine::getImg(){

    return std::vector<uint8_t>(dataBuff);
}