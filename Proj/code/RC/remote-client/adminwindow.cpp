#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>
#include "db-namespaces.h"
#include <iostream>

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
/**
 * @brief The UserType enum
 */
enum UserType {
    ADMIN = 0,
    BRAND,
};

/**
 * @brief AdminWindow::AdminWindow
 * @param sess
 * @param parent
 *
 * AdminWindow constructor that initializes everything that needs to be initialized
 * such as SQL session, the first station to show, etc.
 */
AdminWindow::AdminWindow(Session *sess, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->sess = sess;

    sess->sql(StationDB::select_all).execute();
    std::string station_name;
    SqlResult stations = sess->sql(StationDB::select_all).execute();
    Row station;
    while(station = stations.fetchOne()) {
        station_name = static_cast<std::string>(station[StationDB::NAME]);
        ui->stationsComboBox->addItem(QString::fromStdString(station_name));
    }
    bool checked = false;
    QString ad = "Ad 1", mode = "Normal";
    ui->poweredCheckBox->setChecked(checked);
    ui->currAdLabel_2->setText(ad);
    ui->currModeLabel_2->setText(mode + " Mode");
    ui->stackedWidget->setCurrentIndex(MAIN);
}

/**
 * @brief AdminWindow::~AdminWindow
 *
 * AdminWindow destructor
 */
AdminWindow::~AdminWindow()
{
    delete ui;
}

/**
 * @brief AdminWindow::on_activatedCheckBox_stateChanged
 * @param arg1
 *
 * Function to activate or deactivate an ad
 */
void AdminWindow::on_activatedCheckBox_stateChanged(int arg1)
{

    std::string username = ui->brandComboBox->currentText().toStdString();
    int i = 0, ad_nr = -1;
    do{
        if(ui->brandComboBox->itemText(i) == ui->brandComboBox->currentText())
            ad_nr++;
    }while(i++ != ui->brandComboBox->currentIndex());
    /**< Query to the DB to know to which user belongs the ad*/
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();
    int user_id = user[UserDB::ID];
    std::stringstream ss1;
    ss1 << user_id;
    std::string user_id_str = ss1.str();
    SqlResult ads = sess->sql(AdDB::select_where + "user_id = " + user_id_str).execute();

    i = 0;
    Row ad;
    do {
        ad = ads.fetchOne();
    } while(i++ != ad_nr);

    int id = ad[AdDB::ID];
    std::stringstream ss2;
    ss2 << id;
    std::string ad_id_str = ss2.str();
    /**< Activate/Deactivate the ad according to the previous state */
    if(!this->ui->activatedCheckBox->checkState()) {
        sess->sql(AdDB::deactivate + ad_id_str).execute();
        this->ui->activatedCheckBox->setText("Off");
    }
    else {
        sess->sql(AdDB::activate + ad_id_str).execute();
        this->ui->activatedCheckBox->setText("On");
    }
}

/**
 * @brief AdminWindow::on_goBackBtn_pressed
 *
 * GO back to the main window
 */
void AdminWindow::on_goBackBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(MAIN);
}

/**
 * @brief AdminWindow::on_statisticsBtn_2_pressed
 *
 * Show statistics of a station
 */
void AdminWindow::on_statisticsBtn_2_pressed()
{
    int station_id, user_id;
    std::stringstream ss, ss1;
    QString text;
    /**< Remove previously items from the combobox */
    for(int i = ui->brandComboBox->count(); i >= 0; i--)
        ui->brandComboBox->removeItem(i);

    std::string station_name = ui->stationsComboBox->currentText().toStdString();

    Row station = sess->sql(StationDB::select_where + "name = '" + station_name + "'").execute().fetchOne();

    station_id = station[StationDB::ID];

    ss << station_id;
    std::string station_id_str = ss.str();
    /**< Search for the ads from the selected station */
    SqlResult ads = sess->sql(AdDB::select_from_station + station_id_str).execute();
    Row ad, brand;
    std::string brand_id, brand_name;

    while(ad = ads.fetchOne()) {
        ss1.clear();
        ss1.str("");
        user_id = ad[AdDB::USER_ID];
        ss1 << user_id;
        brand_id = ss1.str();
        brand = sess->sql(UserDB::select_where + "id =" + brand_id).execute().fetchOne();
        brand_name = static_cast<std::string>(brand[UserDB::NAME]);
        ui->brandComboBox->addItem(QString::fromStdString(brand_name));

    }

    ad = sess->sql(AdDB::select_from_station + station_id_str).execute().fetchOne();

    int active = ad[AdDB::ACTIVE];
    if(active)
        ui->activatedCheckBox->setCheckState(Qt::Checked);
    else
        ui->activatedCheckBox->setChecked(Qt::Unchecked);
    ui->stationName->setText(ui->stationsComboBox->currentText());
    ui->stackedWidget->setCurrentIndex(STATISTICS);
}

/**
 * @brief AdminWindow::on_stationsComboBox_activated
 * @param index
 *
 * Show statistics of the selected station (index)
 */
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


/**
 * @brief AdminWindow::on_logoutBtn_pressed
 *
 * Event to handle the logout of a user. If the user really wants to log out
 * it emits a signal to go back to the Sign In page
 */
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

/**
 * @brief AdminWindow::on_poweredCheckBox_stateChanged
 * @param arg1
 *
 * Event to handle the activation of a station
 */
void AdminWindow::on_poweredCheckBox_stateChanged(int arg1)
{
    if(!this->ui->poweredCheckBox->checkState()) {
        this->ui->poweredCheckBox->setText("Off");
    }
    else {
        this->ui->poweredCheckBox->setText("On");
    }
}

/**
 * @brief AdminWindow::on_brandComboBox_activated
 * @param index
 *
 * Event to show the statistics of the selected Ad (index)
 */
void AdminWindow::on_brandComboBox_activated(int index)
{
    int i;
    std::string username = ui->brandComboBox->itemText(index).toStdString();
    i = 0;
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();
    int user_id = user[UserDB::ID];
    std::stringstream ss1;
    ss1 << user_id;
    std::string user_id_str = ss1.str();
    /**< Query to get all the ads from that user */
    SqlResult ads = sess->sql(AdDB::select_where + "user_id = " + user_id_str).execute();
    int ad_nr = -1;
    i=0;
    /**< To know how many ads the user have */
    do{
        if(ui->brandComboBox->itemText(i) == ui->brandComboBox->currentText())
            ad_nr++;
    }while(i++ != ui->brandComboBox->currentIndex());

    i = 0;
    Row ad;
    /**< Search for the selected ad */
    do {
        ad = ads.fetchOne();
    } while(i++ != ad_nr);

    int activated = ad[AdDB::ACTIVE];
    if(activated)
        ui->activatedCheckBox->setChecked(Qt::Checked);

    else
        ui->activatedCheckBox->setChecked(Qt::Unchecked);
}

/**
 * @brief AdminWindow::on_usersBtn_2_pressed
 *
 * Event that switches to the Users page and shows all the users and its carecteristics
 */
void AdminWindow::on_usersBtn_2_pressed()
{
    /**< Remove all previously items added to the combo boxes */
    for(int i = ui->usersComboBox->count(); i >= 0; i--) {
        ui->usersComboBox->removeItem(i);
    }
    for(int i = ui->userTypeComboBox->count(); i >= 0; i--) {
        ui->userTypeComboBox->removeItem(i);
    }

    ui->userTypeComboBox->addItem("BRAND");
    ui->userTypeComboBox->addItem("ADMIN");

    /**< Query to search for all the users */
    SqlResult users = sess->sql(UserDB::select_all).execute();
    Row user;
    std::string name, pass, email;
    while(user = users.fetchOne()) {
        name = static_cast<std::string>(user[UserDB::NAME]);
        ui->usersComboBox->addItem(QString::fromStdString(name));
    }
    /**< Show the carecteristics of the first user selected on the combo box */
    users = sess->sql(UserDB::select_all).execute();
    user = users.fetchOne();
    ui->userTypeComboBox->setCurrentIndex(user[UserDB::ROLE]);
    email = static_cast<std::string>(user[UserDB::EMAIL]);
    ui->emailLabel_2->setText(QString::fromStdString(email));
    ui->stackedWidget->setCurrentIndex(USERS);
}

/**
 * @brief AdminWindow::on_goBackBtn_2_pressed
 *
 * Event to handle the Go Back button, returning to the main page
 */
void AdminWindow::on_goBackBtn_2_pressed()
{
    on_goBackBtn_pressed();
}

/**
 * @brief AdminWindow::on_usersComboBox_activated
 * @param index
 *
 * Event to show the caracteristics of the selected user (index)
 */
void AdminWindow::on_usersComboBox_activated(int index)
{
    UserType type;
    QString email;

    std::string username = ui->usersComboBox->itemText(index).toStdString();

    /**< Search for the selected user on the Database */
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();

    ui->userTypeComboBox->setCurrentIndex(user[UserDB::ROLE]);
    email = QString::fromStdString(static_cast<std::string>(user[UserDB::EMAIL]));
    ui->emailLabel_2->setText(email);
}

/**
 * @brief AdminWindow::on_saveChangesBtn_pressed
 *
 * Event to save the changes made to a specific user
 */
void AdminWindow::on_saveChangesBtn_pressed()
{
    int role_nr = ui->userTypeComboBox->currentIndex();
    std::stringstream ss;
    ss << role_nr;
    std::string role = ss.str();
    std::string username = ui->usersComboBox->currentText().toStdString();
    /**< Query to update the role to the new one (only change that can be made to the user) */
    sess->sql(UserDB::update_role + role + " WHERE username = '" + username + "'").execute();
    QMessageBox::information(this, "SUCCESS!", "User updated with success!!", QMessageBox::Ok);
}

/**
 * @brief AdminWindow::on_discardChangesBtn_pressed
 *
 * Discard changes that were made and that don't want to be saved
 */
void AdminWindow::on_discardChangesBtn_pressed()
{
    on_usersBtn_2_pressed();
}

/**
 * @brief AdminWindow::on_goBackBtn_3_pressed
 *
 * Another go back button handler
 */
void AdminWindow::on_goBackBtn_3_pressed()
{
    on_goBackBtn_pressed();
}

/**
 * @brief AdminWindow::on_adsToActivateBtn_2_pressed
 *
 * Event to show all the ads that need to be activated or rejected by the admin
 */
void AdminWindow::on_adsToActivateBtn_2_pressed()
{
    ui->adsToActivateLabel->setText("Ads To Activate: " + ui->stationsComboBox->currentText());
    for(int i = ui->adsToActComboBox->count(); i >= 0; i--)
        ui->adsToActComboBox->removeItem(i);
    /**< Get the selected station from the Database */
    Row station = sess->sql(StationDB::select_where + "name = '" + ui->stationsComboBox->currentText().toStdString() + "'").execute().fetchOne();
    int station_id = station[StationDB::ID];
    std::stringstream ss1;
    ss1 << station_id;
    std::string station_id_str = ss1.str();
    /**< Get from the Database all the ads from that station that are not activated */
    SqlResult Ads = sess->sql(AdDB::select_where + "station_id = " + station_id_str + " and active = false").execute();
    Row ad;
    while (ad = Ads.fetchOne()) {
        int user_id = ad[AdDB::USER_ID];
        std::stringstream ss2;
        ss2 << user_id;
        std::string user_id_str = ss2.str();
        Row user = sess->sql(UserDB::select_where + "id = " + user_id_str).execute().fetchOne();
        ui->adsToActComboBox->addItem(QString::fromStdString(static_cast<std::string>(user[UserDB::NAME])));
    }
    /**< Show the informations of the first add in the list*/
    ad = sess->sql(AdDB::select_where + "station_id = " + station_id_str + " and active = false").execute().fetchOne();
    if(!ad.isNull()) {
        int fragrance_id = ad[AdDB::FRAGRANCE_ID];
        std::stringstream ss2;
        ss2 << fragrance_id;
        std::string fragrance_id_str = ss2.str();
        Row Fragrance = sess->sql(FragranceDB::select_where + "id =" + fragrance_id_str).execute().fetchOne();
        QString frag_slot = QString::fromStdString(static_cast<std::string>(Fragrance[FragranceDB::NAME]));
        ui->stateLabel->setText("READY");
        ui->fragSlotLabel_2->setText(frag_slot + " | 100%");
        int ad_id = ad[AdDB::ID];
        std::stringstream ss3;
        ss3 << ad_id;
        std::string ad_id_str = ss3.str();
        Row media_file = sess->sql(MediaFileDb::select_where + "ad_id = " + ad_id_str).execute().fetchOne();
        QString media_file_name = QString::fromStdString(static_cast<std::string>(media_file[MediaFileDb::FILENAME]));
        ui->transferVideosBtn->setText(media_file_name);
        int filter_id = ad[AdDB::FILTER_ID];
        std::stringstream ss4;
        ss4 << filter_id;
        std::string filter_id_str = ss4.str();
        Row Filter = sess->sql(FilterDb::select_where + "id =" + filter_id_str).execute().fetchOne();
        QString filter_name = QString::fromStdString(static_cast<std::string>(Filter[FilterDb::NAME]));
        ui->filterLabel_2->setText(filter_name);
    }
    ui->stackedWidget->setCurrentIndex(ADS_TO_ACT);
}

/**
 * @brief AdminWindow::on_testOperationBtn_2_pressed
 *
 * Changes to the page with the test operation
 */
void AdminWindow::on_testOperationBtn_2_pressed()
{
    ui->stackedWidget->setCurrentIndex(TEST_OP);
}

/**
 * @brief AdminWindow::on_goBackBtn_4_pressed
 *
 * Another go back button handler
 */
void AdminWindow::on_goBackBtn_4_pressed()
{
    on_goBackBtn_pressed();
}

/**
 * @brief AdminWindow::on_transferVideosBtn_pressed
 *
 * Event to transfer de video of the selected Ad
 */
void AdminWindow::on_transferVideosBtn_pressed()
{
    QMessageBox::information(this, "SUCCESS!", "Download zip file", QMessageBox::Ok);
}

/**
 * @brief AdminWindow::on_acceptAdBtn_pressed
 *
 * Event to handle when the "accept ad" is pressed. If exists an ad, then
 * accept it and change its value active to true
 */
void AdminWindow::on_acceptAdBtn_pressed()
{
    int ad_nr = -1, i = 0;
    /**< If there are no ads */
    if(ui->adsToActComboBox->currentText() == "") {
            QMessageBox::information(this, "ERROR!", "No ads to accept!", QMessageBox::Ok);
        return;
    }
    do {
        if(ui->adsToActComboBox->itemText(i) == ui->adsToActComboBox->currentText())
            ad_nr++;
    }while(i++ != ui->adsToActComboBox->currentIndex());
    /**< Get the user that owns that ad */
    std::string username = ui->adsToActComboBox->currentText().toStdString();
    i = 0;
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();
    int user_id = user[UserDB::ID];
    std::stringstream ss1;
    ss1 << user_id;
    std::string user_id_str = ss1.str();
    /**< Search for that sprecific ad*/
    SqlResult ads = sess->sql(AdDB::select_where + "user_id = " + user_id_str  + " and active = false").execute();

    i = 0;
    Row ad;
    do {
        ad = ads.fetchOne();
    } while(i++ != ad_nr);

    int id = ad[AdDB::ID];
    std::stringstream ss2;
    ss2 << id;
    std::string ad_id_str = ss2.str();
    /**< Activate the ad*/
    sess->sql(AdDB::activate + ad_id_str).execute();

    QMessageBox::information(this, "SUCCESS!", "Ad accepted", QMessageBox::Ok);
    on_adsToActivateBtn_2_pressed();
}

/**
 * @brief AdminWindow::on_denyAdBtn_pressed
 *
 * Event to handle when the "deny ad" is pressed. If exists an ad, then
 * deny it and and removes it from the database
 */
void AdminWindow::on_denyAdBtn_pressed()
{
    int ad_nr = -1, i = 0;
    /**< In case there are no ads */
    if(ui->adsToActComboBox->currentText() == "") {
            QMessageBox::information(this, "ERROR!", "No ads to deny!", QMessageBox::Ok);
        return;
    }
    do {
        if(ui->adsToActComboBox->itemText(i) == ui->adsToActComboBox->currentText())
            ad_nr++;
    }while(i++ != ui->adsToActComboBox->currentIndex());

    std::string username = ui->adsToActComboBox->currentText().toStdString();
    i = 0;
    /**< Get the user that owns that ad */
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();
    int user_id = user[UserDB::ID];
    std::stringstream ss1;
    ss1 << user_id;
    std::string user_id_str = ss1.str();
    /**< Search for the specific ad */
    SqlResult ads = sess->sql(AdDB::select_where + "user_id = " + user_id_str  + " and active = false").execute();

    i = 0;
    Row ad;
    do {
        ad = ads.fetchOne();
    } while(i++ != ad_nr);

    int id = ad[AdDB::ID];
    std::stringstream ss2;
    ss2 << id;
    std::string ad_id_str = ss2.str();

    /**< Remove the ad from the database */
    sess->sql(AdDB::remove + ad_id_str).execute();

    QMessageBox::information(this, "SUCCESS!", "Ad denied!", QMessageBox::Ok);
    on_adsToActivateBtn_2_pressed();
}

/**
 * @brief AdminWindow::on_adsToActComboBox_activated
 * @param index
 *
 * Event that handles the selected ad from the combo box and shows
 * all its information
 */
void AdminWindow::on_adsToActComboBox_activated(int index)
{
    QString state = "READY", videoFile, filter;
    int slot, perc;

    int ad_nr = -1, i = 0;
    do {
        if(ui->adsToActComboBox->itemText(i) == ui->adsToActComboBox->currentText())
            ad_nr++;
    }while(i++ != ui->adsToActComboBox->currentIndex());
    /**< Search for the user that owns the ad */
    std::string username = ui->adsToActComboBox->currentText().toStdString();
    i = 0;
    Row user = sess->sql(UserDB::select_where + "username = '" + username + "'").execute().fetchOne();
    int user_id = user[UserDB::ID];
    std::stringstream ss1;
    ss1 << user_id;
    std::string user_id_str = ss1.str();
    /**< Search for all the ads owned by the user */
    SqlResult ads = sess->sql(AdDB::select_where + "user_id = " + user_id_str).execute();
    i = 0;
    Row ad;
    do {
        ad = ads.fetchOne();
    } while(i++ != ad_nr);

    /**< Show all the information from the selected ad */
    int fragrance_id = ad[AdDB::FRAGRANCE_ID];
    std::stringstream ss2;
    ss2 << fragrance_id;
    std::string fragrance_id_str = ss2.str();
    Row Fragrance = sess->sql(FragranceDB::select_where + "id =" + fragrance_id_str).execute().fetchOne();
    QString frag_slot = QString::fromStdString(static_cast<std::string>(Fragrance[FragranceDB::NAME]));
    ui->stateLabel->setText("READY");
    ui->fragSlotLabel_2->setText(frag_slot + " | 100%");
    int ad_id = ad[AdDB::ID];
    std::stringstream ss3;
    ss3 << ad_id;
    std::string ad_id_str = ss3.str();
    Row media_file = sess->sql(MediaFileDb::select_where + "ad_id = " + ad_id_str).execute().fetchOne();
    QString media_file_name = QString::fromStdString(static_cast<std::string>(media_file[MediaFileDb::FILENAME]));
    ui->transferVideosBtn->setText(media_file_name);
    int filter_id = ad[AdDB::FILTER_ID];
    std::stringstream ss4;
    ss4 << filter_id;
    std::string filter_id_str = ss4.str();
    Row Filter = sess->sql(FilterDb::select_where + "id =" + filter_id_str).execute().fetchOne();
    QString filter_name = QString::fromStdString(static_cast<std::string>(Filter[FilterDb::NAME]));
    ui->filterLabel_2->setText(filter_name);
    ui->stateLabel_2->setText(state);
}

/**
 * @brief AdminWindow::on_deleteUserBtn_pressed
 *
 * Event that deletes the selected user from the database
 */
void AdminWindow::on_deleteUserBtn_pressed()
{
    std::string username = ui->usersComboBox->currentText().toStdString();

    sess->sql(UserDB::_delete + "username = '" + username + "'").execute();

    QMessageBox::information(this, "SUCCESS!", "User deleted successfully!", QMessageBox::Ok);

    on_usersBtn_2_pressed();
}

/**
 * @brief AdminWindow::setUserID
 * @param id
 *
 * Set the user id to know which user is using the admin page
 */
void AdminWindow::setUserID(int id) {
    this->user_id = id;
}
