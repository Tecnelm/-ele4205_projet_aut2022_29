#include "Server.hpp"
#include "Alphabet.hpp"
#include "Device.hpp"

#include "Device.hpp"
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
#include <vector>

namespace Morse {

void serveurCodeMorse(int port)
{

    TCPServer morseServer = TCPServer(port);

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
    MorseDevice morsePlayer(440, 50);
    /* fuck around with the string */
    for (char& c : morseCodeString) {
        c = toupper(c);
        if (c == ' ') {
            morsePlayer.playDuration(MorseElement::MEDIUM_GAP);
        } else {
            std::vector<MorseElement> elems = morseAlphabet.at(c);
            for (auto& morseElement : elems) {
                morsePlayer.playDuration(morseElement);
                morsePlayer.playDuration(MorseElement::INTER_ELEM);
            }
            morsePlayer.playDuration(MorseElement::SHORT_GAP);
        }
    }
    std::cout << morseCodeString << std::endl;
}
}
