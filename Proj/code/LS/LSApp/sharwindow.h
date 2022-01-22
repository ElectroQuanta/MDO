#ifndef SHARWINDOW_H
#define SHARWINDOW_H

#include <QWidget>

namespace Ui {
class SharWindow;
}

class SharWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SharWindow(QWidget *parent = nullptr);
    ~SharWindow();

signals:
    void twitterShare(const QString &);

private slots:
    void on_pb_cancel_share_clicked();

    void on_pb_twitter_share_clicked();

    void on_pb_edit_cancel_clicked();

    void on_pb_edit_ok_clicked();

    void on_pb_status_cancel_clicked();

    void on_pb_status_ok_clicked();

    /**< Dummy */
    //void on_pushButton_clicked();

signals:
    void inter_mode_pressed();

    /**< Dummy */
    //void home_pressed();

private:
    Ui::SharWindow *ui;
};

#endif // SHARWINDOW_H
