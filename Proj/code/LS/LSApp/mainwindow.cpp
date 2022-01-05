#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <QImage>
#include <qwidget.h>

#define WELCOME_IMG_PATH ":/resources/img/welcome.png"

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
enum UIViews {
  WELCOME = 0, /**< Welcome screen; displayed when no ad is running */
  NORMAL,      /**< Reproduces video in fullscreen (with audio) */
  INTER,       /**< Interaction mode: main menu; picture mode; GIF mode */
  IMGFILT,     /**< Image filtering menu */
  SHAR         /**< Sharing mode: main menu; editing post; status */
};

/**< Camera index */
#define CAM_IDX 0


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
    /* UIs */ 
    connect(_normalWind, SIGNAL( home_pressed() ),
            this, SLOT( onHome_pressed() ));
    connect(_interWind, SIGNAL( home_pressed() ),
            this, SLOT( onHome_pressed() ));
    connect(_interWind, SIGNAL( imgfilt_mode_pressed() ),
            this, SLOT( onImgFilt_mode_pressed() ));
    connect(_interWind, SIGNAL( shar_mode_pressed() ),
            this, SLOT( onShar_mode_pressed() ));
    connect(_imgFiltWind, SIGNAL( inter_mode_pressed() ),
            this, SLOT( onInter_mode_pressed() ));
    connect(_sharWind, SIGNAL( inter_mode_pressed() ),
            this, SLOT( onInter_mode_pressed() ));
    /* Others */
    connect(_interWind, SIGNAL(cam_start() ),
            this, SLOT( onCam_started() ) );

    /* Load resource images */
    QImage img = QImage(WELCOME_IMG_PATH);
    _welcome_img = new QGraphicsPixmapItem( QPixmap::fromImage(img) );
    
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(_welcome_img);
    ui->graphicsView->fitInView(_welcome_img, Qt::KeepAspectRatio);


    
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::onCam_started(){
    using namespace cv;

    /**< Open camera to capture video */
    if(! _video.open( CAM_IDX )){
        emit interWindUpdateStatus("ERROR: could not open camera...");
        return;
    }

    ui->graphicsView->scene()->addItem(_pixmap);

    Mat frame;
    while(_video.isOpened())
    {
        _video >> frame;
        if(!frame.empty())
        {
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            _pixmap->setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView( _pixmap , Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }
}

/* ------------- START DUMMY --------------------
 * DUMMY buttons to navigate to other windows */
void MainWindow::on_pushButton_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    ui->stackedWidget->setCurrentIndex(UIViews::NORMAL);
}

void MainWindow::on_pushButton_2_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    ui->stackedWidget->setCurrentIndex(UIViews::INTER);
}

void MainWindow::on_pushButton_3_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    ui->stackedWidget->setCurrentIndex(UIViews::IMGFILT);
}

void MainWindow::on_pushButton_4_clicked() {
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    ui->stackedWidget->setCurrentIndex(UIViews::SHAR);
}

void MainWindow::onHome_pressed(){
//    ui->graphicsView->set
    ui->graphicsView->scene()->addItem(_welcome_img);
    ui->graphicsView->fitInView(_welcome_img, Qt::KeepAspectRatio);
    ui->stackedWidget->setCurrentIndex(UIViews::WELCOME);
}

void MainWindow::onInter_mode_pressed(){
    ui->stackedWidget->setCurrentIndex(UIViews::INTER);
}

void MainWindow::onImgFilt_mode_pressed(){
    ui->stackedWidget->setCurrentIndex(UIViews::IMGFILT);
}

void MainWindow::onShar_mode_pressed(){
    ui->stackedWidget->setCurrentIndex(UIViews::SHAR);
}

/* ----------------- END DUMMY --------------------- */
