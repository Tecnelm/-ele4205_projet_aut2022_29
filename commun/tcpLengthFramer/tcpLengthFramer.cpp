#include "tcpLengthFramer.hpp"
#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

int32_t tcpLengthFramer::getData(FILE* in, std::vector<uint8_t>& dataBuff)
{

    int32_t dataSize = 0;

    if (fread(&dataSize, sizeof(int32_t), 1, in) != 1){
        printf("Unable to read dataSize from descriptor\n");
        return -1;
    }
        
    dataSize = ntohl(dataSize);

    std::vector<uint8_t> rawData;
    rawData.reserve(dataSize);

    int i = 0;
    while(i < dataSize){

        uint8_t buff;
        if (fread(&buff, sizeof(uint8_t), 1, in) != 1){
            printf("Unable to read data from descriptor\n");
            return -1;
        }
            
        rawData.push_back(buff);
        i++;
    }

    dataBuff.insert(dataBuff.end(), rawData.begin(), rawData.end());
    return rawData.size();
}

int32_t tcpLengthFramer::sendData(FILE* out, std::vector<uint8_t>& dataBuff)
{

    int32_t dataSize = dataBuff.size();

    dataSize = htonl(dataSize);

    if (fwrite(&dataSize, sizeof(int32_t), 1, out) != 1 || fwrite(dataBuff.data(), sizeof(uint8_t), dataBuff.size(), out) != dataBuff.size()){
        printf("Unable to write data to descriptor\n");
        return -1;
    }

    fflush(out);
    return dataBuff.size();
}