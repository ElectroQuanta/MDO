#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>

/**
 * @brief The PageViews enum helps to handle the stackWidget in a more pratical way.
 */
enum PageViews{
    MAIN = 0, /**< Sign in screen: displayed when opening the app. */
    STATISTICS, /**< To register a user. */
    USERS, /**< The admin view: displayed when a user is an admin */
    ADS_TO_ACT, /**< Ads to activate view*/
    TEST_OP,  /**< Test Operation View*/
};

enum UserType {
    ADMIN = 0,
    BRAND,
};

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QString text;
    for(int i = 0; i < 2; i++) {
        text = "Station " + QString::number(i+1) + ": Universidade do Minho";
        ui->stationsComboBox->addItem(text);
    }
    bool checked = false;
    QString ad = "Ad 1", mode = "Normal";
    ui->poweredCheckBox->setChecked(checked);
    ui->currAdLabel_2->setText(ad);
    ui->currModeLabel_2->setText(mode + " Mode");
    ui->stackedWidget->setCurrentIndex(MAIN);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_activatedCheckBox_stateChanged(int arg1)
{
    if(!this->ui->activatedCheckBox->checkState()) {
        this->ui->activatedCheckBox->setText("Off");
    }
    else {
        this->ui->activatedCheckBox->setText("On");
    }
}

void AdminWindow::on_goBackBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(MAIN);
}

void AdminWindow::on_statisticsBtn_2_pressed()
{
    int index = ui->stationsComboBox->currentIndex();
    QString text;
    for(int i = ui->brandComboBox->count(); i >= 0; i--)
        ui->brandComboBox->removeItem(i);
    switch(index){
    case 0:
        for(int i = 0; i < 2; i++) {
            text = "Brand " + QString::number(i+1);
            ui->brandComboBox->addItem(text);
        }
        break;
    case 1:
        for(int i = 0; i < 2; i++) {
            text = "Brand " + QString::number(i+3);
            ui->brandComboBox->addItem(text);
        }
        break;
    }
    ui->stationName->setText(ui->stationsComboBox->currentText());
    ui->stackedWidget->setCurrentIndex(STATISTICS);
}

void AdminWindow::on_stationsComboBox_activated(int index)
{
    bool checked = false;
    QString ad = "Ad 1", mode = "Normal";
    switch (index) {
    case 0:
        ad = "Ad 1";
        mode = "Normal";
        checked = false;
        break;
    case 1:
        ad = "Ad 2";
        mode = "Sharing";
        checked = true;
    default:
        break;
    }
    ui->poweredCheckBox->setChecked(checked);
    ui->currAdLabel_2->setText(ad);
    ui->currModeLabel_2->setText(mode + " Mode");
}

void AdminWindow::on_logoutBtn_pressed()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Logout",
                                                                tr("Are you sure you want to logout?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if(resBtn == QMessageBox::Yes) {
        emit home_pressed();
    }
}

void AdminWindow::on_poweredCheckBox_stateChanged(int arg1)
{
    if(!this->ui->poweredCheckBox->checkState()) {
        this->ui->poweredCheckBox->setText("Off");
    }
    else {
        this->ui->poweredCheckBox->setText("On");
    }
}

void AdminWindow::on_brandComboBox_activated(int index)
{
    int slot, perc, nrTimes, nrPics, nrShared, days;
    bool checked;
    switch (index) {
    case 0:
        nrTimes = 20;
        slot = 1;
        perc = 20;
        nrPics = 5;
        nrShared = 2;
        days = 2;
        checked = true;
        break;
    case 1:
        nrTimes = 30;
        slot = 2;
        perc = 50;
        nrPics = 6;
        nrShared = 0;
        days = 1;
        checked = false;
        break;
    default:
        break;
    }
    ui->NrTimesShowLabel_2->setText(QString::number(nrTimes));
    ui->fragranceSlotQuantLabel_2->setText(QString::number(slot) + " | " + QString::number(perc) + "%");
    ui->NrPicsGIFSLabel_2->setText(QString::number(nrPics));
    ui->NrSharedLabel_2->setText(QString::number(nrShared));
    ui->DaysRemainingLabel_2->setText(QString::number(days));
    ui->activatedCheckBox->setChecked(checked);
}

void AdminWindow::on_usersBtn_2_pressed()
{
    for(int i = ui->usersComboBox->count(); i >= 0; i--) {
        ui->usersComboBox->removeItem(i);
    }
    for(int i = ui->userTypeComboBox->count(); i >= 0; i--) {
        ui->userTypeComboBox->removeItem(i);
    }
    for (int i = 0; i < 3; i++) {
        ui->usersComboBox->addItem("brand" + QString::number(i));
    }
    ui->userTypeComboBox->addItem("ADMIN");
    ui->userTypeComboBox->addItem("BRAND");
    ui->userTypeComboBox->setCurrentIndex(BRAND);
    ui->emailLabel_2->setText("hugofreitas12@gmail.com");
    ui->stackedWidget->setCurrentIndex(USERS);
}

void AdminWindow::on_goBackBtn_2_pressed()
{
    on_goBackBtn_pressed();
}

void AdminWindow::on_usersComboBox_activated(int index)
{
    UserType type;
    QString email;
    switch (index) {
    case 0:
        type = BRAND;
        email = "hugofreitas12@gmail.com";
        break;
    case 1:
        type = ADMIN;
        email = "1111111";
        break;
    case 2:
        type = BRAND;
        email = "2222222222";
        break;
    default:
        break;
    }
    ui->userTypeComboBox->setCurrentIndex(type);
    ui->emailLabel_2->setText(email);
}

void AdminWindow::on_saveChangesBtn_pressed()
{
    QString text = "user: " + ui->usersComboBox->currentText() +
            "\ntype of user: " + ui->userTypeComboBox->currentText() +
            "\nemail: " + ui->emailLabel_2->text();
    QMessageBox::information(this, "SUCCESS!", text, QMessageBox::Ok);
}

void AdminWindow::on_discardChangesBtn_pressed()
{
    QMessageBox::information(this, "SUCCESS!", "Discard Changes", QMessageBox::Ok);
}

void AdminWindow::on_goBackBtn_3_pressed()
{
    on_goBackBtn_pressed();
}

void AdminWindow::on_adsToActivateBtn_2_pressed()
{
    int stationNr = ui->stationsComboBox->currentIndex() + 1;
    ui->adsToActivateLabel->setText("Ads To Activate: Station " + QString::number(stationNr));
    for(int i = ui->adsToActComboBox->count(); i >= 0; i--)
        ui->adsToActComboBox->removeItem(i);
    for (int i = 0; i < 3; i++) {
        ui->adsToActComboBox->addItem("brand" + QString::number(i));
    }
    int slot = 1, perc = 100;
    QString videoFile = "somevideos1.zip", filter = "filter1", state = "READY";
    ui->stateLabel_2->setText(state);
    ui->fragSlotLabel_2->setText(QString::number(slot) +" | " + QString::number(perc) + "%");
    ui->transferVideosBtn->setText(videoFile);
    ui->filterLabel_2->setText(filter);
    ui->stackedWidget->setCurrentIndex(ADS_TO_ACT);
}

void AdminWindow::on_testOperationBtn_2_pressed()
{
    ui->stackedWidget->setCurrentIndex(TEST_OP);
}

void AdminWindow::on_goBackBtn_4_pressed()
{
    on_goBackBtn_pressed();
}

void AdminWindow::on_transferVideosBtn_pressed()
{
    QMessageBox::information(this, "SUCCESS!", "Download zip file", QMessageBox::Ok);
}

void AdminWindow::on_acceptAdBtn_pressed()
{
    QMessageBox::information(this, "SUCCESS!", "Ad accepted", QMessageBox::Ok);
}

void AdminWindow::on_denyAdBtn_pressed()
{
    QMessageBox::information(this, "SUCCESS!", "Ad denied!", QMessageBox::Ok);
}

void AdminWindow::on_adsToActComboBox_activated(int index)
{
    QString state, videoFile, filter;
    int slot, perc;
    switch (index) {
    case 0:
        state = "READY";
        videoFile = "somevideo1.zip";
        filter = "filter1.zip";
        slot = 1;
        perc = 100;
        break;
    case 1:
        state = "READY";
        videoFile = "somevideo2.zip";
        filter = "filter2.zip";
        slot = 2;
        perc = 80;
        break;
    case 2:
        state = "READY";
        videoFile = "somevideo3.zip";
        filter = "filter3.zip";
        slot = 3;
        perc = 50;
        break;
    default:
        break;
    }
    ui->stateLabel_2->setText(state);
    ui->fragSlotLabel_2->setText(QString::number(slot) +" | " + QString::number(perc) + "%");
    ui->transferVideosBtn->setText(videoFile);
    ui->filterLabel_2->setText(filter);
}
