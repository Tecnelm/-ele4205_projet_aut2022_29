/**
 * @file Application.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief
 * @version 0.1
 * @date 2022-11-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "Protocole/AppMessages.h"
#include "QtGui/ConfigWindow.hpp"
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief Class Application containing action of the Client
 *
 */
class Application {
public:
    /**
     * @brief Construct a new Application object
     *
     * @param port int Port where the server listening
     * @param configWindow ConfigWindow& Qt configuration window
     */
    Application(int port, ConfigWindow& configWindow);
    /**
     * @brief Destroy the Application object
     *
     */
    ~Application() = default;
    /**
     * @brief Main Loop of our application
     *
     */
    void process();
    /**
     * @brief Set the Resolution And the Format sended to the server
     *
     * @param resolution const std::string&  Resolution to set on the server
     * @param format const std::string& format for encode to set on the server
     */
    void setResolutionAndFormat(const std::string& resolution, const std::string& format);
    /**
     * @brief Set boolean to stop the application
     *
     */
    void quitApp();

private:

    /**
     * @brief Convert un image to QImage and show it on config window
     * 
     * @param image const cv::Mat& Image to show 
     */
    void showImg(const cv::Mat& image);
    /**
     * @brief Create a Message object depending on change of resolution and format 
     *
     * @param resolution const std::string& Resolution wanted 
     * @param format const std::string& Encoding format wanted 
     * @return uint32_t Message to send to the server 
     */
    uint32_t createMessage(const std::string& resolution, const std::string& format);
    /**
     * @brief Reference to the configurationWindow 
     * 
     */
    ConfigWindow& configWindow_;
    /**
     * @brief Actual resolution 
     * 
     */
    std::string resolution_ = "";
    /**
     * @brief Actual encoding format 
     * 
     */
    std::string format_ = "";
    /**
     * @brief Boolean to quit application 
     * 
     */
    bool quitApp_ = false;
    /**
     * @brief Port where client is connected
     * 
     */    
    const int port_;
        

};
