#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

/**
 * @brief The PageViews enum helps to handle the stackWidget in a more pratical way.
 */
enum PageViews{
    SIGNIN = 0, /**< Sign in screen: displayed when opening the app. */
    REGISTER, /**< To register a user. */
    ADMIN, /**< The admin view: displayed when a user is an admin */
    BRAND, /**< The brand view: displayed when a user is a brand */
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



     /**< Instantiate other UI Windows */
     _adminWind = new AdminWindow();
     _brandWind = new BrandWindow();

     /**< Add more UI views */
     ui->stackedWidget->insertWidget(ADMIN, _adminWind);
     ui->stackedWidget->insertWidget(BRAND, _brandWind);
     ui->stackedWidget->setCurrentIndex(BRAND);

     /**< Connect signals to slots */
         connect(_adminWind, SIGNAL( home_pressed() ),
                 this, SLOT(onLogoutPressed()));
         connect(_brandWind, SIGNAL( home_pressed() ),
                 this, SLOT(onLogoutPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

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


void MainWindow::on_registerBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(REGISTER);
}

void MainWindow::on_signInBtn_pressed()
{
    QString username = this->ui->username->text(),
            password = this->ui->password->text();
    if(username == "brand" && password == "brand") {
        ui->stackedWidget->setCurrentIndex(BRAND);
        ui->username->setText(QString::null);
        ui->password->setText(QString::null);
        QMessageBox::information(this, "SUCCESS", "Logged in!", QMessageBox::Ok, QMessageBox::Ok);
    }
    else if (username == "admin" && password == "admin"){
        ui->stackedWidget->setCurrentIndex(ADMIN);
        ui->username->setText(QString::null);
        ui->password->setText(QString::null);
        QMessageBox::information(this, "SUCCESS", "Logged in!", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {
        QMessageBox::warning(this, "ERROR", "Credentials are wrong!", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_cancelBtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(SIGNIN);
}

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
        QMessageBox::information(this, "SUCCESS", "User created Successfully!", QMessageBox::Ok);
        this->ui->email->setText("");
        this->ui->password_2->setText("");
        this->ui->username_2->setText("");
        this->ui->confPassword->setText("");
    }
}

void MainWindow::on_forgotBtn_pressed()
{
    QMessageBox::information(this, "FORGOT?", "Thtat's a shame...", QMessageBox::Ok);
}

void MainWindow::onLogoutPressed() {
    ui->stackedWidget->setCurrentIndex(PageViews::SIGNIN);
}
