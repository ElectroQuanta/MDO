#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QDateTime>
#include "db-namespaces.h"
#include <iostream>
#include <signal.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <netdb.h>

void panic(char *msg);
#define panic(m)	{perror(m); abort();}

#define UPDATE_LS_TIMEOUT 1
#define TIMEOUT_MS 30000

/**
 * @brief The PageViews enum helps to handle the stackWidget in a more pratical way.
 */
enum PageViews{
    SIGNIN = 0, /**< Sign in screen: displayed when opening the app. */
    REGISTER, /**< To register a user. */
    ADMIN, /**< The admin view: displayed when a user is an admin */
    BRAND, /**< The brand view: displayed when a user is a brand */
};


/**
 * @brief MainWindow::Constructor to the MainWindow
 * @param parent
 *
 * It initializes the MainWindow, creating the connection to the Database and
 * initializing all the threads, mutexes, etc that need to be initialized
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /**< Create session to connect to mySQL */
    sess = new Session("localhost", 33060, "root", "ESRG-MDO-Hugo-Ze@2021", "MDO");


    /**< Initialization - Timer to update local system */
    update_ls = new QTimer(this);
    update_ls_remaining = UPDATE_LS_TIMEOUT;

    /**< Mutexes initialization */
    pthread_mutex_init(&_m_update_local_system, NULL);
    pthread_mutex_init(&_m_connected, NULL);
    pthread_mutex_init(&_m_send_to_ls, NULL);

    /**< Condition variables initialization */
    pthread_cond_init( &_cond_update_local_system, 0);
    pthread_cond_init( &_send_to_ls, 0);

    /**< Instantiate other UI Windows */
     _adminWind = new AdminWindow(sess);
     _brandWind = new BrandWindow(sess);

     /**< Add more UI views */
     ui->stackedWidget->insertWidget(ADMIN, _adminWind);
     ui->stackedWidget->insertWidget(BRAND, _brandWind);
     ui->stackedWidget->setCurrentIndex(SIGNIN);

 /**< Connect signals to slots */
     connect(_adminWind, SIGNAL( home_pressed() ),
             this, SLOT(onLogoutPressed()));
     connect(_brandWind, SIGNAL( home_pressed() ),
             this, SLOT(onLogoutPressed()));
     connect(update_ls, SIGNAL(timeout()), this, SLOT(timeout_handler()));

     /**< Start timer*/
     update_ls->start(TIMEOUT_MS);

     /**< Create thread */
     pthread_create( &updt_ls, NULL,
                         &MainWindow::update_local_system_thr, this );
     pthread_create( &server, NULL,
                         &MainWindow::server_thr, this);
     /**< Receive thread*/
     threads.push_back(receive);
     int sd = 0;
     pthread_create(&receive, 0, receive_from_ls_thr, this);
     //pthread_detach(receive);

     /**< Send thread*/
     threads.push_back(_send);
     pthread_create(&_send, 0, send_to_ls_thr, this);
     //pthread_detach(send);

}

/**
 * @brief MainWindow::~MainWindow
 *
 * MainWindow Destructor
 */
MainWindow::~MainWindow()
{
    /**< Kill thread on the destructor */
    pthread_kill( updt_ls, SIGKILL);
    pthread_kill( server, SIGKILL);
    for(auto it = threads.begin(); it != threads.end(); it++) {
        pthread_kill (*it, SIGKILL);
    }
    delete ui;
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 *
 * Event ensure if the user really wants to quit the app.
 */
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Remote Client",
                                                                tr("Are you sure you want to quit?\n"),
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

/**
 * @brief MainWindow::on_registerBtn_pressed
 *
 * Change window to register window
 */
void MainWindow::on_registerBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(REGISTER);
}

/**
 * @brief MainWindow::on_signInBtn_pressed
 *
 * Event to handle the Sign In of a user
 */
void MainWindow::on_signInBtn_pressed()
{
    std::string username = this->ui->username->text().toStdString(),
            pass = this->ui->password->text().toStdString();
    try{
        /**< Queue on User DB to know if some user matches */
        Row user = sess->sql(UserDB::select_count_where + "username ='" + username + "' AND pass = '" + pass +"'").execute().fetchOne();
        int count = user[0];
    if(count) {
        user = sess->sql(UserDB::select_where + "username ='" + username + "'").execute().fetchOne();
       /**< Verify which is the role of the User - Brand (0) or Admin(1) */
        if(!user[UserDB::ROLE]){
            _brandWind->setUserID(user[UserDB::ID]);
            ui->stackedWidget->setCurrentIndex(BRAND);
            ui->username->setText(QString::null);
            ui->password->setText(QString::null);
            QMessageBox::information(this, "SUCCESS", "Logged in!", QMessageBox::Ok, QMessageBox::Ok);
        }
       else{
            _adminWind->setUserID(user[UserDB::ID]);
            ui->stackedWidget->setCurrentIndex(ADMIN);
            ui->username->setText(QString::null);
            ui->password->setText(QString::null);
            QMessageBox::information(this, "SUCCESS", "Logged in!", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else
        QMessageBox::warning(this, "ERROR", "Credentials are wrong!", QMessageBox::Ok, QMessageBox::Ok);
    }
    catch (const mysqlx::Error &err){
        QMessageBox::warning(this, "ERROR", "Credentials are wrong!", QMessageBox::Ok, QMessageBox::Ok);
    }
}
/**
 * @brief MainWindow::on_cancelBtn_pressed
 *
 * Going back to Sign In page
 */
void MainWindow::on_cancelBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(SIGNIN);
}

/**
 * @brief MainWindow::on_registerBtn_2_pressed
 *
 * Handle the registration of a User, adding it to the BD if everything
 * is in order
 */
void MainWindow::on_registerBtn_2_pressed()
{
    QString password = this->ui->password_2->text(),
            confPassord = this->ui->confPassword->text(),
            email = this->ui->email->text(),
            username = this->ui->username_2->text();
    if(!(email.contains("@") && email.contains(".com")) || email.contains(" ")) {
        QMessageBox::warning(this, "ERROR", "Wrong email format!", QMessageBox::Ok);
    }
    else if(username.isEmpty()) {
        QMessageBox::warning(this, "ERROR", "Type a username!", QMessageBox::Ok);
    }
    else if(username.contains(" ")) {
        QMessageBox::warning(this, "ERROR", "Type a username without spaces!", QMessageBox::Ok);
    }
    else if(password != confPassord) {
        QMessageBox::warning(this, "ERROR", "Passwords don't match!", QMessageBox::Ok);
    }
    else {
        try {
            /**< Query to the User DB to add the new user */
            std::string query = UserDB::insert + "0,'" + username.toStdString() + "','" + email.toStdString() + "','" + password.toStdString() + "')";
            sess->sql(query).execute();
            QMessageBox::information(this, "SUCCESS", "User created Successfully!", QMessageBox::Ok);
            this->ui->email->setText("");
            this->ui->password_2->setText("");
            this->ui->username_2->setText("");
            this->ui->confPassword->setText("");
        }
        catch (const mysqlx::Error &err)
        {
          std::string error(err.what());
          if(error.find("duplicate") && error.find("username"))
            QMessageBox::warning(this, "ERROR", "Username already taken!", QMessageBox::Ok);
          else if(error.find("duplicate") && error.find("email"))
            QMessageBox::warning(this, "ERROR", "Email already taken!", QMessageBox::Ok);
          else
            QMessageBox::warning(this, "ERROR", "Something went wrong! Please try again later...", QMessageBox::Ok);
        }
    }
}

/**
 * @brief MainWindow::on_forgotBtn_pressed
 *
 *  Forget Password handling
 */
void MainWindow::on_forgotBtn_pressed()
{
    QMessageBox::information(this, "FORGOT?", "Thtat's a shame...", QMessageBox::Ok);
}

/**
 * @brief MainWindow::onLogoutPressed
 *
 *  When logging out, the View to go next is the Sign In View
 */
void MainWindow::onLogoutPressed() {
    ui->stackedWidget->setCurrentIndex(PageViews::SIGNIN);
}

/**
 * @brief MainWindow::update_local_system_thr
 * @param arg
 * @return
 *
 * Thread do handle the update of the local System.
 * The thread waits for the condition variable to be set, as soon as
 * it occurs, it calls the function that uploads the file to the internet
 * and send the updates to the local system
 */
void* MainWindow::update_local_system_thr(void *arg) {
    MainWindow *mw = (MainWindow *)arg;

    while(1) {
        pthread_mutex_lock( &mw->_m_update_local_system);
        pthread_cond_wait( &mw->_cond_update_local_system, &mw->_m_update_local_system );
        pthread_mutex_unlock( &mw->_m_update_local_system);

        mw->upload_and_update(mw);

    }


    return nullptr;
}

/**
* @brief MainWindow::upload_and_update
* @param arg
*
* Function that uploads the specific file to the internet, receiveng
* the link that will be sent to the local system to download the file
*/
void MainWindow::upload_and_update(void *arg) {
    MainWindow *mw = (MainWindow *)arg;
    std::stringstream ss1, ss2, ss3, ss4;
    QDate now = QDate::currentDate();
    int week_nr = now.weekNumber();
    int weekday = (now.dayOfWeek()-1);
    ss1 << week_nr;
    std::string week_nr_str = ss1.str();

    /**< Search for the Ad that is going to be shown in the next hour (if exists) */
    Row TimeTable = mw->sess->sql(TimeTableDB::select_from_station + "1 and week = " + week_nr_str).execute().fetchOne();
    int timeTable_id = TimeTable[TimeTableDB::ID];
    ss2 << timeTable_id;
    std::string timeTable_id_str = ss2.str();
    int time_slot_id = QDateTime::currentDateTime().time().hour()+1;
    time_slot_id += 24*weekday;
    ss4 << time_slot_id;
    std::string timeSlot_id_str = ss4.str();


    std::cout << QDateTime::currentDateTime().time().hour()+1 << std::endl;

    Row Ad = mw->sess->sql(AdDB::select_where + "station_id = 1 and timeSlot_id = " + timeSlot_id_str).execute().fetchOne();

    /**< If doesn't exist, return */
    if (Ad.isNull()) {
        std::cout << "No ad to send" << std::endl;
        return;
    }

    int ad_id = Ad[AdDB::ID];
    ss3 << ad_id;
    std::string ad_id_str = ss3.str();

    /**< Search for the Media File */
    Row MediaFile = mw->sess->sql(MediaFileDb::select_where + "ad_id = " + ad_id_str).execute().fetchOne();

    std::string file_name = static_cast<std::string>(MediaFile[MediaFileDb::FILENAME]);

    std::string file_path = QCoreApplication::applicationDirPath().toStdString() + "/../res/" + file_name;
    std::string url_str = "https://transfer.sh/" + file_name;
    const char *path = file_path.c_str();
    const char *url= url_str.c_str();

    /**< Upload the Media File through CURL to transfer.sh*/
    std::ifstream file(path);
    std::stringstream myStream;
     std::copy(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>( ),
            std::ostreambuf_iterator<char>(myStream));
     int size = myStream.str().size();
     char buf[50];

     curlpp::Cleanup cleaner;
           curlpp::Easy request;

           std::list< std::string > headers;
           headers.push_back("Content-Type: text/*");
           sprintf(buf, "Content-Length: %d", size);
           headers.push_back(buf);

           using namespace curlpp::Options;
           request.setOpt(new Verbose(false));
           request.setOpt(new ReadStream(&myStream));
           request.setOpt(new InfileSize(size));
           request.setOpt(new Upload(true));
           request.setOpt(new HttpHeader(headers));
           request.setOpt(new Url(url));
           /**< Receiveng the output (download link) in a file */
           FILE* fp=freopen("link.txt", "w", stdout);
           request.perform();
           freopen ("/dev/tty", "a", stdout);
           std::ifstream link_file("link.txt");

           /**< Get the Download Link */
           std::string buff;
           std::getline(link_file, buff);
           std::string link(buff);

           ad_to_send.fname = file_name;
           ad_to_send.link = link;
           int frag_id = Ad[AdDB::FRAGRANCE_ID];
           std::stringstream s;
           s << frag_id;
           ad_to_send.frag_id = s.str();
           int filter_id = Ad[AdDB::FILTER_ID];
           std::stringstream s2;
           s2 << filter_id;
           ad_to_send.filter_id = s2.str();
           ad_to_send.timeSlot_id = timeSlot_id_str;
           int active = Ad[AdDB::ACTIVE];
           std::stringstream s3;
           s3 << active;
           ad_to_send.enabled = s3.str();
           /**< Siganlize to send the information to the Local System */
           pthread_mutex_lock(&_m_send_to_ls);
           pthread_cond_signal(&_send_to_ls);
           pthread_mutex_unlock( &_m_send_to_ls);
           std::cout << std::endl << link << std::endl;
}

void MainWindow::timeout_handler() {

    /**< Decrement the minutes counter */
    update_ls_remaining--;
    /**< If no time remaining, activate de conditional signal*/
    if(!update_ls_remaining) {
        update_ls_remaining = UPDATE_LS_TIMEOUT;
        pthread_mutex_lock(&_m_update_local_system);
        pthread_cond_signal(&_cond_update_local_system);
        pthread_mutex_unlock( &_m_update_local_system);
    }

}

void* MainWindow::server_thr(void* arg) {
    MainWindow *mw = (MainWindow *)arg;


        int socket_desc , client_sock , c , read_size;
        struct sockaddr_in server , client;
        char client_message[2000];

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
            std::cout << "Could not create socket" << std::endl;
            return 0;
        }
        std::cout << "Socket created" << std::endl;

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8888);

        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
            //print the error message
            std::cout << "bind failed. Error" << std::endl;
            return 0;
        }
        std::cout << "bind done" << std::endl;

        //Listen
        listen(socket_desc , 3);

        //Accept and incoming connection
        std::cout<< "Waiting for incoming connections..." << std::endl;
        c = sizeof(struct sockaddr_in);

        while(1) {
            //accept connection from an incoming client
            client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
            if (client_sock < 0)
            {
                std::cout << "accept failed" << std::endl;
                return 0;
            }
            std::cout << "Connection accepted" << std::endl;
            mw->connectionEnable(true);
            mw->sock = client_sock;
        }


        //Receive a message from client
        /*while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
        {
            //Send the message back to client
            write(client_sock , client_message , strlen(client_message));
        }

        if(read_size == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(read_size == -1)
        {
            perror("recv failed");
        }*/

        return 0;
}

/**
 * @brief MainWindow::receive_from_ls_thr
 * @param arg
 * @return
 *
 * Thread to receive messages from the Local System
 */
void* MainWindow::receive_from_ls_thr(void *arg) {
    MainWindow *mw = (MainWindow *)arg;
     char buffer[256];

     /**< Wait for the connection */
    while(!mw->isConnected());
    /**< When connected, wait to receive something from the Local System*/
    while(1) {
        recv(mw->sock,buffer,sizeof(buffer),0);
        std::cout << "Received: " << buffer << std::endl;
    }

    return 0;
}

void* MainWindow::send_to_ls_thr(void *arg) {
    MainWindow *mw = (MainWindow *)arg;

    std::cout << "Entrou em Enviado" << std::endl;
    while(!mw->isConnected());
    while(1) {
        /**< When connected, wait for the conditional signal to be set*/
        pthread_mutex_lock( &mw->_m_send_to_ls);
        pthread_cond_wait( &mw->_send_to_ls, &mw->_m_send_to_ls);
        pthread_mutex_unlock( &mw->_m_send_to_ls);

        /**< Construct the string to send and send it to the Local System*/
        std::string buff = mw->ad_to_send.fname + "," + mw->ad_to_send.link + "," + mw->ad_to_send.frag_id + "," + mw->ad_to_send.filter_id + "," + mw->ad_to_send.timeSlot_id + "," + mw->ad_to_send.enabled;
        int buf_size = buff.size();

        std::stringstream ss;
        ss << buf_size;
        std::string buf_size_str = ss.str();
        std::string buffer = "A," + buf_size_str + "," + buff;
        send(mw->sock , buffer.c_str(), buffer.size(), 0);
        std::cout << "Enviado!!" << std::endl;
    }/* close the client's channel */
    return 0;
}

/**
 * @brief MainWindow::isConnected
 * @return
 *
 * Function to return the value of the connection to the Local System
 */
bool MainWindow::isConnected() {
    bool connected = false;
    pthread_mutex_lock(&_m_connected);
    connected = this->connected;
    pthread_mutex_unlock(&_m_connected);
    return connected;
}

/**
 * @brief MainWindow::connectionEnable
 * @param connected
 *
 * Function to change the value of the connection to the local system
 */
void MainWindow::connectionEnable(bool connected) {
    pthread_mutex_lock(&_m_connected);
    this->connected = connected;
    pthread_mutex_unlock(&_m_connected);
}
