/**
 * @file ConfigWindow.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Configuration gui for the client side
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __CONFIGWINDOW_H__
#define __CONFIGWINDOW_H__

#include "qt5/QtWidgets/QWidget"
#include <functional>
#include <string>

/**
 * @brief Foward declaration of the ui file used for the window ( located in ressources/*.ui)
 *
 */
namespace Ui {
class Ele4205;
}

class ConfigWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construct a new Config Window object
     *
     * @param parent
     */
    ConfigWindow(QWidget* parent = 0);
    /**
     * @brief Construct a new Config Window object
     *
     * @param changeConfigurationClicked std::function<void(const std::string&,const std::string&)> Function to execute in different an other thread when button is clicked
     * @param onCloseCallback  std::function<void()> Function to execute before closing the window
     * @param parent QWidget parent of the QWidget
     */
    ConfigWindow(std::function<void(const std::string&, const std::string&)> changeConfigurationClicked, std::function<void(void)> onCloseCallback, QWidget* parent = 0);
    /**
     * @brief Set the Change Configuration Callback object
     *
     * @param changeConfigurationClicked std::function<void(const std::string&,const std::string&)>  Lambda callback function when clicking on the change configuration button
     */
    void setChangeConfigurationCallback(std::function<void(const std::string&, const std::string&)> changeConfigurationClicked);
    /**
     * @brief Set the Close Callback object
     *
     * @param closeCallback std::function<void()> Lambda function to execute when closing the QWidget
     */
    void setCloseCallback(std::function<void(void)> closeCallback);
    /**
     * @brief Set the Status Label object
     *
     * @param string std::string to show in the lineEdit
     */
    void setStatusLabel(const std::string& string);
    /**
     * @brief Destroy the Config Window object
     *
     */
    ~ConfigWindow();

    /**
     * @brief Set image in Imagelabel 
     * 
     * @param image const QImage& image image to show on the label
     */
    void setImage(const QImage& image);

    /**
     * @brief Allow auto resize on next  function allowed 
     * 
     */
    void updateSize();
    
private slots:
    /**
     * @brief Function called when button is pressed
     *
     */
    void on_ChangeConfigurationButton_clicked();

private:
    /**
     * @brief Desired action when clicked on button
     *
     */
    std::function<void(const std::string&, const std::string&)> changeConfigurationClicked_;
    /**
     * @brief Desired action on closing event
     *
     */
    std::function<void(void)> closeCallback_;
    /**
     * @brief Function call by Qt on event See QtDocumentation
     *
     * @param event
     * @return true
     * @return false
     */
    bool event(QEvent* event) override;
    /**
     * @brief Ui of the window created with qt designer
     *
     */
    Ui::Ele4205* ui_;
    /**
     * @brief Boolean to allow autoresize window
     * 
     */
    bool changeSize_;
};

#endif // __CONFIGWINDOW_H__