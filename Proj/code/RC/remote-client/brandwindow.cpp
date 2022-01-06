#include "brandwindow.h"
#include "ui_brandwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

/**
 * @brief The PageViews enum helps to handle the stackWidget in a more pratical way.
 */
enum PageViews{
    MAIN = 0, /**< Welcome view. */
    RENTED, /**< To display statistics of rented ads. */
    TO_RENT, /**< The rent view: displayed when a user wants to rent ads*/
    NOTIFICATIONS, /**< View to see notifications*/
};

QString months[12] {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "NOvember",
    "December"
};

BrandWindow::BrandWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrandWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(MAIN);
}

BrandWindow::~BrandWindow()
{
    delete ui;
}

void BrandWindow::on_logoutBtn_pressed()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Logout",
                                                                tr("Are you sure you want to logout?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if(resBtn == QMessageBox::Yes) {
        emit home_pressed();
    }
}

void BrandWindow::on_goBackBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(MAIN);
}

void BrandWindow::on_rentedBtn_pressed()
{
    QString text;
    int slot, perc, nrTimes, nrPics, nrShared, days;
    QString status;
    for(int i = ui->stationsComboBox->count(); i >= 0; i--)
        ui->stationsComboBox->removeItem(i);
     for(int i = 0; i < 2; i++) {
            text = "Station " + QString::number(i+1);
            ui->stationsComboBox->addItem(text);
    }
     nrTimes = 20;
     slot = 1;
     perc = 20;
     nrPics = 5;
     nrShared = 2;
     days = 2;
     status = "activated";
     ui->NrTimesShowLabel_2->setText(QString::number(nrTimes));
     ui->fragranceSlotQuantLabel_2->setText(QString::number(slot) + " | " + QString::number(perc) + "%");
     ui->NrPicsGIFSLabel_2->setText(QString::number(nrPics));
     ui->NrSharedLabel_2->setText(QString::number(nrShared));
     ui->DaysRemainingLabel_2->setText(QString::number(days));
    ui->stackedWidget->setCurrentIndex(RENTED);
}

void BrandWindow::on_stationsComboBox_activated(int index)
{
    int slot, perc, nrTimes, nrPics, nrShared, days;
    QString status;
    switch (index) {
    case 0:
        nrTimes = 20;
        slot = 1;
        perc = 20;
        nrPics = 5;
        nrShared = 2;
        days = 2;
        status = "activated";
        break;
    case 1:
        nrTimes = 30;
        slot = 2;
        perc = 50;
        nrPics = 6;
        nrShared = 0;
        days = 1;
        status = "Not active";
        break;
    default:
        break;
    }
    ui->NrTimesShowLabel_2->setText(QString::number(nrTimes));
    ui->fragranceSlotQuantLabel_2->setText(QString::number(slot) + " | " + QString::number(perc) + "%");
    ui->NrPicsGIFSLabel_2->setText(QString::number(nrPics));
    ui->NrSharedLabel_2->setText(QString::number(nrShared));
    ui->DaysRemainingLabel_2->setText(QString::number(days));

}

void BrandWindow::on_goBackBtn_2_pressed()
{
    on_goBackBtn_pressed();
}

void BrandWindow::on_toRentBtn_pressed()
{
    for(int i = ui->stationsComboBox_2->count(); i >= 0; i--)
        ui->stationsComboBox_2->removeItem(i);
    for(int i = 0; i < 2; i++) {
        ui->stationsComboBox_2->addItem("Station " + QString::number(i+1));
    }
    for(int i = 0; i < 24; i++) {
        ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i+1) + ":00");
    }
    ui->fragranceComboBox->addItem("Coffee");
    ui->fragranceComboBox->addItem("Perfume");
    ui->filterComboBox->addItem("Glasses");
    ui->filterComboBox->addItem("Moustache");
    ui->filterComboBox->addItem("Hat");
    ui->stackedWidget->setCurrentIndex(TO_RENT);
}

void BrandWindow::on_stationsComboBox_2_activated(int index)
{
    for(int i = ui->targetHoursComboBox->count(); i >= 0; i--)
        ui->targetHoursComboBox->removeItem(i);
    switch(index){
    case 0:
        for(int i = 0; i < 24; i++) {
            ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i+1) + ":00");
        }
        break;
    case 1:
        for(int i = 0; i < 10; i++) {
            ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i+1) + ":00");
        }
        break;
    default:
        break;
    }

}

void BrandWindow::on_calendarWidget_clicked(const QDate &date)
{
    for(int i = ui->targetHoursComboBox->count(); i >= 0; i--)
        ui->targetHoursComboBox->removeItem(i);
    if(date.day() == 23) {
        for(int i = 0; i < 15; i++) {
            ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " +           QString::number(i+1) + ":00");
        }
    }
    else if (date.month() == 2) {
            for(int i = 0; i < 5; i++) {
                ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i+1) + ":00");
            }
        }
}

void BrandWindow::on_uploadBtn_pressed()
{
    QString filename = QFileDialog::getOpenFileName(this, "Upload File", "", "Zip-File (*.zip)");
    if (filename.contains(".zip")) {
        QFileInfo file(filename);
        ui->filenameLabel->setText(file.fileName());
        QMessageBox::information(this, "SUCCESS", "File uploaded!");
    }
    else if (!filename.isEmpty()){
        QMessageBox::warning(this, "ERROR!", "Enter only .zip files!");
        ui->filenameLabel->setText("");
    }
}

void BrandWindow::on_rentBtn_pressed()
{
    QString text = "Rent Description:\n"
                   "Station: " + ui->stationsComboBox_2->currentText() +
            "\nDate: " + ui->calendarWidget->selectedDate().toString() +
            "\nTarget Hours: " + ui->targetHoursComboBox->currentText() +
            "\nFragrance: " + ui->fragranceComboBox->currentText() +
            "\nFilter: " + ui->filterComboBox->currentText() +
            "\nFile: " + ui->filenameLabel->text();
    if(ui->filenameLabel->text().isEmpty()) {
        QMessageBox::warning(this, "ERROR!", "Upload a .zip file!", QMessageBox::Ok);
    }
    else {
        auto resbtn = QMessageBox::question(this, "WARNING", "Are you sure of the rent?\n" + text, QMessageBox::Yes | QMessageBox::No);
        if(resbtn == QMessageBox::Yes) {
            QMessageBox::information(this, "SUCCESS", "Ad rented!", QMessageBox::Ok);
        }
    }


}
