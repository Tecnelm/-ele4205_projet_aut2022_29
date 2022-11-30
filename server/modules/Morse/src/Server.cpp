#include "Server.hpp"
#include "Alphabet.hpp"
#include "Device.hpp"

#include "Device.hpp"
#include <fstream>
#include <iostream>
#include <netinet/in.h>
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

    printf("Waiting for a client Morse to connect...\n");

    int clientPort = morseServer.acceptClient();

    printf("Client Morse connected on port : %d\n", clientPort);

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
    std::cout << "String received = " << morseCodeString << std::endl;
    for (char& c : morseCodeString) {
        c = toupper(c);
        if (c == ' ') {
            usleep(MorseElement::MEDIUM_GAP * 1000);

        } else {
            std::vector<MorseElement> elems = morseAlphabet.at(c);
            for (auto& morseElement : elems) {
                morsePlayer.playDuration(morseElement);
                usleep(MorseElement::INTER_ELEM * 1000);
            }
            usleep(MorseElement::SHORT_GAP * 1000);
        }
    }
    std::cout << "Morse Code Played Kill server" << std::endl;
}
}
