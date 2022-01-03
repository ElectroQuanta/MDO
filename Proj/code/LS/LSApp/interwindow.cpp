#include "interwindow.h"
#include "ui_interwindow.h"

/**
 * @brief Enum describing UI pages for this Window
 */
enum UIPages{
    MAIN = 0,
    PIC,
    GIF
};

InterWindow::InterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterWindow)
{
    ui->setupUi(this);

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

InterWindow::~InterWindow() { delete ui; }

void InterWindow::on_pb_img_filt_clicked() {
    /**< Go to IMGFILT mode */
}

void InterWindow::on_pb_take_pic_clicked()
{
  ui->stackedWidget->setCurrentIndex(UIPages::PIC);
}

void InterWindow::on_pb_create_gif_clicked()
{
  ui->stackedWidget->setCurrentIndex(UIPages::GIF);
}


void InterWindow::on_pb_pic_cancel_clicked()
{
  ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

void InterWindow::on_pb_pic_share_clicked()
{
    /**< Go to SHARING mode */
}

void InterWindow::on_pb_gif_cancel_clicked()
{
  ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

void InterWindow::on_pb_gif_share_clicked()
{
    /**< Go to SHARING mode */
}

