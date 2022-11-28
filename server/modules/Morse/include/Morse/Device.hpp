#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#pragma once

namespace Morse {
class MorseDevice {
public:
    MorseDevice(int frequency, int dutyCycle, const std::string& driverPath = "/sys/devices/pwm-ctrl.42/", const std::string& enableFile = "enable0", const std::string& frequencyFile = "freq0", const std::string& dutyFile = "duty0");
    ~MorseDevice();
    void playDuration(int duration_ms);
    // Data members

private:
    std::string driverPath_;
    std::string enableFile_;
    std::string frequencyFile_;
    std::string dutyFile_;
};

}