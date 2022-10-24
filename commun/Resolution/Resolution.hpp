#include <iostream>
#include <map>
#include <string>
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

}
