#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(400,100);
    w.resize(900,700);
    w.show();

    return a.exec();
}
