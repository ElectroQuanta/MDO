#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qwidget.h>
#include <qdebug.h>

#include "imgfilter_defs.h" /**< For filters definition */

/**< Define relevant paths */
#define WELCOME_IMG_PATH ":/resources/img/welcome.png"
#define FACE_CASCADE_FNAME "../models/haarcascade_frontalface_alt.xml"
#define FILTERS_PATH_PREFIX "../filters/"


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
    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(this, SIGNAL(textChanged(QString)), ui->label_status,
            SLOT(setText(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(imgGrabbed(cv::Mat)), this,
            SLOT(displayImg(cv::Mat)), Qt::QueuedConnection);
    connect(_imgFiltWind, SIGNAL(imgFiltSelected(int)),
            this, SLOT(onImgFiltSelected(int)) );

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

     /**< Initialize CV cascades */
    if( !_face_cascade.load( FACE_CASCADE_FNAME ) )
    {
      ui->label_status->setText("Status:  ERROR:  Could not load face cascade");
    };

    /**< Create filters */
    createFilters();

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

void MainWindow::createFilters(){

    /**< Mustache */
    ImgFilter imgfilt = ImgFilter(
        FILTER_MUSTACHE_FNAME,
        FILTER_MUSTACHE_WIDTH_OFFSET, FILTER_MUSTACHE_HEIGHT_OFFSET,
        FILTER_MUSTACHE_SCALE_WIDTH, FILTER_MUSTACHE_SCALE_HEIGHT
        );
    /**< Glasses */
    ImgFilter imgfilt2 = ImgFilter(
        FILTER_GLASSES_FNAME,
        FILTER_GLASSES_WIDTH_OFFSET, FILTER_GLASSES_HEIGHT_OFFSET,
        FILTER_GLASSES_SCALE_WIDTH, FILTER_GLASSES_SCALE_HEIGHT
        );
    /**< Pig */
    ImgFilter imgfilt3 = ImgFilter(
        FILTER_PIG_FNAME,
        FILTER_PIG_WIDTH_OFFSET, FILTER_PIG_HEIGHT_OFFSET,
        FILTER_PIG_SCALE_WIDTH, FILTER_PIG_SCALE_HEIGHT
        );

    for(int i = 0; i < 4; i++){
        _filters.push_back(imgfilt);
        _filters.push_back(imgfilt2);
        _filters.push_back(imgfilt3);
    }

    _filters_idx = 0;
}

void MainWindow::detectFaces(cv::Mat *frame){
    using namespace cv;
    Mat frame_gray;
    cvtColor( *frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
//void cv::CascadeClassifier::detectMultiScale 	( 	InputArray  	image,
//		std::vector< Rect > &  	objects,
//		double  	scaleFactor = 1.1,
//		int  	minNeighbors = 3,
//		int  	flags = 0,
//		Size  	minSize = Size(),
//		Size  	maxSize = Size() 
//	) 	
    std::vector<Rect> faces;
    _face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0,
                                    Size(150,150) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( *frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4 );
    }
}

void MainWindow::transparentOv(cv::Mat *src, cv::Mat *dst, cv::Mat *overlay) {
  for (int y = 0; y < src->rows; y++) {
    /**< Get src, overlay and dst pixels */
    const cv::Vec3b *src_pixel = src->ptr<cv::Vec3b>(y);
    const cv::Vec4b *ovl_pixel = overlay->ptr<cv::Vec4b>(y);
    cv::Vec3b *dst_pixel = dst->ptr<cv::Vec3b>(y);

    for (int x = 0; x < src->cols;
         x++, ++src_pixel, ++ovl_pixel, ++dst_pixel) {
        /**< Get transparency val (alpha) from overlay */
      double alpha = (*ovl_pixel).val[3] / 255.0;

     /**< For every channel */
      for (int c = 0; c < 3; c++) {
          /**< Apply blending equation */
        (*dst_pixel).val[c] = (uchar)((*ovl_pixel).val[c] * alpha +
                                      (*src_pixel).val[c] * (1.0 - alpha));
      }
    }
  }
}

void MainWindow::applyFilterOverlay(cv::Mat &frame, ImgFilter &filt) {
    using namespace cv;
    #define FACE_MIN_SIZE 100 /**< face min size (in pixels) */
    #define FACE_MIN_NEIGHBORS 3
    #define FACE_SCALE_FACTOR 1.1
    #define FACE_FLAGS 0
    
    Mat frame_gray, roi;
    Mat overlay = filt.Mat().clone();
    std::vector<Rect> faces;
    
    /**< Detect faces and draw them */
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    this->_face_cascade.detectMultiScale( frame_gray, faces,
                                          FACE_SCALE_FACTOR,
                                    FACE_MIN_NEIGHBORS, FACE_FLAGS,
                                    Size(FACE_MIN_SIZE, FACE_MIN_SIZE) );

    for (size_t i = 0; i < faces.size(); i++) {
      // rectangle( frame, faces.at(i), (255, 0, 255), 2);

      int x = faces.at(i).x;
      int y = faces.at(i).y;
      int h = faces.at(i).height;
      int w = faces.at(i).width;

      /**< Resize filter to match a scale of ROI (face) */
      cv::resize(filt.Mat(), overlay,
                 cv::Size( ((int)(filt.scale_width() * w)),
                           ((int)(filt.scale_height() * h)) ),
                 0, 0, cv::INTER_CUBIC);

      /**< Extract ROI from frame */
      Rect roiRect = Rect(x + filt.width_offset_coef() * w,
                          y + filt.height_offset_coef() * h,
                          overlay.cols, overlay.rows);
      roi = frame(roiRect);

      /**< Apply overlay over ROI and then over frame */
      transparentOv(&roi, &roi, &overlay);
      // src: https://stackoverflow.com/a/10482252/17836786
      roi.copyTo(frame(roiRect));
    }
}

void MainWindow::onImgFiltSelected(int idx){
    _filters_idx = idx;
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

        /**< Check for interaction or img filter modes */
        if(_mode == AppMode::INTER || _mode == AppMode::IMGFILT){

          if (mw->_video.isOpened()) {
            /**< Acquiring frame */
            mw->_video >> frame;
            if (!frame.empty()) {
                emit mw->imgGrabbed(frame);
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
 
void MainWindow::displayImg(cv::Mat frame){

    if(_appmode == AppMode::IMGFILT)
        this->applyFilterOverlay(frame, _filters[_filters_idx]);
            //this->detectFaces(&frame);

    QImage qimg(frame.data, frame.cols, frame.rows, frame.step,
                            QImage::Format_RGB888);
                //img.fromData(frame.data, COLS*ROWS*3);
              //qDebug() << frame.cols << ',' // 1280
              //         << frame.rows << ',' // 720
              //         << frame.step ; // 3840

    this->_pixmap.setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));

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
