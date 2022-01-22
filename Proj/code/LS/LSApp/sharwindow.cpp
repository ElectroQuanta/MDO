#include "sharwindow.h"
#include "ui_sharwindow.h"

/**
 * @brief Enum describing UI pages for this Window
 */
enum UIPages{
    MAIN = 0,
    EDIT,
    STATUS
};

SharWindow::SharWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SharWindow)
{
    ui->setupUi(this);

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

SharWindow::~SharWindow()
{
    delete ui;
}

void SharWindow::on_pb_cancel_share_clicked()
{
    /**< Go to INTERACTION mode */
    emit inter_mode_pressed();
}


void SharWindow::on_pb_twitter_share_clicked()
{
    /**< Go to EDIT */
    ui->stackedWidget->setCurrentIndex(UIPages::EDIT);

}


void SharWindow::on_pb_edit_cancel_clicked()
{
    /**< Go to MAIN */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}


void SharWindow::on_pb_edit_ok_clicked()
{
    /**< Change to status */

    ui->stackedWidget->setCurrentIndex(UIPages::STATUS);
    // Share post
    if( !ui ->lineEdit_msg->text().isEmpty() )
        emit twitterShare( ui->lineEdit_msg->text() );
}


void SharWindow::on_pb_status_cancel_clicked()
{
    /**< Go to MAIN */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}


void SharWindow::on_pb_status_ok_clicked()
{
    /**< Go to INTERACTION mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit inter_mode_pressed();

}

/**< Dummy */
//void SharWindow::on_pushButton_clicked()
//{
//    /**< Go to INTERACTION mode */
//    // Reset view to main before emiting signal
//    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
//    emit home_pressed();
//}

