#ifndef IMGFILTWINDOW_H
#define IMGFILTWINDOW_H

#include <QWidget>

namespace Ui {
class ImgFiltWindow;
}

class ImgFiltWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImgFiltWindow(QWidget *parent = nullptr);
    ~ImgFiltWindow();

private slots:
    void on_pb_cancel_share_clicked();

    void on_pb_img_filt_clicked();

    void on_pb_img_filt_2_clicked();

    void on_pb_img_filt_3_clicked();

//    void on_pb_img_filt_4_clicked();

    void on_pb_img_filt_5_clicked();

    void on_pb_cancel_share_2_clicked();

    //   void on_pb_img_filt_10_clicked();

    void on_pb_img_filt_6_clicked();

    void on_pb_img_filt_7_clicked();

    void on_pb_img_filt_8_clicked();

    void on_pb_img_filt_9_clicked();

    /**< dummy */
    //void on_pushButton_clicked();

signals:
    void inter_mode_pressed();
    void imgFiltSelected(int);

private:
    Ui::ImgFiltWindow *ui;
};

#endif // IMGFILTWINDOW_H
