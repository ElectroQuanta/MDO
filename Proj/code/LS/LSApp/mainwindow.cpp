#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qnamespace.h>
#include <qwidget.h>
#include <qdebug.h>
#include <QMouseEvent>

#include "imgfilter_defs.h" /**< For filters definition */

#include <signal.h>
#include <QGraphicsVideoItem>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <type_traits>


/**< Define relevant paths */
#define WELCOME_IMG_PATH ":/resources/img/welcome.png"
#define FACE_CASCADE_FNAME "../models/haarcascade/frontalface_alt.xml"
#define GESTURE_CASCADE_FNAME "../models/haarcascade/closed_frontal_palm.xml"
#define FILTERS_PATH_PREFIX "../filters/"

/**< Define Architecture */
#define ARCH 1 /**< DESKTOP */

/**
 * @brief Screen resolution for embedded display
 *
 * We are using the screen in PORTRAIT MODE
 * - This is done directly in the Qt Designer form
 * @todo: make it dynamic for several resolutions modes and orientations 
 */
#define SCREEN_RES_W 600 /**< Width in pixels */
#define SCREEN_RES_H 1024 /**< Height in pixels */
#define SCENE_RES_H 800  /**< Height in pixels */
#define CAMERA_RES_W 640
#define CAMERA_RES_H 480

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
    connect(_sharWind, SIGNAL( twitterShare(const QString &) ),
            this, SLOT( onTwitterShare(const QString &) ));
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
    connect(_interWind, SIGNAL( takePic_complete() ),
            this, SLOT( onTakePic_complete() ));
    connect(_imgFiltWind, SIGNAL(imgFiltGlobal(bool)),
            this, SLOT(onImgFiltGlobal(bool)) );
    connect(_interWind, SIGNAL( gif_enabled(bool) ),
            this, SLOT( onGifEnabled(bool) ));

    /**< Initializing mode */
    _appmode = AppMode::WELCOME;

    /**< Mutexes initialization */
    pthread_mutex_init(&_m_status_bar, NULL);
    pthread_mutex_init(&_m_canvas, NULL);
    pthread_mutex_init(&_m_mode, NULL);
    pthread_mutex_init(&_m_cond_cam_started, NULL);
    pthread_mutex_init(&_m_curFrame, NULL);
    pthread_mutex_init(&_m_imgFilter, NULL);
    pthread_mutex_init(&_m_gif, NULL);
    //pthread_mutex_init(&_m_cond_gif_save, NULL);

    /**< Condition variables initialization */
    pthread_cond_init( &_cond_cam_started, 0);
    //pthread_cond_init( &_cond_gif_save, 0);
    //_cond_cam_started = PTHREAD_COND_INITIALIZER;


    /**< VideoPlayer */
    _mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    _videoItem = new QGraphicsVideoItem;
    _videoItem->setSize( QSizeF(SCREEN_RES_W-60, SCENE_RES_H-60) );
    //ui->graphicsView->scene()->addItem(_videoItem);
    _mediaPlayer->setVideoOutput(_videoItem);


    /**< Initialize graphics view */
    /* Load resource images */
    QImage img = QImage(WELCOME_IMG_PATH);

    /* Scenes */
    _welcome_scene = new QGraphicsScene(this);
    _video_scene = new QGraphicsScene(this);
    _inter_scene = new QGraphicsScene(this);

    /* Welcome scene */
    _welcome_img = new QGraphicsPixmapItem( QPixmap::fromImage(img) );
    _welcome_scene->addItem(_welcome_img);

    /* Interaction scene */
    _pixmap = new QGraphicsPixmapItem();
    _inter_scene->addItem(_pixmap);

    /* Video scene */
    _video_scene->addItem(_videoItem);


    /**< Setting the scene */
    updateScene(_appmode);

      _updateCanvas = true;

     /**< Initialize CV cascades */
    if( !_face_cascade.load( FACE_CASCADE_FNAME ) )
    {
      ui->label_status->setText("Status:  ERROR:  Could not load face cascade");
    };

    if( !_gesture_cascade.load( GESTURE_CASCADE_FNAME ) )
    {
      ui->label_status->setText("Status:  ERROR:  Could not load gesture cascade");
    };

    /**< Twitter */
    _twitterAuthenticated = TwitterAuthenticate();

    /**< GIF */
    _gif_on = false;
    _gif_complete = false;

    /**< Post */
//    _post = new Post();


    /**< Create filters */
    createFilters();
    _filter_on = false;


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
//    pthread_create( &_gesture_recog_thr, NULL,
//                    &MainWindow::gesture_recog_worker_thr, this );
//    pthread_create( &_twitter_thr, NULL,
//                    &MainWindow::twitter_worker_thr, this );
    pthread_create( &_gif_save_thr, NULL,
                    &MainWindow::gif_save_worker_thr, this );
}

void MainWindow::onImgFiltGlobal(bool enable){
    //std::cout << "ImgFiltGlobal" << std::endl;
    /**< Enabling filter globally */;
    pthread_mutex_lock( &this->_m_imgFilter);
    this->_filter_on = enable;
    pthread_mutex_unlock( &this->_m_imgFilter);
}

MainWindow::~MainWindow() {

    /**< Getting the mode to decide flow */;
    pthread_mutex_lock( &this->_m_mode);
    this->_appmode = AppMode::QUIT;
    pthread_mutex_unlock( &this->_m_mode);

    /**< Waiting for threads to finish along with the UI */
    pthread_join( _frame_grab_thr, NULL);
    //pthread_join( _gif_save_thr, NULL);

    /**< Forcing thread to terminate */
    /* This is required because the thread is thread is instantiated at
     * startup and is waiting for a signal to execute, staying blocked there
     *  - The other approach would be to spawn the thread and execute in
     *    one-shot, dismissing the usage of the condition variable, but
     *    requiring more resources to startup, negatively affecting system's
     *    predictibility and execution time
     *  - NOTE: pthread_kill can be used safely if the appropriate cleanup
     *    handlers are installed using pthread_cleanup_push and
     *    pthread_cleanup_pop to deallocate resources.
     */ 
    pthread_kill( _gif_save_thr, SIGKILL);

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
    _filters_idx = (idx % _filters.size());
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
    //ui->graphicsView->scene()->addItem(_pixmap);

    ui->graphicsView->setScene(_inter_scene);


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
            _pixmap->setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );

            /**< Aspect ratio */
            /* KeepAspectRatio is what works best */
            ui->graphicsView->fitInView( _pixmap , Qt::KeepAspectRatio);
            //ui->graphicsView->fitInView( &_pixmap ,
            //                             Qt::KeepAspectRatioByExpanding);
            // ui->graphicsView->fitInView( &_pixmap ,
            //                              Qt::IgnoreAspectRatio);
        }
        qApp->processEvents(); 
    }
}

void MainWindow::onTakePic_complete(){
    cv::Mat frame;
    std::string path;

    /**< Stop canvas update */
    // pthread_mutex_lock(&_m_canvas);
    // _updateCanvas = false;
    // pthread_mutex_unlock(&_m_canvas);

    /**< Set media Type and get path */
    _post.setMediaType(MediaType::PNG);
    _post.MediaPath(path);

    //std::cout << "Path: " << path << std::endl;

    /**< Get current frame */
    pthread_mutex_lock(&_m_curFrame);
    frame = _curFrame;
    pthread_mutex_unlock(&_m_curFrame);

    /**< Write it to a file */
    cv::imwrite(path, frame);

    /**< Update status bar */
    ui->label_status->setText("Status: Picture taken!");

    /**< Update Label of interaction window */
    _interWind->updatePicLabel(QString::fromStdString(path));
}

void MainWindow::onGifEnabled(bool enable){

    /**< Setting logical variables */;
    pthread_mutex_lock( &_m_gif);
    _gif_on = enable;
    _gif_complete = !enable;

//    std::cout << "GIF: On: "
//              << _gif_on
//              << ", Complete: "
//              << _gif_complete
//              << std::endl;

    pthread_mutex_unlock( &_m_gif);
    
    //if(enable){
    //    _gif_on = true;
    //}else {
    //    _gif_on = false;
    //    _gif_complete = true;
    //}
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
    //#define STEP 3840

    while(1){

        /**< Getting the mode to decide flow */;
        pthread_mutex_lock( &mw->_m_mode);
        _mode = mw->_appmode;
        pthread_mutex_unlock( &mw->_m_mode);

        /**< If App was quitted, terminate thread */
        if(_mode == AppMode::QUIT) 
            return NULL;

        /**< Check for interaction or img filter modes */
        if(_mode == AppMode::INTER || _mode == AppMode::IMGFILT
           || _mode == AppMode::SHAR){

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
                  mw->_video.set(cv::CAP_PROP_FRAME_WIDTH, CAMERA_RES_W);
                  mw->_video.set(cv::CAP_PROP_FRAME_HEIGHT, CAMERA_RES_H);
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

/**
 * @brief Gesture recognition thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * detailed
 */
void* MainWindow::gesture_recog_worker_thr(void *arg){

    using namespace cv;
    MainWindow *mw = (MainWindow *)arg;

    AppMode_t _mode = AppMode::INTER;
    Mat frame;
    QString label_text;

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
                  mw->_video.set(cv::CAP_PROP_FRAME_WIDTH, CAMERA_RES_W);
                  mw->_video.set(cv::CAP_PROP_FRAME_HEIGHT, CAMERA_RES_H);
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

/**
 * @brief GIF save thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * detailed
 */
void* MainWindow::gif_save_worker_thr(void *arg){

    using namespace cv;
    MainWindow *mw = (MainWindow *)arg;

    //Mat frame;
    //QString label_text;

    while(1){

        /**< Waiting for a UI signal */;
        mw->_gif_save_Obj.WaitForSignal();
        //pthread_mutex_lock( &mw->_m_cond_gif_save);
        //pthread_cond_wait( &mw->_cond_gif_save, &mw->_m_cond_gif_save );
        //pthread_mutex_unlock( &mw->_m_cond_gif_save);

        std::string path;

        /**< Save file to disk */
        /*< Set media Type and get path */
        mw->_post.setMediaType(MediaType::GIF);
        mw->_post.MediaPath(path);
        
        writeImages( mw->images.begin(), mw->images.end(), path );

        /**< Update Status */
        pthread_mutex_lock( &mw->_m_status_bar);
        mw->ui->label_status->setText("Status: GIF saved");
        pthread_mutex_unlock( &mw->_m_status_bar);

        /**< Reset gif vector */
        mw->images.clear();

        /**< Enable UI pushbuttons again */
        mw->_interWind->updateGIFStatus();
    }

    return NULL;
}

void MainWindow::displayImg(cv::Mat frame){

    //switch(_appmode){
    //case AppMode::INTER:
    //case AppMode::SHAR:
    //    /**< Store current frame */
    //    pthread_mutex_lock( &_m_curFrame);
    //    _curFrame = frame;
    //    pthread_mutex_unlock( &_m_curFrame);

    //    /**< Recognize gesture */
    //    this->recognizeGesture(frame);
    //    break;
    //case AppMode::IMGFILT:
    //    /**< Recognize gesture */
    //    this->recognizeGesture(frame);

    //    /**< Apply filter */
    //    this->applyFilterOverlay(frame, _filters[_filters_idx]);

    //    /**< Store current frame */
    //    pthread_mutex_lock( &_m_curFrame);
    //    _curFrame = frame;
    //    pthread_mutex_unlock( &_m_curFrame);
    //    break;
    //default:
    //    break;
    //}

    static bool gif_on = false;
    static bool gif_complete = false;
    //static int i = 0;

    /**< Store current frame */
    pthread_mutex_lock( &_m_curFrame);
    _curFrame = frame;
    pthread_mutex_unlock( &_m_curFrame);

    /**< Store GIF status */
    pthread_mutex_lock( &_m_gif);
    gif_on = _gif_on;
    gif_complete = _gif_complete;
    pthread_mutex_unlock( &_m_gif);

    /**< Recognize gesture */
    this->recognizeGesture(frame);

    /**< Apply filter */
    if(_filter_on)
        this->applyFilterOverlay(frame, _filters[_filters_idx]);

    /* GIF management */
    if(gif_on)
    {
        Magick::Image img;

        /**< Push frames to vector */
        //std::cout << "Pushing frame " << ++i << std::endl;

        /**< Converting frame to Image and storing it */
        Mat2Magick(_curFrame, img);
        images.push_back(img);
    }

    if(gif_complete){

        //i = 0;

        /**< Reset flag */
        pthread_mutex_lock( &this->_m_gif);
        this->_gif_complete = false;
        pthread_mutex_unlock( &this->_m_gif);


        /**< Signal event to waiting thread */
        _gif_save_Obj.Signal();
        //pthread_mutex_lock( &this->_m_cond_gif_save);
        //pthread_cond_signal( &this->_cond_gif_save );
        //pthread_mutex_unlock( &this->_m_cond_gif_save);

    }

//    static bool updateCanvas = false;
//    /**< Store current frame */
//    pthread_mutex_lock( &_m_canvas);
//    updateCanvas = _updateCanvas;
//    pthread_mutex_unlock( &_m_canvas);
//
//    if(updateCanvas){

    QImage qimg(frame.data, frame.cols, frame.rows, frame.step,
                QImage::Format_RGB888);

    this->_pixmap->setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));

    /**< Aspect ratio */
    /* KeepAspectRatio is what works best */
    this->ui->graphicsView->fitInView(this->_pixmap, Qt::KeepAspectRatio);
    //   }
}

void MainWindow::recognizeGesture(cv::Mat &frame){
    using namespace cv;
  std::vector<Rect> fists;
    //int i = 0;
  //const static Scalar colors[] = {CV_RGB(0, 0, 255),   CV_RGB(0, 128, 255),
  //                                CV_RGB(0, 255, 255), CV_RGB(0, 255, 0),
  //                                CV_RGB(255, 128, 0), CV_RGB(255, 255, 0),
  //                                CV_RGB(255, 0, 0),   CV_RGB(255, 0, 255)};
  //#define COLORS_SZ 8
  Mat gray;
  Mat smallImg(frame.rows, frame.cols, CV_8UC1);

  cvtColor(frame, gray, COLOR_BGR2GRAY);
  cv::resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
  equalizeHist(smallImg, smallImg);

//  t = (double)getTickCount();

#define FIST_MIN_SIZE 100 /**< face min size (in pixels) */
#define FIST_MIN_NEIGHBORS 3
#define FIST_SCALE_FACTOR 1.1
#define FIST_FLAGS 0

  static int cnt = 0;
  static int iter = 0;
  //static double t = 0;

  _gesture_cascade.detectMultiScale(smallImg, fists,
                           FIST_SCALE_FACTOR, FIST_MIN_NEIGHBORS,
                           FIST_FLAGS
                           |
                               CASCADE_FIND_BIGGEST_OBJECT
                               //|CV_HAAR_DO_ROUGH_SEARCH
                               | CASCADE_SCALE_IMAGE,
                           Size(FIST_MIN_SIZE, FIST_MIN_SIZE));

  iter++;
  #define MAX_ITER 80 /**< 3 seconds: Desktop */

  static cv::Rect gesture(0,0,0,0);

  cv::Point p;

  if( ! fists.empty() )
  {
      cnt++;
      sort(fists.begin(), fists.end(), compareRects);

      gesture = fists.at(0);
      
      #define LINE_THICKNESS 2
      #define LINE_TYPE 8
      #define LINE_SHIFT 0
      //rectangle(frame, gesture, colors[0], LINE_THICKNESS, LINE_TYPE,
      //          LINE_SHIFT);
      
  }
  //t = (double)getTickCount() - t;
  if(iter > MAX_ITER ){
      //cout << "detection time =" << t*1000/getTickFrequency()
      //     << "ms" << endl;
      //cout << "Nr_iter: " << iter << endl;
      //cout << "Cnt: " << cnt << endl;


      if(cnt > iter/3){
          /**< Detected hand gesture */
          //cout << "Hand gesture detected!" << endl;
          //cout << "detection time ="
          //     << ((double)getTickCount()) * 1/getTickFrequency()
          //     << "s" << endl;

          /**< Get middle point */
//#if ARCH == 0
//#define CMDS_BAR_Y (SCREEN_RES_H - 70)
//#elif ARCH == 1
//#define CMDS_BAR_Y (2500 - 70)
//#endif
#define CMDS_BAR_Y (SCREEN_RES_H - 70)
          p.x = gesture.x + gesture.width/2;
          p.y = CMDS_BAR_Y;

          //QString auxStr, auxStr2;

          std::string statusStr = "Status: Gest detected: (x,y): " +
              std::to_string(p.x) + "," + std::to_string(p.y);
          
          ui->label_status->setText(QString::fromStdString(statusStr));

          /**< Emulate mouse press */
          QPoint screenPos = QPoint(p.x, p.y);
          QWidget *targetWidget = QApplication::widgetAt(screenPos);

          if( targetWidget == nullptr){
              //QPoint cursorP = QCursor::pos();
              //std::cout << "Hand: (x,y) = "
              //          << p.x << "," << p.y << std::endl;
              //std::cout << "Cursor: (x,y) = "
              //          << cursorP.x() << "," << cursorP.y() << std::endl;
              //std::cout << "targetWidget not found" << std::endl;
              return;
          }

          QPoint localPos = targetWidget->mapFromGlobal(screenPos);

          QMouseEvent *eventPress =
              new QMouseEvent(QEvent::MouseButtonPress, localPos, screenPos,
                              Qt::LeftButton, Qt::LeftButton,
                              Qt::NoModifier);
          QApplication::postEvent(targetWidget, eventPress);

          QMouseEvent *eventRelease =
              new QMouseEvent(QEvent::MouseButtonRelease, localPos,
                              screenPos,
                              Qt::LeftButton, Qt::LeftButton,
                              Qt::NoModifier);
          QApplication::postEvent(targetWidget, eventRelease);

          // cout << "Rect: (x, y, w, h) = ("
          //      << gesture.x << ", "
          //      << gesture.y << ", "
          //      << gesture.width << ", "
          //      << gesture.height << ")"
          //      << endl;

          // cout << "Middle point: (x, y) = ("
          //      << p.x << ", "
          //      << p.y << ")"
          //      << endl;
      }

      //t = 0;
      cnt = 0; iter = 0;
  }
  
}

bool MainWindow::TwitterAuthenticate(){
    
#define TWITTER_API_FILE "../twitter/api.txt"

    std::string username("");
    std::string password("");
    std::string consumerKey("");
    std::string consumerSecret("");
    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");

    std::ifstream apiFile (TWITTER_API_FILE);
    if( apiFile.is_open() ){
        apiFile >> username;
        apiFile >> password;
        apiFile >> consumerKey;
        apiFile >> consumerSecret;
        apiFile >> myOAuthAccessTokenKey;
        apiFile >> myOAuthAccessTokenSecret;
    }
    else
        return false;

    _twitterObj.setTwitterUsername( username );
    _twitterObj.setTwitterPassword( password );

    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
    _twitterObj.getOAuth().setConsumerKey( consumerKey );
    _twitterObj.getOAuth().setConsumerSecret( consumerSecret );


    _twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
    _twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );

    /* Account credentials verification */
    return _twitterObj.accountVerifyCredGet();
}

void MainWindow::onTwitterShare(const QString &msg) {
    /* Authenticate to Twitter */
    if( ! _twitterAuthenticated ){
        if( ! TwitterAuthenticate() )
          ui->label_status->setText(
              "Status:  ERROR:  Could not authenticate to Twitter");
        return;
    }

    std::string tmpStr;

    _post.Msg(tmpStr);
    tmpStr += msg.toStdString();

  if (_twitterObj.statusUpdate(tmpStr)) {
      ui->label_status->setText("STATUS: post shared!");
  } else {
      ui->label_status->setText("STATUS: ERROR: post not shared! Please try again...");
  }
}

/**
 * @brief Converts OpenCV Mat into Imagemagick Image for GIF generation
 * @param src: cv::Mat frame
 * @param mgk: Magick::Image
 * @return ret
 *
 * detailed
 */
void MainWindow::Mat2Magick(cv::Mat& src, Magick::Image &mgk){
    switch(src.channels() ){
    case 1:
        cv::cvtColor(src,src, cv::COLOR_GRAY2BGR);
        cv::cvtColor(src,src, cv::COLOR_BGR2BGRA);
        mgk = Magick::Image(src.cols, src.rows, "BGRA",
                            Magick::CharPixel, (char *)src.data);
        break;
    case 3:
        cv::cvtColor(src,src, cv::COLOR_BGR2BGRA);
        mgk = Magick::Image(src.cols, src.rows, "BGRA",
                            Magick::CharPixel, (char *)src.data);
        break;
    case 4:
        mgk = Magick::Image(src.cols, src.rows, "BGRA",
                            Magick::CharPixel, (char *)src.data);
        break;
    default:
        break;
    }
}

void MainWindow::updateScene(AppMode_t mode){

    /**< Default state: Welcome */
    QGraphicsScene *scene = _welcome_scene;
    Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio;

    switch (mode){
        //case AppMode::WELCOME :
        //    scene = _welcome_scene;
        //    aspectRatioMode = Qt::IgnoreAspectRatio;
        //    break;
       case AppMode::NORMAL :
           scene = _video_scene;
           aspectRatioMode = Qt::KeepAspectRatio;
           break;
       case AppMode::INTER :
       case AppMode::IMGFILT :
       case AppMode::SHAR :
           scene = _inter_scene;
           aspectRatioMode = Qt::KeepAspectRatio;
           break;
    default:
        break;
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->items().at(0), aspectRatioMode);
}

/* ------------- START DUMMY --------------------
 * DUMMY buttons to navigate to other windows */

/**
 * @brief Navigates to Normal mode (bypassing app logic)
 *
 * Dummy function to help navigate the app
 */
void MainWindow::on_pushButton_clicked(){
//    /**< Remove background image from Welcome screen */
//    ui->graphicsView->scene()->removeItem(_welcome_img);

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::NORMAL;
    updateScene(_appmode);
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

    //QUrl url;
    #define VIDEO_PATH "../ads/media/video.mp4"
    if ( openVideo( QString(VIDEO_PATH) ) )
        _mediaPlayer->play(); /**< Play video */
    else
        ui->label_status->setText("Status: [ERROR] Could not open media");

}

bool MainWindow::openVideo(const QString fname){

//    /**< Open Video File */
//    QFileDialog fileDialog(this);
//    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
//    fileDialog.setWindowTitle(tr("Open Movie"));
//    const QStringList supportedMimeTypes = _mediaPlayer->supportedMimeTypes();
//    if (!supportedMimeTypes.isEmpty())
//        fileDialog.setMimeTypeFilters(supportedMimeTypes);
//    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
//    if (fileDialog.exec() == QDialog::Accepted)
//        url = fileDialog.selectedUrls().constFirst();

    /**< Get the file info */
    QFileInfo fileInfo(fname);
    if( ! fileInfo.exists() )
        return false;

    _mediaPlayer->setMedia(
        QUrl::fromLocalFile(fileInfo.absoluteFilePath())
        );

    return true;
}

void MainWindow::on_pushButton_2_clicked(){
    //ui->graphicsView->scene()->removeItem(_videoItem);

    ///**< Remove background image from Welcome screen */
    //ui->graphicsView->scene()->removeItem(_welcome_img);


    ///**< Change mode before jumping */
    //pthread_mutex_lock( &_m_mode);
    //_appmode = AppMode::INTER;
    //ui->stackedWidget->setCurrentIndex(_appmode);
    //pthread_mutex_unlock( &_m_mode);

    ///**< Signaling start condition for worker thread */
    //pthread_mutex_lock( &this->_m_cond_cam_started );
    // //while( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
    // //{
    //pthread_cond_signal( &this->_cond_cam_started );
    //    //}
    //pthread_mutex_unlock( &this->_m_cond_cam_started );
    //onCam_started();

    onInter_mode_pressed();
}

void MainWindow::on_pushButton_3_clicked(){
    /**< Remove background image from Welcome screen */
//    ui->graphicsView->scene()->removeItem(_welcome_img);


    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::IMGFILT;
    ui->stackedWidget->setCurrentIndex(_appmode);
    updateScene(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::on_pushButton_4_clicked() {
    /**< Remove background image from Welcome screen */
//    ui->graphicsView->scene()->removeItem(_welcome_img);

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::SHAR;
    updateScene(_appmode);
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::onHome_pressed(){
    /**< Stop video */
    _mediaPlayer->stop();

    /**< Clear status bar */
    emit(textChanged(""));

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::WELCOME;
    updateScene(_appmode);
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);

}

void MainWindow::onInter_mode_pressed(){

    /**< Stop video */
    _mediaPlayer->stop();

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::INTER;
    updateScene(_appmode);
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);
}

void MainWindow::onImgFilt_mode_pressed(){

    /**< Enabling filter globally */;
    pthread_mutex_lock( &this->_m_imgFilter);
    this->_filter_on = true;
    pthread_mutex_unlock( &this->_m_imgFilter);

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::IMGFILT;
    updateScene(_appmode);
    ui->stackedWidget->setCurrentIndex(_appmode);
    pthread_mutex_unlock( &_m_mode);
}

void MainWindow::onShar_mode_pressed(){

    /**< Change mode before jumping */
    pthread_mutex_lock( &_m_mode);
    _appmode = AppMode::SHAR;
    updateScene(_appmode);
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
