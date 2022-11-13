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
#include "Protocole/PacketEngine/PacketEngine.hpp"
#include "QtGui/ConfigWindow.hpp"
#include <TCP/Client/TCPClient.hpp>

#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

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
    Application(int port, ConfigWindow& configWindow, std::string address = "192.168.7.2");
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

    /**
     * @brief Conect client to server
     *
     */
    void connect();

    /**
     * @brief Return the thread containing the process running
     *
     * @return std::thread&
     */
    std::thread& getProcess();

    /**
     * @brief Ask for packet and Verify if the type of a message is correct or not. If not close the the socket and stop process
     *
     * @param pEngine
     * @param type dataTypes_t wanted
     * @return true type is correct
     * @return false error when reading message
     */
    bool getPacket(PacketEngine& pEngine, const dataTypes_t& type);

private:
    /**
     * @brief Convert un image to QImage and show it on config window
     *
     * @param image const cv::Mat& Image to show
     */
    void showImg(const cv::Mat& image);

    bool readImage(PacketEngine& pEngine, cv::Mat& dec_image);

    void buttonpushedProcess(cv::Mat& image);

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

    /**
     * @brief Address where the client is currently connected
     *
     */
    std::string address_;

    /**
     * @brief TCP client linked to the server
     *
     */
    TCPClient client_;

    /**
     * @brief thread Containing main process
     *
     */
    std::thread mainThread_;

    /**
     * @brief suffix to add on image name
     *
     */
    static int imageCount_;
};
