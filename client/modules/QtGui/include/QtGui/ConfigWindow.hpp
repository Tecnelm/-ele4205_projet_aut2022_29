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

Q_DECLARE_METATYPE(std::string)
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

    /**
     * @brief Set the Connection Callback on connection button
     *
     * @param connectionCallback
     */
    void setConnectionCallback(std::function<void(void)> connectionCallback);

signals:
    /**
     * @brief Signal to show a QmessageBox "error" with specified message
     *
     * @param message std::string message to show in QmessageBox
     */
    void showError(const std::string& message);

private slots:
    /**
     * @brief Function called when button is pressed
     *
     */
    void on_ChangeConfigurationButton_clicked();
    /**
     * @brief Function called when button connection is pressed
     *
     */
    void on_ConnectButton_clicked();
    /**
     * @brief Function that show an QmessageBox "error" with specified message call when emiting showError signal
     *
     * @param message std::string Message to show
     */
    void showErrorMessage(const std::string& message);

    /**
     * @brief Set the image on the camera
     *
     * @param pixmap
     */
    void setImagePixMap(const QPixmap& pixmap);

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

    /**
     * @brief Lambda function called when pressing connection button
     *
     */
    std::function<void(void)> connectionCallback_;
};

#endif // __CONFIGWINDOW_H__