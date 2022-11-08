#include "ConfigWindow.hpp"
#include "Resolution/Resolution.hpp"
#include "Worker.hpp"
#include "qt5/QtCore/QThread"
#include "qt5/QtGui/QKeyEvent"
#include "ressources/ui_ele4205.h"
#include <iostream>
#include <qt5/QtWidgets/QMessageBox>

ConfigWindow::ConfigWindow(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::Ele4205)
    , changeSize_(true)
{
    qRegisterMetaType<std::string>("std::string");
    ui_->setupUi(this);

    changeConfigurationClicked_ = [](const std::string& a, const std::string& b) {};
    closeCallback_ = []() {};
    for (auto& resolution : Resolution::resolutionsMessage) {
        ui_->ResolutionComboBox->addItem(QString::fromStdString(resolution.first));
    }

    for (auto& format : Resolution::formatMessage) {
        ui_->FormatCombotBox->addItem(QString::fromStdString(format.first));
    }
    connect(this, &ConfigWindow::showError, this, &ConfigWindow::showErrorMessage);
    adjustSize();
    setMaximumSize(size());
    setMinimumSize(size());
}

ConfigWindow::~ConfigWindow()
{
    delete ui_;
}

void ConfigWindow::on_ChangeConfigurationButton_clicked()
{
    QThread* thread = new QThread();
    Worker* sendCommand = new Worker(changeConfigurationClicked_, ui_->ResolutionComboBox->currentText().toStdString(), ui_->FormatCombotBox->currentText().toStdString());
    sendCommand->moveToThread(thread);
    connect(thread, &QThread::started, sendCommand, &Worker::process); // Start process of Workend when starting thread
    connect(sendCommand, &Worker::finished, thread, &QThread::quit); // Stop Thread when process ending
    connect(sendCommand, &Worker::finished, sendCommand, &Worker::deleteLater); // Set object to autofree when ending process
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}

void ConfigWindow::setChangeConfigurationCallback(std::function<void(const std::string&, const std::string&)> changeConfigurationClicked)
{
    changeConfigurationClicked_ = changeConfigurationClicked;
}
void ConfigWindow::setCloseCallback(std::function<void(void)> closeCallback)
{
    closeCallback_ = closeCallback;
}

void ConfigWindow::setStatusLabel(const std::string& status)
{
    ui_->LineStatusHolder->setText(QString::fromStdString(status));
}
bool ConfigWindow::event(QEvent* event)
{
    if (event->type() == QEvent::Close) {
        closeCallback_();
    } else if (event->type() == QEvent::KeyPress) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Escape) {
            close();
        }
    }
    return QWidget::event(event);
}

void ConfigWindow::setImage(const QImage& image)
{
    if (changeSize_) {
        changeSize_ = false;
        setMinimumSize(0, 0);
        setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        ui_->imageLabel->setPixmap(QPixmap::fromImage(image));
        ui_->imageLabel->adjustSize();
        ui_->widget->adjustSize();
        adjustSize();
        adjustSize();
        setMinimumSize(size());
        setMaximumSize(size());
    } else {
        ui_->imageLabel->setPixmap(QPixmap::fromImage(image));
    }
}

void ConfigWindow::updateSize()
{
    changeSize_ = true;
}

void ConfigWindow::showErrorMessage(const std::string& message)
{
    QMessageBox messageBox(this);
    messageBox.critical(0, "Error", message.c_str());
}

void ConfigWindow::on_ConnectButton_clicked()
{
    connectionCallback_();
}
void ConfigWindow::setConnectionCallback(std::function<void(void)> connectionCallback)
{
    connectionCallback_ = connectionCallback;
}