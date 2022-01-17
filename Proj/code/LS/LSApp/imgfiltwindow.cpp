#include "imgfiltwindow.h"
#include "ui_imgfiltwindow.h"

/**
 * @brief Enum describing UI pages for this Window
 */
enum UIPages {
  MAIN = 0,
  PAGE2 /**< more img filters */
};

/**< Filters file names */
#define FILT1 "mustache.png"
#define FILT2 "glass.png"

ImgFiltWindow::ImgFiltWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgFiltWindow)
{
    ui->setupUi(this);

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

ImgFiltWindow::~ImgFiltWindow()
{
    delete ui;
}

void ImgFiltWindow::on_pb_cancel_share_clicked()
{
    /**< Go to INTERACTION mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit inter_mode_pressed();
}


void ImgFiltWindow::on_pb_img_filt_clicked()
{
    emit imgFiltSelected(0);
}


void ImgFiltWindow::on_pb_img_filt_2_clicked()
{
    emit imgFiltSelected(1);
}


void ImgFiltWindow::on_pb_img_filt_3_clicked()
{
    emit imgFiltSelected(2);
}


void ImgFiltWindow::on_pb_img_filt_4_clicked()
{
    emit imgFiltSelected(3);
}


void ImgFiltWindow::on_pb_img_filt_5_clicked()
{
    // DUMMY: for navigation only
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE2);
}


void ImgFiltWindow::on_pb_cancel_share_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}


void ImgFiltWindow::on_pb_img_filt_6_clicked()
{
}


void ImgFiltWindow::on_pb_img_filt_7_clicked()
{

}


void ImgFiltWindow::on_pb_img_filt_8_clicked()
{

}


void ImgFiltWindow::on_pb_img_filt_9_clicked()
{

}

void ImgFiltWindow::on_pb_img_filt_10_clicked()
{

}

/**< Dummy */
//void ImgFiltWindow::on_pushButton_clicked()
//{
//
//}

