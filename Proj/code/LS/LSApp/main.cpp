#include "mainwindow.h"

#include <QApplication>
#include <qnamespace.h>
//#include <QFile>

int main(int argc, char *argv[])
{
    /**< Enable virtual keyboard */
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    /**< Instantiating app */
    QApplication a(argc, argv);

    /**< Setting global style */
    /* Reading from file
     * src: https://forum.qt.io/post/415606
     */
    // QFile file(":/resources/style/stylesheet.qss");
    // file.open(QFile::ReadOnly);
    // QString styleSheet = QLatin1String( file.readAll() );
    // a.setStyleSheet(styleSheet);
    /* setting string directly */
    a.setStyleSheet("QWidget{ background-color: black; color: rgb(186, 189, 182); } QPushButton{ background-color: rgb(186, 189, 182); color: black; }");


    /**< Creating the main window and displaying it */
    MainWindow w;
    w.show();

    /**< Starting loop of events */
    return a.exec();
}
