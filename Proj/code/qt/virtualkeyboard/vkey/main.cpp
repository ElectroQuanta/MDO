#include "mainwindow.h"
#include <QtWidgets>

#include <QApplication>

// src: https://stackoverflow.com/q/57161308
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc, argv);
    QMainWindow window;
    window.setGeometry(20, 20, 500, 500);
    QLineEdit input(&window);
    input.move(250, 250);
    window.show();
    return app.exec();
}
