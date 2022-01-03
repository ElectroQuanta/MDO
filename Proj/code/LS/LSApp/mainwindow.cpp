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

    /**< TITLE BAR */
    // remove title bar (we dont want this in the embedded display)
    // UNCOMMENT this at the end
    // src: https://amin-ahmadi.com/2016/07/14/how-to-make-a-frameless-qt-window/
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    /**< STATUS BAR */
    // remove programatically:
    // if(ui->statusbar)
    //     delete ui->statusbar;
    // it is done in the Qt designer

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIViews::WELCOME);

    /**< Instantiate other UI Windows */
    _normalWind = new NormalWindow();
    _interWind = new InterWindow();
    _imgFiltWind = new ImgFiltWindow();
    _sharWind = new SharWindow();

    /**< Add more UI views */
    ui->stackedWidget->insertWidget(UIViews::NORMAL, _normalWind);
    ui->stackedWidget->insertWidget(UIViews::INTER, _interWind);
    ui->stackedWidget->insertWidget(UIViews::IMGFILT, _imgFiltWind);
    ui->stackedWidget->insertWidget(UIViews::SHAR, _sharWind);

    /**< Connect signals to slots */
    connect(_normalWind, SIGNAL( home_pressed() ),
            this, SLOT( onHome_pressed() ));

}

MainWindow::~MainWindow() { delete ui; }


/* ------------- START DUMMY --------------------
 * DUMMY buttons to navigate to other windows */
void MainWindow::on_pushButton_clicked(){
    ui->stackedWidget->setCurrentIndex(UIViews::NORMAL);
}

void MainWindow::on_pushButton_2_clicked(){
    ui->stackedWidget->setCurrentIndex(UIViews::INTER);
}

void MainWindow::on_pushButton_3_clicked(){
    ui->stackedWidget->setCurrentIndex(UIViews::IMGFILT);
}

void MainWindow::on_pushButton_4_clicked() {
    ui->stackedWidget->setCurrentIndex(UIViews::SHAR);
}

void MainWindow::onHome_pressed(){
    ui->stackedWidget->setCurrentIndex(UIViews::WELCOME);
}

/* ----------------- END DUMMY --------------------- */
