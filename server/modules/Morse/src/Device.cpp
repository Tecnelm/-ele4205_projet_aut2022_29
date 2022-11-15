#include "Device.hpp"

namespace Morse {
using namespace std;
MorseDevice ::MorseDevice(int frequency, int dutyCycle, const std::string& driverPath, const std::string& enableFile, const std::string& fequencyFile, const std::string& dutyFile)
{
    driverPath_ = driverPath;
    enableFile_ = enableFile;
    frequencyFile_ = frequencyFile_;
    dutyFile_ = dutyFile;

    ofstream fileDevice;
    fileDevice.open(driverPath_ + "/" + frequencyFile_, ios::out);
    fileDevice << frequency;
    fileDevice.close();

    fileDevice.open(driverPath_ + "/" + dutyFile_, ios::out);
    fileDevice << (dutyCycle * (1024 / 100));
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
    usleep(duration_ms * 1000);
    fileDevice.open(driverPath_ + "/" + enableFile_, ios::out);
    fileDevice << 0;
    fileDevice.close();
}
}