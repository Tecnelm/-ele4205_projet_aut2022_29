
#include "Application.hpp"
#include "QtGui/ConfigWindow.hpp"
#include <QApplication>
#include <thread>
using namespace std;

#define PORT 4099

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ConfigWindow configWindow;
    #ifdef LOCAL 
    Application mainApplication(PORT, configWindow, "127.0.0.1");
    #else
    Application mainApplication(PORT, configWindow);
    #endif

    configWindow.setCloseCallback(
        [&]() {
            mainApplication.quitApp();
        });

    configWindow.setChangeConfigurationCallback([&](const string& resolution, const string& format) {
        mainApplication.setResolutionAndFormat(resolution, format);
    });
    configWindow.setConnectionCallback([&]() {
        mainApplication.connect();
    });
    
    
    configWindow.show();
    mainApplication.connect();
    int res = app.exec();
    if (res != 0)
        mainApplication.quitApp();
    if (mainApplication.getProcess().joinable())
        mainApplication.getProcess().join();
    return res;
}