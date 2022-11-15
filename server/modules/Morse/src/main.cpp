#include "Device.hpp"
#include "unistd.h"

int main(int argc, char const* argv[])
{
    std::cout << "Start" << std::endl;
    Morse::MorseDevice device(440, 50);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);

    return 0;
}
