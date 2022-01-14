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
#include <qgraphicsitem.h>
#include <qwidget.h>

/**< OpenCV */
#include <opencv2/opencv.hpp>

/**< Pthreads */
#include <pthread.h>

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
    void onInter_mode_pressed();
    void onShar_mode_pressed();
    void onImgFilt_mode_pressed();
    void onCam_started();
    void displayImg(QImage);

    bool eventFilter(QObject *, QEvent *);

    static void* frame_grabber_worker_thr(void* arg);

signals:
    void interWindUpdateStatus(const QString str);
    void textChanged(QString);
    void imgGrabbed(QImage);

private:
    Ui::MainWindow *ui; /**< UI main view */
    NormalWindow *_normalWind; /**< Normal Window ptr */
    InterWindow *_interWind; /**< Normal Window ptr */
    ImgFiltWindow *_imgFiltWind; /**< Normal Window ptr */
    SharWindow *_sharWind; /**< Normal Window ptr */

    QGraphicsPixmapItem _pixmap; /**< Holds the grabbed frames */
    QGraphicsPixmapItem *_welcome_img; /**< Welcome img for the UI */

    cv::VideoCapture _video; /**< CV video object to handle video */

    AppMode_t _appmode; /**< Stores app mode */

    /**< Mutexes */
    /* Normal */
    pthread_mutex_t 	_m_status_bar; /**< Protects access to UI status bar */
    pthread_mutex_t 	_m_canvas; /**< Protects access to Graphics view */
    pthread_mutex_t 	_m_mode; /**< Protects access to mode state variable */
    /* For condition variables */
    pthread_mutex_t _m_cond_cam_started;

    /**< Condition variables */
    pthread_cond_t _cond_cam_started;

    /**< Threads */
    pthread_t _frame_grab_thr; /**< Frame Grabber thread */
};
#endif // MAINWINDOW_H
