/**
 * @file Device.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Implementation of the morse device 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Device.hpp"

namespace Morse {
using namespace std;
MorseDevice ::MorseDevice(int frequency, int dutyCycle, const std::string& driverPath, const std::string& enableFile, const std::string& frequencyFile, const std::string& dutyFile)
{
    driverPath_ = driverPath;
    enableFile_ = enableFile;
    frequencyFile_ = frequencyFile;
    dutyFile_ = dutyFile;

    ofstream fileDevice;
    fileDevice.open(driverPath_ + "/" + frequencyFile_, ios::out);
    fileDevice << frequency;
    fileDevice.close();

    fileDevice.open(driverPath_ + "/" + dutyFile_, ios::out);
    fileDevice << dutyCycle*1024/100;
    fileDevice.close();
}

MorseDevice::~MorseDevice()
{
    ofstream fileDevice;
    fileDevice.open(driverPath_ + "/" + enableFile_, ios::out);
    fileDevice << 0;
    fileDevice.close();
}

void MorseDevice::playDuration(int duration_ms)
{
    ofstream fileDevice;
    fileDevice.open(driverPath_ + "/" + enableFile_, ios::out);
    fileDevice << 1;
    fileDevice.close();
    /* Should be change according to security advice*/
    usleep(duration_ms * 1000); 
    fileDevice.open(driverPath_ + "/" + enableFile_, ios::out);
    fileDevice << 0;
    fileDevice.close();
}
}