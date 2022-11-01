#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include<cstdint>
#include <vector>
namespace tcpLengthFramer {
/**
 * @brief Get data from socket by length framing
 *
 * @param in descripteur de fichier accessible en lecture
 * @param dataBuff
 * @return uint32_t nombre d'octets lus
 */
int32_t getData(FILE* in, std::vector<uint8_t>& dataBuff);

/**
 * @brief Send data to socket by length framing
 *
 * @param out descripteur de fichier accessible en ecriture
 * @param dataBuff buffer de données à envoyées
 * @return int32_t nombre d'octets envoyés
 */
int32_t sendData(FILE* out, std::vector<uint8_t>& dataBuff);
}