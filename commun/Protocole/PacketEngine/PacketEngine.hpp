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

/**
 * @brief This class provide an "high-level" interface to send and receive 
 * data with any given (and implemented) types through a TCP connection.
 * 
 * It wrap a TCPClient or TCPServer (via a common interface) and use
 * it to send and receive data.
 */
class PacketEngine {

public:
    /**
     * @brief Construct a PacketEngine around any given object implementing the TCPreadWrite interface
     * The connection must be already initialised as this class will only attempt to read and write from/to the TCP stream 
     * @param tcpIf pointer to any object implementing the TCPreadWrite Interface
     */
    PacketEngine(TCPreadWrite* tcpIf);
    ~PacketEngine() = default;

    /**
     * @brief Sends an "AppMsg_t" through the TCP stream
     * @param msg an Application message, can be any value of AppMsg_t
     * @return a value < 0, that can be interpreted as a TCPStatus_t flag, if an error occured 
     * or the number of "Application" bytes sent when successful
     */
    int32_t sendMsg(AppMsg_t msg);

    /**
     * @brief Sends a compressed image through the TCP stream
     * @param image
     * @return a value < 0, that can be interpreted as a TCPStatus_t flag, if an error occured 
     * or the number of "Application" bytes sent when successful
     */
    int32_t sendImg(std::vector<uint8_t>& image);

    /**
     * @brief Poll for a new packet from the stream to arrive.
     * This function will block until a full new packet is received or if an error occured on the socket
     * @return a value < 0, that can be interpreted as a TCPStatus_t flag, if an error occured 
     * or the number of "Application" bytes received when successful
     */
    int32_t receivePacket();

    /**
     * @brief Get the type of data that was just received using the receivePacket() function
     * @return a member of dataTypes_t enum
     */
    dataTypes_t getType();
    
    /**
     * @brief Convert the data just received using receivePacket() function to an AppMsg_t
     * @return the AppMsg_t converted from the "raw" data received from the stream
     */
    AppMsg_t getMsg();

    /**
     * @brief Convert the data just received using receivePacket() function to a std::vector<uint8_t>
     * aka an openCV container for compressed images
     * @return std::vector<uint8_t> correponding to a compressed images
     */
    std::vector<uint8_t> getImg();

private:
    TCPreadWrite* tcpIf;
    dataTypes_t dataType;
    std::vector<uint8_t> dataBuff;

    int32_t _send(dataTypes_t type, std::vector<uint8_t>& rawBuf);
};
