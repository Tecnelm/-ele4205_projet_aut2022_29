#include <iostream>
#include <map>
#include <string>
#pragma once

namespace Resolution {

struct Resolution_t {
    int WIDTH;
    int HEIGHT;
    double FPS;
};

extern const std::map<std::string, Resolution_t> resolutions;
std::ostream& operator<<(std::ostream& os, const Resolution_t& resolution);

}
