#include "tcpLengthFramer.hpp"
#include "../TCPtypes.h"
#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

int32_t TCPLengthFramer::getData(FILE* in, std::vector<uint8_t>& dataBuff)
{

    int32_t dataSize = 0;

    if (fread(&dataSize, sizeof(int32_t), 1, in) != 1){
        printf("Unable to read dataSize from descriptor\n");
        return TCPStatus_t::TCP_ERROR_READ;
    }
        
    dataSize = ntohl(dataSize);

    std::vector<uint8_t> rawData;
    rawData.reserve(dataSize);

    for(int i = 0; i < dataSize; i++){
        uint8_t buff;
        if (fread(&buff, sizeof(uint8_t), 1, in) != 1){
            printf("Unable to read data from descriptor\n");
            return TCPStatus_t::TCP_ERROR_READ;
        }
        rawData.push_back(buff);
    }

    dataBuff.insert(dataBuff.end(), rawData.begin(), rawData.end());
    return rawData.size();
}

int32_t TCPLengthFramer::sendData(FILE* out, std::vector<uint8_t>& dataBuff)
{

    int32_t dataSize = dataBuff.size();

    dataSize = htonl(dataSize);

    if (fwrite(&dataSize, sizeof(int32_t), 1, out) != 1 || fwrite(dataBuff.data(), sizeof(uint8_t), dataBuff.size(), out) != dataBuff.size()){
        printf("Unable to write data to descriptor\n");
        return TCPStatus_t::TCP_ERROR_WRITE;
    }

    fflush(out);
    
    return dataBuff.size();
}