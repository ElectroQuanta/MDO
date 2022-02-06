#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "normalwindow.h"
#include "interwindow.h"
#include "imgfiltwindow.h"
#include "sharwindow.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <opencv2/objdetect.hpp>
#include <qfiledialog.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qwidget.h>

/**< OpenCV */
#include <opencv2/opencv.hpp>

/**< Pthreads */
#include <pthread.h>
#include "pEvent.h"

/**< STL containers */
#include <vector>
#include <list>

/**< Image filter */
#include "imgfilter.h"

/**< Twitter */
#include "include/twitcurl.h"

/**< Post */
#include "post.h"

/**< Imagemagick (for GIF generation) */
#include <Magick++.h>

/**< VideoPlayer */
#include <QMediaPlayer>
#include <QMediaPlaylist>
//#include <QUrl>

/**< Ad */
#include "ad.h"

/**< Fragrance */
#include "frag.h"
#include "fragManager.h"
#include "fragDiffuser.h"

/**< Client Server Architecture */
/* Cant use Linux system call connect() due to naming clashes with
 * Qt connect() function
 */
#include <QTcpSocket>

/**
 * @brief App modes
 *
 * Used to handle application logic and UIs views
 * - WELCOME = 0,  Welcome screen; displayed when no ad is running
 * - NORMAL,       Reproduces video in fullscreen (with audio)
 * - INTER,        Interaction mode: main menu; picture mode; GIF mode
 * - IMGFILT,      Image filtering menu
 * - SHAR,         Sharing mode: main menu; editing post; status
 * - QUIT          Quit application
 */
enum AppMode { WELCOME = 0, NORMAL, INTER, IMGFILT, SHAR, QUIT };
typedef enum AppMode AppMode_t;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    
/* ----- DUMMY ------------- */
    void on_pushButton_clicked(); /**< Dummy button to go to Normal Mode */
    void on_pushButton_2_clicked(); /**< Dummy button to go to Interaction Mode */
    void on_pushButton_3_clicked(); /**< Dummy button to go to ImgFilt Mode */
    void on_pushButton_4_clicked(); /**< Dummy button to go to Sharing Mode */
    void onHome_pressed(); /**< slot to handle dummy signal to return to main window */
/* ----- END DUMMY ------------- */

    /**< Signals handlers */
    void onNormalMode_pressed();
    void onInter_mode_pressed();
    void onShar_mode_pressed();
    void onImgFilt_mode_pressed();
    void onCam_started();
    void onImgFiltSelected(int idx);
    void onTwitterShare(const QString &);
    void onTakePic_complete();
    void onImgFiltGlobal(bool enable);
    void onGifEnabled(bool enable);
    void onMediaPlayerStateChanged(QMediaPlayer::State state);
    void OnMediaStatusChanged(QMediaPlayer::MediaStatus status);
    //void onFragTimerStart(int);
    void onFragTimerElapsed();
    void onCheckModeTimerElapsed();
    void onRemoteConnectionStateChanged(QAbstractSocket::SocketState);
    void onRemoteConnected();
    void OnTcpDataAvail();

    bool eventFilter(QObject *, QEvent *);

    /**< Display image */
    void displayImg(cv::Mat frame);

    /**< ImgFilter */
    void createFilters();
    void detectFaces(cv::Mat *frame);
    void transparentOv(cv::Mat *src, cv::Mat *dst, cv::Mat *overlay);
    void applyFilterOverlay(cv::Mat &frame, ImgFilter &filt);

    /**< Thread workers */
    static void* frame_grabber_worker_thr(void* arg);
    //static void* gesture_recog_worker_thr(void* arg);
    //static void* twitter_worker_thr(void* arg);
    static void* gif_save_worker_thr(void* arg);
    //static void* video_manager_worker_thr(void* arg);
    //static void* frag_diff_worker_thr(void* arg);
    //static void* check_mode_worker_thr(void *arg);
    static void* rx_worker_thr(void* arg);
    static void* process_worker_thr(void* arg);
    static void* download_ad_worker_thr(void* arg);

    /**< Twitter sharing */
    bool TwitterAuthenticate();

    /**< recognize gestures */
    void recognizeGesture(cv::Mat &frame);

    /**< GIF */
    void Mat2Magick(cv::Mat& src, Magick::Image &mgk);

    /**< Scene */
    void updateScene(AppMode_t mode);

    /**< VideoPlayer */
    bool openVideo(const QString fname);

    /**< Client-server */
    void connectToRemote();
    void pushTcpData(const QString &s);
    void popTcpData(QString &s);

    /**< Helpers */
    void updateStatusBar(const QString str);
    AppMode_t appMode();
    void setAppMode(AppMode_t mode);
    void filterEnable(bool enable);
    bool filterEnabled();
    void curAd(Ad &ad);
    void setCurAd(Ad &ad);
    void curFrag(Frag::Fragrance &f);
    void setCurFrag(Frag::Fragrance &f);
    //bool eventDiff();
    //void enableEventDiff(bool);
    bool detectUser();

/**
 * @brief Compare rectangles by area (descending)
 * @param a: first rectangle to compare
 * @param b: second rectangle to compare
 * @return comparison result: true if first rectangle area is bigger than second one, otherwise false;
 *
 * detailed
 */
inline static bool compareRects(const cv::Rect &a, const cv::Rect &b){
    return a.area() - b.area();
}

signals:
    void interWindUpdateStatus(const QString str);
    void textChanged(QString);
    void imgGrabbed(cv::Mat frame);
    //void fragTimerStart(int);

private:
    Ui::MainWindow *ui = nullptr; /**< UI main view */
    NormalWindow *_normalWind = nullptr; /**< Normal Window ptr */
    InterWindow *_interWind = nullptr; /**< Normal Window ptr */
    ImgFiltWindow *_imgFiltWind = nullptr; /**< Normal Window ptr */
    SharWindow *_sharWind = nullptr; /**< Normal Window ptr */

    QGraphicsPixmapItem *_pixmap = nullptr; /**< Holds the grabbed frames */
    QGraphicsPixmapItem *_welcome_img = nullptr; /**< Welcome img for the UI */

    cv::VideoCapture _video; /**< CV video object to handle video */
    cv::CascadeClassifier _face_cascade; /**< Haar cascade to detect faces */
    cv::CascadeClassifier _gesture_cascade; /**< Haar cascade to detect faces */

    AppMode_t _appmode; /**< Stores app mode */


    /**< Threads */
    pthread_t _frame_grab_thr; /**< Frame Grabber thread */
    //pthread_t _gesture_recog_thr; /**< Gesture recognition thread */
    //pthread_t _twitter_thr; /**< Twitter sharing thread */
    pthread_t _gif_save_thr; /**< GIF save thread */
    //pthread_t _video_manager_thr; /**< Video manager thread */
    //pthread_t _frag_diff_thr; /**< Fragrance diffusion thread */
    pthread_t _rx_thr; /**< Receive from Remote System thread */
    pthread_t _process_rx_thr; /**< Process rx thread */
    pthread_t _download_ad_thr; /**< Download Ad thread */
    //pthread_t _check_mode_thr; /**< Check normal mode thread */
    //pthread_t _check_normal_mode_thr; /**< Check normal mode thread */
    //pthread_t _check_interaction_mode_thr; /**< Check interaction thread */
    std::vector<pthread_t *> _threads;

    /**< Mutexes */
    /* Normal */
    pthread_mutex_t _m_status_bar; /**< Protects access to UI status bar */
    pthread_mutex_t _m_canvas; /**< Protects access to Graphics view */
    pthread_mutex_t _m_mode; /**< Protects access to mode state variable */
    pthread_mutex_t _m_curFrame; /**< Protects access to current frame */
    pthread_mutex_t _m_imgFilter; /**< Protects access to img filter */
    pthread_mutex_t _m_gif; /**< Protects access to GIF resources */
    pthread_mutex_t _m_cur_ad; /**< Protects access to current Ad */
    pthread_mutex_t _m_cur_frag; /**< Protects access to current Frag */
    pthread_mutex_t _m_event_diff; /**< Protects access to current Ad */
    pthread_mutex_t _m_tcp_buff; /**< Protects access to the TCP buffer */
    std::vector<pthread_mutex_t *> _mutexes;
    /* For condition variables */
    //pthread_mutex_t _m_cond_cam_started;
    //pthread_mutex_t _m_cond_gif_save;

    /**< Pthread events: Condition variables */
    //pthread_cond_t _cond_cam_started;
    //pthread_cond_t _cond_gif_save;
    pEvent *_ev_gif_save; /**< Event GIF save */
    pEvent *_ev_frame_grab; /**< Event Frame Grabber */
    pEvent *_ev_diff; /**< Event Fragrance diffuser */
    pEvent *_ev_rx; /**< Event Rx: data received from remote system */
    pEvent *_ev_download; /**< Event Download: download a new Ad */
    pEvent *_ev_process; /**< Event process: Process Rx data */
//    pEvent *_ev_mode_check; /**< Event Check mode: checks periodically if normal mode or interaction mode must be set */
//    pEvent *_ev_normal_mode_on;
//    pEvent *_ev_interaction_mode; /**< Event Interaction mode: check periodically if a user was detected */
//    pEvent *_ev_user_detected; /**< Event User detected: signals a user was detected */


    /**< Filters */
    QString _filtName; /**< Filter name */
    cv::Mat _filter;
    std::vector<ImgFilter> _filters;
    int _filters_idx;
    bool _filter_on;

    /**< Scenes */
    QGraphicsScene *_welcome_scene = nullptr;
    QGraphicsScene *_video_scene = nullptr;
    QGraphicsScene *_inter_scene = nullptr;

    /**< Image Acquisition */
    cv::Mat _curFrame;
    bool _updateCanvas;

    /**< GIF */
    bool _gif_on;
    bool _gif_complete;
    std::vector<cv::Mat> frames;
    std::list<Magick::Image> images; 

    /**< Twitter obj */
    twitCurl _twitterObj;
    bool _twitterAuthenticated;

    /**< Post */
    Post _post;

    /**< VideoPlayer */
    QMediaPlayer *_mediaPlayer = nullptr;
    QMediaPlaylist *_mediaPlaylist = nullptr;
    QGraphicsVideoItem *_videoItem = nullptr;

    /**< Ad */
    Ad _curAd;
    Frag::Fragrance _curFrag;

    /**< Fragrance */
    Frag::Manager *_fragMan = nullptr;
    Frag::Diffuser *_fragDiff = nullptr;
    QTimer *_fragTimer = nullptr;
    bool _event_diff = false;

    /**< Normal mode */
    QTimer *_checkModeTimer; /**< Check periodically if normal mode needs to run */

    /**< Client-Server: Local system is the client */
    /* Cant use Linux system call connect() due to naming clashes with
     * Qt connect() function
     */
    //int _fd_serv;
    QTcpSocket *_remoteSock;
    bool _remoteConnected;
    QStringList *_remoteDataBuff;
};
#endif // MAINWINDOW_H
