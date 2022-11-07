/**
 * @file tcpLengthFramer.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cstdint>
#include <vector>

namespace TCPLengthFramer {
/**
 * @brief Get data from socket by length framing
 *
 * @param in descripteur de fichier accessible en lecture
 * @param dataBuff
 * @return TCPStatus_t nombre d'octets lus
 */
int32_t getData(FILE* in, std::vector<uint8_t>& dataBuff);

/**
 * @brief Send data to socket by length framing
 *
 * @param out descripteur de fichier accessible en ecriture
 * @param dataBuff buffer de données à envoyées
 * @return TCPStatus_t nombre d'octets envoyés
 */
int32_t sendData(FILE* out, std::vector<uint8_t>& dataBuff);
}