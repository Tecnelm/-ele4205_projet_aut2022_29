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
    /**
     * @brief Construct a client for a tcp stream (wrap the unix syscalls to a simple interface)
     * @param serverIP IP address of the server
     * @param serverPort Port of the server to connect to
     * @param connectUpon if true, a connection attempt is made at construction otherwise "connectToServ()" must be called to connect to the server.
     */
    TCPClient(std::string serverIP ,int serverPort, bool connectUpon = false);

    /**
     * @brief Destroy the TCPClient object
     * If server is still connected when called, it will close the tcp stream and all sys. interfaces
     */
    ~TCPClient();

    /**
     * @brief Attempt to connect to the server
     * @return TCP_OK (= 0) if success, a TCPStatus_t error flag (< 0) otherwise
     */
    TCPStatus_t connectToServ();

    /**
     * @brief Close the tcp stream and all sys. interfaces
     * @return TCP_OK (= 0) if success, a TCPStatus_t error flag (< 0) otherwise
     */
    TCPStatus_t disconnectFromServ();

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

    /**
     * @brief return the connection state of the TCP Client
     * @return 
     */
    const bool isConnected() const;

private:

    int commSocketFd;
    FILE* readCommFd;
    FILE* writeCommFd;
    
    struct sockaddr_in serv_addr;

    bool serverConnected;
};

