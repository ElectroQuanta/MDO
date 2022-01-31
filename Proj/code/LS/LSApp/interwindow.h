#ifndef INTERWINDOW_H
#define INTERWINDOW_H

#include <QWidget>
#include <qpixmap.h>
#include <qwindowdefs.h>
#include <QTimer>

namespace Ui {
class InterWindow;
}

class InterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InterWindow(QWidget *parent = nullptr);
    ~InterWindow();

    //void updatePicLabel(QPixmap pixmap);
    void updatePicLabel(QString fname);

private slots:
    /**< UI */
    void on_pb_take_pic_clicked();
    void on_pb_img_filt_clicked();
    void on_pb_pic_cancel_clicked();
    void on_pb_pic_share_clicked();
    void on_pb_gif_cancel_clicked();
    void on_pb_gif_share_clicked();
    void on_pb_create_gif_clicked();

    /**< Signal handlers */
    //void oninterWindUpdateStatus(const QString str);
    void onPicTimerElapsed();

    /**< Dummy */
    void on_pushButton_clicked();

    /**< Helpers */
    void enablePushbuttons(bool enable);

signals:
    void shar_mode_pressed();
    void imgfilt_mode_pressed();
    void home_pressed();
    void cam_start();
    void takePic_complete();

private:
    Ui::InterWindow *ui;

    QTimer *_pic_timer;
    int _pic_time_remaining;
};

#endif // INTERWINDOW_H
