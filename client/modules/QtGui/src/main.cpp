#include "ConfigWindow.hpp"
#include "iostream"
#include "qt5/QtWidgets/QApplication"
#include <unistd.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ConfigWindow w;
    w.show();
    w.setCloseCallback([]() { std::cout << "close" << std::endl; });
    w.setChangeConfigurationCallback([](std::string resolution, std::string format) {
        sleep(3);
        std::cout << "Resolution: " << resolution << std::endl;
        std::cout << "Format : " << format << std::endl;
    });
    w.setStatusLabel("bonjour");
    app.exec();
    return 0;
}
