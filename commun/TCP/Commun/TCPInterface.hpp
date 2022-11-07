/**
 * @file TCPInterface.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "TCPtypes.h"
#include <stdint.h>
#include <vector>

class TCPreadWrite{

public :
    virtual int32_t sendData(std::vector<uint8_t>& data) = 0;
	virtual int32_t readData(std::vector<uint8_t>& data) = 0;
};