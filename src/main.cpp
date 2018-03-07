#include <iostream>

#include <QApplication>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << std::endl;

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    a.exec();

    return 0;
}
