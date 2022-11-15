/**
 * @file main.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ServerApplication.hpp"

#define PORT 4099

int main(int argc, char const* argv[]) {

    ServerApplication::ServerApplication server(PORT);
    server.process();

    return 0;
}