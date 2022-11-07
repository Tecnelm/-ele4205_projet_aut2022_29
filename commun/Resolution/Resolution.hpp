/**
 * @file Resolution.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Protocole/AppMessages.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

#pragma once

namespace Resolution {

/**
 * @brief Description of a resolution
 *
 */
struct Resolution_t {
    /**
     * @brief Width of the resolution
     *
     */
    int WIDTH;
    /**
     * @brief Height of the resolution
     *
     */
    int HEIGHT;
    /**
     * @brief Number of frame per second of the camera at this resolution, will be writed on change resolution
     *
     */
    double FPS;
};

/**
 * @brief Array containing resolution supported, from txt to Resolution::Resolution_t
 *
 */
extern const std::map<std::string, Resolution_t> resolutions;

/**
 * @brief Fonction discribing the behaviours of flux operator on Resolution::Resolution_t
 *
 * @param os std::ostream& output stream
 * @param resolution const Resolution::Resolution_t resolution to print
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Resolution_t& resolution);

extern const std::map<std::string, AppMsgBit_t> resolutionsMessage;
extern const std::map<std::string, AppMsgBit_t> formatMessage;

}
