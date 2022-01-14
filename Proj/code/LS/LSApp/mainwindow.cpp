#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <opencv2/videoio.hpp>
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qwidget.h>
#include <qdebug.h>

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
#define SCENE_RES_W 800 /**< Height in pixels */

// /**
// * @brief Enumeration of the UI Views the MainWindow controls
// */
//enum UIViews {
//  WELCOME = 0, /**< Welcome screen; displayed when no ad is running */
//  NORMAL,      /**< Reproduces video in fullscreen (with audio) */
//  INTER,       /**< Interaction mode: main menu; picture mode; GIF mode */
//  IMGFILT,     /**< Image filtering menu */
//  SHAR         /**< Sharing mode: main menu; editing post; status */
//};

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
    ui->stackedWidget->setCurrentIndex(AppMode::WELCOME);

    /**< Instantiate other UI Windows */
    _normalWind = new NormalWindow();
    _interWind = new InterWindow();
    _imgFiltWind = new ImgFiltWindow();
    _sharWind = new SharWindow();

    /**< Add more UI views */
    ui->stackedWidget->insertWidget(AppMode::NORMAL, _normalWind);
    ui->stackedWidget->insertWidget(AppMode::INTER, _interWind);
    ui->stackedWidget->insertWidget(AppMode::IMGFILT, _imgFiltWind);
    ui->stackedWidget->insertWidget(AppMode::SHAR, _sharWind);

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
    // connect(_interWind, SIGNAL(cam_start() ),
    //         this, SLOT( onCam_started() ) );
    connect(this, SIGNAL(textChanged(QString)), ui->label_status,
            SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(imgGrabbed(QImage)), this,
            SLOT(displayImg(QImage)), Qt::QueuedConnection);

    //connect()

    /**< Initializing mode */
    _appmode = AppMode::WELCOME;

    /**< Mutexes initialization */
    pthread_mutex_init(&_m_status_bar, NULL);
    pthread_mutex_init(&_m_canvas, NULL);
    pthread_mutex_init(&_m_mode, NULL);
    pthread_mutex_init(&_m_cond_cam_started, NULL);

    /**< Condition variables initialization */
    pthread_cond_init( &_cond_cam_started, 0);
    //_cond_cam_started = PTHREAD_COND_INITIALIZER;


    /**< Initialize graphics view */
    /* Load resource images */
    QImage img = QImage(WELCOME_IMG_PATH);
    _welcome_img = new QGraphicsPixmapItem( QPixmap::fromImage(img) );
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(_welcome_img);
    ui->graphicsView->fitInView(_welcome_img, Qt::KeepAspectRatio);
      /**< Adding the img container to the scene */
      // ui->graphicsView->scene()->removeItem(_welcome_img);
      ui->graphicsView->scene()->addItem(&_pixmap);
      //ui->graphicsView->installEventFilter(eventFilter);




    /**< Threads */
    /*--*
     *-- @brief create thread
     *-- @param new_thread: pointer to a newly created thread
     *-- @param attr: thread attributes
     *-- @param start_routine: ptr to a thread worker function
     *-- @param arg: argument to pass to the thread (ptr)
     *-- @return status: indicates the creation status (int)
     */
    pthread_create( &_frame_grab_thr, NULL,
                    &MainWindow::frame_grabber_worker_thr, this );
    
}

MainWindow::~MainWindow() {

    /**< Getting the mode to decide flow */;
    pthread_mutex_lock( &this->_m_mode);
    this->_appmode = AppMode::QUIT;
    pthread_mutex_unlock( &this->_m_mode);

    /**< Waiting for threads to finish along with the UI */
    pthread_join( _frame_grab_thr, NULL);

    //qDebug() << "Destructor called" << endl;

    if( _video.isOpened() )
        _video.release();

    delete ui;
}


void MainWindow::onCam_started(){
    using namespace cv;


    /**< Checking if video was previously opened */
    if(_video.isOpened()){
        _video.release();
        return;
    }
    
    /**< Open camera to capture video */
    //if(! _video.open( CAM_IDX , cv::CAP_FFMPEG)){
    if(! _video.open( CAM_IDX , cv::CAP_V4L2)){
        ui->label_status->setText("Status:  ERROR: could not open camera...");
        return;
    }
    else{
        ui->label_status->setText("Status:  Camera OK!");
    }

    /**< Adding the img container to the scene */
    //ui->graphicsView->scene()->removeItem(_welcome_img);
    ui->graphicsView->scene()->addItem(&_pixmap);


    Mat frame;
    while(_video.isOpened())
    {
        _video >> frame;
        if(!frame.empty())
        {
            //copyMakeBorder(frame,
            //               frame,
            //               frame.rows/2,
            //               frame.rows/2,
            //               frame.cols/2,
            //               frame.cols/2,
            //               BORDER_REFLECT);
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            _pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );

            /**< Aspect ratio */
            /* KeepAspectRatio is what works best */
            ui->graphicsView->fitInView( &_pixmap , Qt::KeepAspectRatio);
            //ui->graphicsView->fitInView( &_pixmap ,
            //                             Qt::KeepAspectRatioByExpanding);
            // ui->graphicsView->fitInView( &_pixmap ,
            //                              Qt::IgnoreAspectRatio);
        }
        qApp->processEvents(); 
    }
}

/**
 * @brief Frame grabber thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * detailed
 */
void* MainWindow::frame_grabber_worker_thr(void *arg){

    using namespace cv;
    MainWindow *mw = (MainWindow *)arg;

    AppMode_t _mode = AppMode::INTER;
    Mat frame;
    QString label_text;
    #define COLS 1280
    #define ROWS 720
    #define STEP 3840

    while(1){

        /**< Getting the mode to decide flow */;
        pthread_mutex_lock( &mw->_m_mode);;
        _mode = mw->_appmode;
        pthread_mutex_unlock( &mw->_m_mode);

        /**< If App was quitted, terminate thread */
        if(_mode == AppMode::QUIT) 
            return NULL;

        /**< Check for interaction mode */
        if(_mode == AppMode::INTER){

          if (mw->_video.isOpened()) {
            /**< Acquiring frame */
            mw->_video >> frame;
            if (!frame.empty()) {
                QImage qimg(frame.data, frame.cols, frame.rows, frame.step,
                            QImage::Format_RGB888);
                //img.fromData(frame.data, COLS*ROWS*3);
              //qDebug() << frame.cols << ',' // 1280
              //         << frame.rows << ',' // 720
              //         << frame.step ; // 3840
              emit mw->imgGrabbed(qimg);
            }
          }
          else{
              /**< Open camera to capture video */
              // Adding the CAP_V4L2 solved the GStreamer issue
              // src: https://stackoverflow.com/a/65033057/17836786
              if (!mw->_video.open(CAM_IDX, CAP_V4L2)) {
                  label_text = "Status:  ERROR: could not open camera...";
              } else {
                  //mw->ui->label_status->setText("Status:  Camera OK!");
                  label_text = "Status:  Camera OK!";
              }
              emit(mw->textChanged(label_text));
          }
        } else {
          /**< If video was opened but we changed mode, close video feed */
          if (mw->_video.isOpened())
              mw->_video.release();
        }
    }

    return NULL;
}
 
void MainWindow::displayImg(QImage img){
    this->_pixmap.setPixmap(QPixmap::fromImage(img.rgbSwapped()));

    /**< Aspect ratio */
    /* KeepAspectRatio is what works best */
    this->ui->graphicsView->fitInView(&this->_pixmap,
                                              Qt::KeepAspectRatio);
    
}

/* ------------- START DUMMY --------------------
 * DUMMY buttons to navigate to other windows */
void MainWindow::on_pushButton_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::NORMAL;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

    
    ui->stackedWidget->setCurrentIndex(AppMode::NORMAL);
}

void MainWindow::on_pushButton_2_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);


    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::INTER;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

    /**< Signaling start condition for worker thread */
    pthread_mutex_lock( &this->_m_cond_cam_started );
     //while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
     //{
    pthread_cond_signal( &this->_cond_cam_started );
        //}
    pthread_mutex_unlock( &this->_m_cond_cam_started );
    //onCam_started();
}

void MainWindow::on_pushButton_3_clicked(){
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);


    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::IMGFILT;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::on_pushButton_4_clicked() {
    /**< Remove background image from Welcome screen */
    ui->graphicsView->scene()->removeItem(_welcome_img);

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::SHAR;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::onHome_pressed(){
    //ui->graphicsView->hide();
//    ui->graphicsView->fitInView( ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio );
    ui->graphicsView->scene()->addItem(_welcome_img);
    ui->graphicsView->fitInView(_welcome_img, Qt::IgnoreAspectRatio);
    //ui->graphicsView->show();

    /**< Clear status bar */
    emit(textChanged(""));

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::WELCOME;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::onInter_mode_pressed(){

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::INTER;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);
}

void MainWindow::onImgFilt_mode_pressed(){

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::IMGFILT;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);
    
}

void MainWindow::onShar_mode_pressed(){

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::SHAR;
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);
}

/* ----------------- END DUMMY --------------------- */

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
        if (event->type() == QEvent::Show){
            ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),
                                        Qt::IgnoreAspectRatio);
            return true;
        }

        if (event->type() == QEvent::Resize){
            ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(),
                                        Qt::IgnoreAspectRatio);
            return true;
        }
        return false;
}
