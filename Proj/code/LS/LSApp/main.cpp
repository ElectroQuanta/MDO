#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /**< Enable virtual keyboard */
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
