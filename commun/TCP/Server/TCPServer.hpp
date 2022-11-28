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

    /**
     * @brief Construct a TCP Server by wrapping unix syscalls
     * @param listeningPort Port to listen for incoming client connections
     * @param reuseAddr if true, will attempt to reuse the listening port if already mark as "used",
     * see socket(7) man page "SO_REUSEADDR", "SO_REUSEPORT" and "NOTES" sections for more informations on this feature
     * @param connectionQueueSize The number of pending connection for "accept()" before new ones gets rejected
     */
    TCPServer(int listeningPort, int reuseAddr = true, int connectionQueueSize = 1);

    /**
     * @brief Destroy the TCPServer object
     * If clients are still connected or pending when called, it will close all tcp stream and all sys. interfaces
     */
    ~TCPServer();

    /**
     * @brief wait for a new client connection and accept it
     * @return Port number of the TCP Stream on the server
     */
    int32_t acceptClient();

    /**
     * @brief Close the tcp stream.
     * @return TCP_OK (= 0) if success
     */
    TCPStatus_t disconnectClient();

    /**
     * @brief Send raw data contained in an std::vector<uint8_t> using TCPLengthFramer
     * @param data a buffer of raw data to send
     * @return if success, the number of bytes sent (>=0), TCPStatus_t error flag (< 0) otherwise
     */
    int32_t sendData(std::vector<uint8_t>& data) override;

    /**
     * @brief Poll and wait for new data to arrive using TCPLengthFramer
     * @param data ref. to a std::vector<uint8_t> that will be fill with received data
     * @return if success, the number of bytes received (>=0), TCPStatus_t error flag (< 0) otherwise
     */
    int32_t readData(std::vector<uint8_t>& data) override;

    private:
    
    struct sockaddr_in address;
    
    int listeningSocketFd; 

    bool clientConnected;

    int commSocketFd;
    FILE* readCommFd;
    FILE* writeCommFd;
};