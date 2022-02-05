#include "brandwindow.h"
#include "ui_brandwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include "db-namespaces.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

/**
 * @brief The PageViews enum helps to handle the stackWidget in a more pratical way.
 */
enum PageViews{
    MAIN = 0, /**< Welcome view. */
    RENTED, /**< To display statistics of rented ads. */
    TO_RENT, /**< The rent view: displayed when a user wants to rent ads*/
    NOTIFICATIONS, /**< View to see notifications*/
};

/**
 * @brief BrandWindow::BrandWindow
 * @param sess
 * @param parent
 *
 * Constructor to the Brand window, initializes the SQL Session and
 * the stacked widget
 */
BrandWindow::BrandWindow( Session* sess, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrandWindow)
{
    ui->setupUi(this);
    this->sess = sess;
    ui->stackedWidget->setCurrentIndex(MAIN);
}

/**
 * @brief BrandWindow::~BrandWindow
 *
 * BrandWindow Destructor
 */
BrandWindow::~BrandWindow()
{
    delete ui;
}

/**
 * @brief BrandWindow::on_logoutBtn_pressed
 *
 * Confirm if the user wants to Logout, if so emits the signal to go to Sign In
 */
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

/**
 * @brief BrandWindow::on_goBackBtn_pressed
 *
 * Goes back to the main page
 */
void BrandWindow::on_goBackBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(MAIN);
}

/**
 * @brief BrandWindow::on_rentedBtn_pressed
 *
 * Shows the statistics of the rented ads in all the stations
 */
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

/**
 * @brief BrandWindow::on_stationsComboBox_activated
 * @param index
 *
 * Changes the statistics that differ from station to station
 */
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

/**
 * @brief BrandWindow::on_goBackBtn_2_pressed
 *
 * Another Go Back button
 */
void BrandWindow::on_goBackBtn_2_pressed()
{
    on_goBackBtn_pressed();
}

/**
 * @brief BrandWindow::on_toRentBtn_pressed
 *
 * Menu used to rent ads, showing a calendar widget and all the options to
 * rent an Ad.
 */
void BrandWindow::on_toRentBtn_pressed()
{
    std::stringstream ss1, ss2, ss3, ss4, ss5;
    /**< Remove all the items that were preciously on the combo boxes*/
    for(int i = ui->stationsComboBox_2->count(); i >= 0; i--) {
        ui->stationsComboBox_2->removeItem(i);
    }
    for(int i = ui->targetHoursComboBox->count(); i >= 0; i--) {
        ui->targetHoursComboBox->removeItem(i);
    }
    for(int i = ui->filterComboBox->count(); i >= 0; i--) {
        ui->filterComboBox->removeItem(i);
    }
    for(int i = ui->fragranceComboBox->count(); i >= 0; i--) {
        ui->fragranceComboBox->removeItem(i);
    }
    ui->calendarWidget->setSelectedDate(QDate::currentDate());

    /**< Query to search for all the stations to show them*/
    SqlResult stations = sess->sql(StationDB::select_all).execute();
    Row station;
    std::string station_name;
    while(station = stations.fetchOne()) {
        station_name = static_cast<std::string>(station[StationDB::NAME]);
        ui->stationsComboBox_2->addItem(QString::fromStdString(station_name));
    }
    station = sess->sql(StationDB::select_all).execute().fetchOne();
    int station_id = station[StationDB::ID];
    QDate date = ui->calendarWidget->selectedDate();
    int week_nr = date.weekNumber();
    int weekday = (date.dayOfWeek()-1);
    ss1 << station_id;
    ss2 << week_nr;
    ss4 << weekday;
    std::string station_id_str = ss1.str();
    std::string week_nr_str = ss2.str();
    std::string weekday_str = ss4.str();
    /**< Delete all time slots that were already used (all time slots from previous days) */
    sess->sql(TimeSlotDB::delete_where + "timeTable_id < " + week_nr_str + " or (timeTable_id =" + week_nr_str + " and id < " + weekday_str + ")").execute();
    Row timetable = sess->sql(TimeTableDB::select_where + "station_id =" + station_id_str + " and week = " + week_nr_str).execute().fetchOne();
    int timetable_id = timetable[TimeTableDB::ID];
    ss3 << timetable_id;
    std::string timetable_id_str = ss3.str();
    SqlResult timeslots;
    Row Timeslot;
    int slot, id;
    /**< Add time slots to target hours combobox, the ones who are rented show the label "Rented" */
    for(int i = 0; i < 24; i++) {
        timeslots = sess->sql(TimeSlotDB::select_from_timetable + timetable_id_str).execute();
        while(Timeslot = timeslots.fetchOne()) {
           slot = 24 * weekday + i;
           id = Timeslot[TimeSlotDB::ID];
            if(slot == id)
                break;
        }
        if(slot == id)
            ui->targetHoursComboBox->addItem("Rented");
        else
            ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i) + ":59");
    }
    /**< Add the fragrances available on the station */
    Row FragranceList = sess->sql(FragranceListDB::select_from_station + station_id_str).execute().fetchOne();
    int fragranceList_id = FragranceList[FragranceListDB::ID];
    ss5 << fragranceList_id;
    std::string fragranceList_id_str = ss5.str();
    SqlResult Fragrances = sess->sql(FragranceDB::select_from_fragranceList + fragranceList_id_str).execute();
     Row Fragrance;
     std::string fragrance_name;
    while(Fragrance = Fragrances.fetchOne()) {
        fragrance_name = static_cast<std::string>(Fragrance[FragranceDB::NAME]);
        ui->fragranceComboBox->addItem(QString::fromStdString(fragrance_name));
    }

    /**< Add the filters available on the station*/
    SqlResult Filters = sess->sql(FilterDb::select_all).execute();
    Row Filter;
    std::string filter_name;
    while(Filter = Filters.fetchOne()) {
        filter_name = static_cast<std::string>(Filter[FilterDb::NAME]);
        ui->filterComboBox->addItem(QString::fromStdString(filter_name));
    }
    ui->stackedWidget->setCurrentIndex(TO_RENT);
}

/**
 * @brief BrandWindow::on_stationsComboBox_2_activated
 * @param index
 *
 * When changing station
 */
void BrandWindow::on_stationsComboBox_2_activated(int index)
{
    for(int i = ui->targetHoursComboBox->count(); i >= 0; i--)
        ui->targetHoursComboBox->removeItem(i);

}

/**
 * @brief BrandWindow::on_calendarWidget_clicked
 * @param date
 *
 * Function that responses to a different date selection.
 * It changes all the fields to all the information according to that date
 */
void BrandWindow::on_calendarWidget_clicked(const QDate &date)
{
    std::stringstream ss1, ss2, ss3;

    /**< Firstly remove all the target hours*/
    for(int i = ui->targetHoursComboBox->count(); i >= 0; i--)
        ui->targetHoursComboBox->removeItem(i);

    /**< It is only possible to rent in a maximum space of a week*/
    if(date >= QDate::currentDate() && QDate::currentDate().daysTo(date) < 7) {
        /**< Query to know which station is it*/
        Row station = sess->sql(StationDB::select_where + "name = '" + ui->stationsComboBox_2->currentText().toStdString() + "'").execute().fetchOne();
        int station_id = station[StationDB::ID];
        int week_nr = date.weekNumber();
        int weekday = date.dayOfWeek()-1;
        ss1 << station_id;
        ss2 << week_nr;
        std::string station_id_str = ss1.str();
        std::string week_nr_str = ss2.str();
        /**< Query to select the time Table and the time slots from that time table*/
        Row timetable = sess->sql(TimeTableDB::select_where + "station_id =" + station_id_str + " and week = " + week_nr_str).execute().fetchOne();
        int timetable_id = timetable[TimeTableDB::ID];
        ss3 << timetable_id;
        std::string timetable_id_str = ss3.str();
        SqlResult timeslots;
        Row Timeslot;
        int slot, id;

        /**< Get all the time slots rented and available to rent*/
        for(int i = 0; i < 24; i++) {
            timeslots = sess->sql(TimeSlotDB::select_from_timetable + timetable_id_str).execute();
            while(Timeslot = timeslots.fetchOne()) {
                slot = 24 * weekday + i;
                id = Timeslot[TimeSlotDB::ID];
                if(slot == id)
                    break;
            }
            /**< If exists, they are rented*/
            if(slot == id)
                ui->targetHoursComboBox->addItem("Rented");
            else
                ui->targetHoursComboBox->addItem(QString::number(i) + ":00 to " + QString::number(i) + ":59");
        }
    }
    else
        ui->targetHoursComboBox->addItem("Unavailable");
}

/**
 * @brief BrandWindow::on_uploadBtn_pressed
 *
 * Opens a file dialog to select a mp4 file
 */
void BrandWindow::on_uploadBtn_pressed()
{
    QString filename = QFileDialog::getOpenFileName(this, "Upload File", "", "MP4 (*.mp4)");
    if (filename.contains(".mp4")) {
        QFileInfo file_(filename);
        ui->filenameLabel->setText(file_.fileName());
        QMessageBox::information(this, "SUCCESS", "File uploaded!");
        file = file_;
    }
    else if (!filename.isEmpty()){
        QMessageBox::warning(this, "ERROR!", "Enter only .mp4 files!");
        ui->filenameLabel->setText("");
    }
}

/**
 * @brief BrandWindow::on_rentBtn_pressed
 *
 * When clicking on Rent, verifies if everything is in order and ads all the
 * data necessary to the database
 */
void BrandWindow::on_rentBtn_pressed()
{
    QString text = "Rent Description:\n"
                   "Station: " + ui->stationsComboBox_2->currentText() +
            "\nDate: " + ui->calendarWidget->selectedDate().toString() +
            "\nTarget Hours: " + ui->targetHoursComboBox->currentText() +
            "\nFragrance: " + ui->fragranceComboBox->currentText() +
            "\nFilter: " + ui->filterComboBox->currentText() +
            "\nFile: " + ui->filenameLabel->text();
    std::string station_name = ui->stationsComboBox_2->currentText().toStdString();
    /**< Needs to upload a mp4 file*/
    if(ui->filenameLabel->text().isEmpty()) {
        QMessageBox::warning(this, "ERROR!", "Upload a .mp4 file!", QMessageBox::Ok);
    }
    /**< It can not be already rented*/
    else if (ui->targetHoursComboBox->currentText() == "Rented") {
        QMessageBox::warning(this, "ERROR!", "Slot already rented!", QMessageBox::Ok);
    }

    else {
        /**< Confirm the Ad rent */
        auto resbtn = QMessageBox::question(this, "WARNING", "Are you sure of the rent?\n" + text, QMessageBox::Yes | QMessageBox::No);
        if(resbtn == QMessageBox::Yes) {
            std::stringstream ss1, ss2, ss3, ss4;
            /**< Get Fragrance ID (Through station id and fragrance list id) */
            Row Station = sess->sql(StationDB::select_where + "name = '" + station_name + "'").execute().fetchOne();
            int station_id = Station[StationDB::ID];
            ss1 << station_id;
            std::string station_id_str = ss1.str();
            Row FragList = sess->sql(FragranceListDB::select_from_station + station_id_str).execute().fetchOne();
            int fragList_id = FragList[FragranceDB::ID];
            ss2 << fragList_id;
            std::string fragList_id_str = ss2.str();
            Row Fragrance = sess->sql(FragranceDB::select_from_fragranceList + fragList_id_str).execute().fetchOne();
            int frag_id = Fragrance[FragranceDB::ID];
            ss3 << frag_id;
            std::string fragrance_id_str = ss3.str();

            /**< Get user id */
            ss4 << user_id;
            std::string user_id_str = ss4.str();

            /**< Insert new timeSlot and get its id */
            std::stringstream ss5, ss6, ss7;
            int week = ui->calendarWidget->selectedDate().weekNumber();
            ss5 << week;
            std::string week_str = ss5.str();
            Row TimeTable = sess->sql(TimeTableDB::select_from_station + station_id_str + " and week = " + week_str).execute().fetchOne();
            int timeTable_id = TimeTable[TimeTableDB::ID];
            ss6 << timeTable_id;
            std::string timeTable_id_str = ss6.str();
            int time_slot_id = ui->targetHoursComboBox->currentIndex();
            int day_week = ui->calendarWidget->selectedDate().dayOfWeek() - 1 ;
            time_slot_id = 24*day_week + ui->targetHoursComboBox->currentIndex();
            ss7 << time_slot_id;
            std::string timeSlot_id_str = ss7.str();
            try {
                sess->sql(TimeSlotDB::insert + timeSlot_id_str + ", " + timeTable_id_str + ", 60, 20)").execute();
            }
            catch(const mysqlx::Error &err) {
                QMessageBox::information(this, "ERROR!!", "Something went wrong!", QMessageBox::Ok);
                return;
            }

            /**< Get filter id */
            std::stringstream ss8;
            Row Filter = sess->sql(FilterDb::select_where + "name = '" + ui->filterComboBox->currentText().toStdString() + "'").execute().fetchOne();
            int filter_id = Filter[FilterDb::ID];
            ss8 << filter_id;
            std::string filter_id_str = ss8.str();

            /**< Adding the Ad */
            try{
                sess->sql(AdDB::insert + fragrance_id_str + ", " + user_id_str + ", " + timeSlot_id_str + ", " + station_id_str + ", " + filter_id_str + ", false)").execute();
            }
            /**< Delete everything that was added if the query doesn't work*/
            catch (const mysqlx::Error &err){
                sess->sql("Delete from TimeSlot where id = " + timeSlot_id_str).execute();
                QMessageBox::information(this, "ERROR!!", "Something went wrong!", QMessageBox::Ok);
                return;
            }
            /**< Adding the file */
            std::stringstream ss9, ss10;
            qint64 file_size = file.size();
            ss9 << file_size;
            std::string file_size_str = ss9.str(),
            file_name = file.fileName().toStdString();
            Row Ad = sess->sql("SELECT * FROM Ad WHERE id = (SELECT max(id) from Ad)").execute().fetchOne();
            int ad_id = Ad[AdDB::ID];
            ss10 << ad_id;
            std::string ad_id_str = ss10.str();
            std::string file_type = file.completeSuffix().toStdString();
            try {
                sess->sql(MediaFileDb::insert + ad_id_str + ", '" + file_name + "', " + file_size_str + ", '" + file_type + "')").execute();
            }
            /**< Delete everything that was added if the query doesn't work*/
            catch(const mysqlx::Error &err) {
                sess->sql("Delete from TimeSlot where id = " + timeSlot_id_str).execute();
                sess->sql("Delete from Ad where id = (SELECT id FROM Ad ORDER BY id DESC LIMIT 1)").execute();
                QMessageBox::information(this, "ERROR!!", "Something went wrong!", QMessageBox::Ok);
                return;
            }
            Row User = sess->sql(UserDB::select_where + "id =" + user_id_str).execute().fetchOne();
            std::string user_name = static_cast<std::string>(User[UserDB::NAME]);
            QString curr_path = file.absoluteFilePath();
            QString new_path = QCoreApplication::applicationDirPath() + "/../res/";
            if (!QDir(new_path).exists()) {
                QDir().mkdir(new_path);
            }
            /**< Send the file to a specific location */
            if(QFile::copy(curr_path, new_path + file.fileName()));
            //char* path;
            //strcpy(path, curr_path.toStdString().c_str());
            //uploadFile(path);

            QMessageBox::information(this, "SUCCESS", "Ad rented!",  QMessageBox::Ok);
            //std::cout << "Ad rented!!" << std::endl;
            on_toRentBtn_pressed();

        }
    }
}

void BrandWindow::uploadFile(char* path) {
    /*std::string url_str = "https://transfer.sh/";
    char *url;
    strcpy(url, url_str.c_str());
    int size = strlen(path);

    char buf[50];
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::list<std::string> headers;
        headers.push_back("Content-Type: text/*");
        sprintf(buf, "Content-Length: %d", size);
        headers.push_back(buf);

        using namespace curlpp::Options;
        request.setOpt(new Verbose(true));
        //request.setOpt(new ReadFunction(curlpp::types::ReadFunctionFunctor(readData)));
        request.setOpt(new InfileSize(size));
        request.setOpt(new Upload(true));
        request.setOpt(new HttpHeader(headers));
        request.setOpt(new Url(url));

        request.perform();
*/}

/**
 * @brief BrandWindow::setUserID
 * @param id
 *
 * Set the user id to know which user is using the brand page
 */
void BrandWindow::setUserID(int id) {
    this->user_id = id;
}
