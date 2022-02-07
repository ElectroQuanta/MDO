#include "sharwindow.h"
#include "ui_sharwindow.h"
#include <qnamespace.h>

#define TWITTER_SHARE_FOCUS 1

#if TWITTER_SHARE_FOCUS == 1
#include <QMouseEvent>
//#include <iostream>
#endif

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

    ui->lineEdit_msg->setText("");
    //ui->lineEdit_msg->setFocusPolicy(Qt::ClickFocus);
    ui->lineEdit_msg->setFocus();

#if TWITTER_SHARE_FOCUS == 1

    #define P_X 200
    #define P_Y 850
    
    /**< Emulate mouse press */
    QPoint screenPos = QPoint(P_X, P_Y);
    QWidget *targetWidget = QApplication::widgetAt(screenPos);


    //while(1){
    //    QPoint cursorP = QCursor::pos();
    //    std::cout << "Cursor: (x,y) = "
    //              << cursorP.x() << "," << cursorP.y() << std::endl;
        //}

    if(targetWidget == nullptr){
        //std::cout << "targetWidget not found" << std::endl;
        return;
    }

    QPoint localPos = targetWidget->mapFromGlobal(screenPos);

    QMouseEvent *eventPress =
        new QMouseEvent(QEvent::MouseButtonPress, localPos, screenPos,
                        Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::postEvent(targetWidget, eventPress);

    QMouseEvent *eventRelease =
        new QMouseEvent(QEvent::MouseButtonRelease, localPos, screenPos,
                        Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::postEvent(targetWidget, eventRelease);
#endif

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

