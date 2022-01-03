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

}


void SharWindow::on_pb_twitter_share_clicked()
{

}


void SharWindow::on_pb_edit_cancel_clicked()
{

}


void SharWindow::on_pb_edit_ok_clicked()
{

}


void SharWindow::on_pb_status_cancel_clicked()
{

}


void SharWindow::on_pb_status_ok_clicked()
{

}


void SharWindow::on_pushButton_clicked()
{

}

