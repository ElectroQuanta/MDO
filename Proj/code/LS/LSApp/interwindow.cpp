#include "interwindow.h"
#include "ui_interwindow.h"
#include <type_traits>

/**
 * @brief Enum describing UI pages for this Window
 */
enum UIPages { MAIN = 0, PIC, GIF };

#define PIC_TIMEOUT 3
#define GIF_TIMEOUT 5

InterWindow::InterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterWindow)
{
    ui->setupUi(this);

    /**< stackedWidget: manages the UI views - set default view */
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);

    /**< Initialize Picture timer */
    _pic_timer = new QTimer(this);
    _pic_time_remaining = PIC_TIMEOUT;

    /**< Initialize GIF timer */
    _gif_timer = new QTimer(this);
    _gif_time_remaining = GIF_TIMEOUT;

    /**< Connect signals to slots */
    //connect(this, SIGNAL(interWindUpdateStatus(const QString str)),
    //        this, SLOT(oninterWindUpdateStatus(const QString str)) );
    connect(_pic_timer, SIGNAL(timeout()), this, SLOT(onPicTimerElapsed()) );
    connect(_gif_timer, SIGNAL(timeout()), this, SLOT(onGifTimerElapsed()) );
}

void InterWindow::onPicTimerElapsed(){
    /* Decrement counter */
    _pic_time_remaining--;

    QString str;

    /* Check counter reset */
    if( !_pic_time_remaining ){
        /**< Stop timer */
        _pic_timer->stop();

        /**< Clear label */
        ui->timer_setup->setText("");
        
        /**< Re-enable pushbuttons */
        enablePushbuttons(true);

        /**< Signal event */
        takePic_complete();

        /* Exit */
        return;
    }
    ui->timer_setup->setText( str.setNum(_pic_time_remaining) );
}

void InterWindow::onGifTimerElapsed(){
    /* Decrement counter */
    _gif_time_remaining--;

    /**< Update Progress Bar */
    ui->progressBar->setValue(
        (float)(GIF_TIMEOUT - _gif_time_remaining)
        / GIF_TIMEOUT * 100);

    /* Check counter reset */
    if( !_gif_time_remaining ){
        /**< Stop timer */
        _gif_timer->stop();
        
        /**< Re-enable pushbuttons */
        enablePushbuttons(true);

        /**< Signal event */
        gif_enabled(false);
    }
}

void InterWindow::resetUI(){

    /**< Clear pixmap */
    ui->timer_setup->setPixmap(QPixmap());

    /**< Clear bars */
    ui->timer_setup->setText("");
    ui->progressBar->setValue(0);

    /**< Enable pusbbuttons */
    ui->pb_pic_cancel->setEnabled(true);
    ui->pb_pic_share->setEnabled(true);
    ui->pb_gif_cancel->setEnabled(true);
    ui->pb_gif_share->setEnabled(true);
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
  #define TIMEOUT_MS 1000

  ui->stackedWidget->setCurrentIndex(UIPages::PIC);

  /**< Disable other pushbuttons */
  enablePushbuttons(false);

  /**< Setup timer */
  _pic_time_remaining = PIC_TIMEOUT;

  /**< Update label */
  QString timeRemainingStr;
  timeRemainingStr.setNum(_pic_time_remaining);
  ui->timer_setup->setText(timeRemainingStr);

  /**< Start timer */
  _pic_timer->start(TIMEOUT_MS);
}

void InterWindow::enablePushbuttons(bool enable) {
  switch ( ui->stackedWidget->currentIndex() ) {
  case UIPages::PIC:
    ui->pb_pic_cancel->setEnabled(enable);
    ui->pb_pic_share->setEnabled(enable);
    break;
  case UIPages::GIF:
    ui->pb_gif_cancel->setEnabled(enable);
    ui->pb_gif_share->setEnabled(enable);
    break;
  default:
    break;
  }
}

void InterWindow::on_pb_create_gif_clicked()
{
  #define TIMEOUT_MS 1000

  ui->stackedWidget->setCurrentIndex(UIPages::GIF);

  /**< Disable other pushbuttons */
  enablePushbuttons(false);

  /**< Setup timer */
  _gif_time_remaining = GIF_TIMEOUT;

  /**< Update progress bar */
  ui->progressBar->setValue(0);

  /**< Start timer */
  _gif_timer->start(TIMEOUT_MS);

  /**< Signal event GIF acquisition started  */
  emit gif_enabled(true);
}

void InterWindow::on_pb_pic_cancel_clicked()
{
    /**< Reset UI */
    resetUI();

  /**< Change view */
  ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

void InterWindow::on_pb_pic_share_clicked()
{
    /**< Reset UI */
    resetUI();

    /**< Go to SHARING mode */
    // Reset view to main before emiting signal
    ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
    emit shar_mode_pressed();
}

void InterWindow::on_pb_gif_cancel_clicked()
{
    /**< Reset UI */
    resetUI();

  ui->stackedWidget->setCurrentIndex(UIPages::MAIN);
}

void InterWindow::on_pb_gif_share_clicked()
{
    /**< Reset UI */
    resetUI();

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

void InterWindow::updatePicLabel(QString fname){

    ui->timer_setup->setAlignment(Qt::AlignCenter);

    QPixmap pixmap;

    /** If Pic successfully loaded */
    if( pixmap.load(fname) ){

        /** scale pixmap to fit in label'size and keep ratio of pixmap */
    pixmap = pixmap.scaled(ui->timer_setup->size(),Qt::KeepAspectRatio);
    ui->timer_setup->setPixmap(pixmap);
    }
}
