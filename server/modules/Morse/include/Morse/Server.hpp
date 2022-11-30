/**
 * @file Server.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Description of morse server 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Protocole/AppMessages.h"
#include "Protocole/PacketEngine/PacketEngine.hpp"
#include <TCP/Server/TCPServer.hpp>
#include <string>

namespace Morse
{
    /**
     * @brief defined value use by the server that receive the string to play on the morse player 
     * 
     */
    const int portServeurCodeMorse = 4100;
    /**
     * @brief Main code of the morse server 
     * 
     * @param port Port use by the server
     */
    void serveurCodeMorse(int port = portServeurCodeMorse );


}