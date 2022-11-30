/**
 * @file Device.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Description of the morse device
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#pragma once

namespace Morse {
class MorseDevice {
public:
    /**
     * @brief Construct a new Morse Device object
     *
     * @param frequency frequency of the song played on buzzer
     * @param dutyCycle Duty cycle on the buzzer affect volume must be from 0 to 100
     * @param driverPath Path to the driver of the buzzer
     * @param enableFile File name where activate the buzzer
     * @param frequencyFile File name where writting frequency value of the buffer
     * @param dutyFile File name where writting duty cycle value
     */
    MorseDevice(int frequency, int dutyCycle, const std::string& driverPath = "/sys/devices/pwm-ctrl.42/", const std::string& enableFile = "enable0", const std::string& frequencyFile = "freq0", const std::string& dutyFile = "duty0");
    /**
     * @brief Destroy the Morse Device object
     *
     */
    ~MorseDevice();
    /**
     * @brief Activate the buzzer for the duration specified
     *
     * @param duration_ms duration of activation
     */
    void playDuration(int duration_ms);
    // Data members

private:
    /**
     * @brief Path to the driver of the buzzer
     *
     */
    std::string driverPath_;
    /**
     * @brief File name where activate the buzzer
     *
     */
    std::string enableFile_;
    /**
     * @brief  File name where writting frequency value of the buffer
     *
     */
    std::string frequencyFile_;
    /**
     * @brief File name where writting duty cycle value
     *
     */
    std::string dutyFile_;
};

}