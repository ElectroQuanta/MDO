#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qnamespace.h>


/**
 * @brief Screen resolution for embedded display
 *
 * We are using the screen in PORTRAIT MODE
 * - This is done directly in the Qt Designer form
 * @todo: make it dynamic for several resolutions modes and orientations 
 */
#define SCREEN_RES_W 1024 /**< Width in pixels */
#define SCREEN_RES_H 600 /**< Height in pixels */

/**
 * @brief Enumeration of the UI Views the MainWindow controls
 */
enum UIViews{
    WELCOME = 0, /**< Welcome screen; displayed when no ad is running */
    NORMAL, /**< Reproduces video in fullscreen (with audio) */
    INTER, /**< Interaction mode: main menu; picture mode; GIF mode */
    IMGFILT, /**< Image filtering menu */
    SHAR /**< Sharing mode: main menu; editing post; status */
};

/**
 * @brief Constructs the mainwindow
 * @param parent: ptr to a QWidget
 *
 * It initializes the MainWindow, performing the following tasks:
 *  - sets up the UI
 *  - initializes the QStackedwidget to hold the remaining Views
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // remove title bar (we dont want this in the embedded display)
    // UNCOMMENT this at the end
    // src: https://amin-ahmadi.com/2016/07/14/how-to-make-a-frameless-qt-window/
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // STATUSBAR: remove
    // programatically:
    // if(ui->statusbar)
    //     delete ui->statusbar;
    // it is done in the Qt designer
}

MainWindow::~MainWindow()
{
    delete ui;
}

