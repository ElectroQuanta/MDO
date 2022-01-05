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

signals:
    void interWindUpdateStatus(const QString str);

private:
    Ui::MainWindow *ui; /**< UI main view */
    NormalWindow *_normalWind; /**< Normal Window ptr */
    InterWindow *_interWind; /**< Normal Window ptr */
    ImgFiltWindow *_imgFiltWind; /**< Normal Window ptr */
    SharWindow *_sharWind; /**< Normal Window ptr */

    QGraphicsPixmapItem *_pixmap;
    QGraphicsPixmapItem *_welcome_img;

    cv::VideoCapture _video; /**< CV video object to handle video */
};
#endif // MAINWINDOW_H
