
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
    Application mainApplication(PORT, configWindow);

    configWindow.setCloseCallback(
        [&]() {
            mainApplication.quitApp();
        });

    configWindow.setChangeConfigurationCallback([&](const string& resolution, const string& format) {
        mainApplication.setResolutionAndFormat(resolution, format);
    });

    thread mainthread([&]() {
        mainApplication.process();
    });
    configWindow.show();
    int res = app.exec();
    if (res != 0)
        mainApplication.quitApp();
    mainthread.join();
    return res;
}