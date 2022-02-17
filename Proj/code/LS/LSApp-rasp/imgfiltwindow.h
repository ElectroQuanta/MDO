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
    /**< Page 1 */
    void on_pb_cancel_clicked();
    void on_pb_img_filt_clicked();
    void on_pb_img_filt_2_clicked();
    void on_pb_img_filt_3_clicked();
    void on_pb_p1_next_clicked();

    /**< Page 2 */
    void on_pb_p2_back_clicked();
    void on_pb_img_filt_4_clicked();
    void on_pb_img_filt_5_clicked();
    void on_pb_img_filt_6_clicked();
    void on_pb_img_filt_ok_clicked();

    /**< dummy */
    //void on_pushButton_clicked();

signals:
    void inter_mode_pressed();
    void imgFiltSelected(int);
    void imgFiltGlobal(bool enable);

private:
    Ui::ImgFiltWindow *ui;
};

#endif // IMGFILTWINDOW_H
