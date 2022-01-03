#ifndef INTERWINDOW_H
#define INTERWINDOW_H

#include <QWidget>

namespace Ui {
class InterWindow;
}

class InterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InterWindow(QWidget *parent = nullptr);
    ~InterWindow();

private slots:
    void on_pb_take_pic_clicked();

    void on_pb_img_filt_clicked();

    void on_pb_pic_cancel_clicked();

    void on_pb_pic_share_clicked();

    void on_pb_gif_cancel_clicked();

    void on_pb_gif_share_clicked();

    void on_pb_create_gif_clicked();

    /**< Dummy */
    void on_pushButton_clicked();

signals:
    void shar_mode_pressed();
    void imgfilt_mode_pressed();
    void home_pressed();

private:
    Ui::InterWindow *ui;
};

#endif // INTERWINDOW_H
