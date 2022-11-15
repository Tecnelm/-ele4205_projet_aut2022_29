#include "Server.hpp"

#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

namespace Morse{

    const int portServeurCodeMorse = 4100;

    void serveurCodeMorse(void){

        TCPServer morseServer = TCPServer(portServeurCodeMorse);

        printf("Waiting for a client to connect...\n");

        int clientPort = morseServer.acceptClient();

        printf("Client connected on port : %d\n", clientPort);

        PacketEngine pEngine = PacketEngine(&morseServer);

        // waitAnswer from client
        if (pEngine.receivePacket() < 0) {
            printf("Error on read\n");
            return;
        }

        if (pEngine.getType() != dataTypes_t::STR_MESSAGE) {
            printf("Bad dataType received\n");
            return;
        }

        std::string morseCodeString = pEngine.getStr();

        /* fuck around with the string */
        std::cout << morseCodeString << std::endl;
    }
}