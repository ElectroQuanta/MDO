/**
 * @brief Frame grabber thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * detailed
 */
void* MainWindow::frame_grabber_worker_thr(void *arg){
    using namespace cv;
    MainWindow *mw = (MainWindow *)arg;
    AppMode_t mode = AppMode::INTER;
    Mat frame;
    QString label_text;

    while(1){
        /**< Getting the mode to decide flow */;
        mode = mw->appMode();
        /**< If App was quitted, terminate thread */
        if(mode == AppMode::QUIT) 
            return NULL;
        /**< Check for interaction or img filter modes */
        if(mode == AppMode::INTER || mode == AppMode::IMGFILT
           || mode == AppMode::SHAR){
          if (mw->_video.isOpened()) {
            /**< Acquiring frame */
            mw->_video >> frame;
            if (!frame.empty()) {
                emit mw->imgGrabbed(frame);
            }
          }
          else{
              /**< Open camera to capture video */
              if (!mw->_video.open(CAM_IDX, CAP_V4L2)) {
                  label_text = "ERROR: could not open camera...";
              } else {
                  mw->_video.set(cv::CAP_PROP_FRAME_WIDTH, CAMERA_RES_W);
                  mw->_video.set(cv::CAP_PROP_FRAME_HEIGHT, CAMERA_RES_H);
                  label_text = "Camera OK!";
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
 * @brief Rx worker thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * Handles Rx connection
 */
void* MainWindow::rx_worker_thr(void *arg){
    MainWindow *mw = (MainWindow *)arg;
    QString data;
    while(1){
        /**< Wait for RX signal */
        mw->_ev_rx->WaitForSignal();
        /**< Read TCP data and push it to vector */
        while( mw->_remoteSock->canReadLine() ){
            data =  QString( mw->_remoteSock->readLine() );
            std::cout << "Rx Data: " << data.toStdString()
                      << std::endl;
            mw->pushTcpData( data );
        }
        /**< Trigger Processing thread */
        mw->_ev_process->Signal();
    }
    return NULL;
}
/**
 * @brief Process worker thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * Processes Rx data
 */
void* MainWindow::process_worker_thr(void *arg){
    MainWindow *mw = (MainWindow *)arg;
    QString data;
#define CMD_AD "A"
    QStringList list;
    std::string link;
    while(1){
        /**< Wait for RX signal */
        mw->_ev_process->WaitForSignal();
        /**< Read TCP data from buffer */
        while( !mw->_remoteDataBuff->empty() ){
            mw->popTcpData( data );
            /**< Parse input */
            list = data.split(',');
            if(list.at(0) == CMD_AD){
               Ad ad(list.at(2).toStdString(),
                     list.at(3).toStdString(),
                     list.at(4).toInt(),
                     list.at(5).toInt(),
                     list.at(6).toInt()
                   );
               /**< Update current Ad and fragrance */
               mw->setCurAd(ad);
               Frag::Fragrance f(ad.fragID());
               mw->setCurFrag( f );
               /**< Download media files */
               mw->_ev_download->Signal();
            }
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
    std::string path;
    while(1){
        /**< Waiting for a UI signal */;
        mw->_ev_gif_save->WaitForSignal();
        /**< Save file to disk */
        mw->_post.setMediaType(MediaType::GIF);
        mw->_post.MediaPath(path);
        writeImages( mw->images.begin(), mw->images.end(), path );
        /**< Update Status */
        mw->updateStatusBar("GIF saved!");
        /**< Reset gif vector */
        mw->images.clear();
        /**< Enable UI pushbuttons again */
        mw->_interWind->updateGIFStatus();
    }
    return NULL;
}
/**
 * @brief Download Ad worker thread function
 * @param arg: ptr to a UI::MainWindow
 *
 * Downloads Ad using curl
 */
void* MainWindow::download_ad_worker_thr(void *arg){
    MainWindow *mw = (MainWindow *)arg;
    std::string link;
    Ad ad;
#define CMD_AD "A"
    QStringList list;
    while(1){
        /**< Wait for Download signal */
        mw->_ev_download->WaitForSignal();
        /**< Get current ad */
        mw->curAd(ad);
        /**< Download link */
        ad.link(link);
        /**< Update status bar */
        mw->updateStatusBar( "Downloaded " + QString::fromStdString(link) );
        std::cout << "Downloaded " << link << std::endl;
    }
    return NULL;
}
