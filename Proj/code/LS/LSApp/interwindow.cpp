#include "interwindow.h"
#include "ui_interwindow.h"

/**
 * @brief Enum describing UI pages for this Window
 */
enum UIPages { MAIN = 0, PIC, GIF };

InterWindow::InterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterWindow)
{
    ui->setupUi(this);

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);

    /**< Connect signals to slots */
    //connect(this, SIGNAL(interWindUpdateStatus(const QString str)),
    //        this, SLOT(oninterWindUpdateStatus(const QString str)) );
    
}

InterWindow::~InterWindow() { delete ui; }

//void InterWindow::oninterWindUpdateStatus(const QString str){
//    ui->label_status->setText(str);
//}

void InterWindow::on_pb_img_filt_clicked() {

    /**< Go to IMGFILT mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit imgfilt_mode_pressed();
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
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit shar_mode_pressed();
}

void InterWindow::on_pb_gif_cancel_clicked()
{
  ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

void InterWindow::on_pb_gif_share_clicked()
{
    /**< Go to SHARING mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit shar_mode_pressed();
}

void InterWindow::on_pushButton_clicked()
{
    /**< Go to MAIN mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit home_pressed();
}


