#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_machineinfo.h"
#include "ui_settingsinfo.h"
#include <qobjectdefs.h>

enum UIViews{
    MAIN = 0,
    MACHINE,
    SETTINGS,
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set the current view for the stackedwidget
    ui->stackedWidget->setCurrentIndex(UIViews::MAIN);

    // add UI forms
    _machInfo = new MachineInfo();
    _setInfo = new SettingsInfo();
    ui->stackedWidget->insertWidget(UIViews::MACHINE, _machInfo);
    ui->stackedWidget->insertWidget(UIViews::SETTINGS, _setInfo);

    // connect home_pressed signal to its handler (slot)
    connect(_machInfo, SIGNAL( home_pressed() ),
            this, SLOT( on_home_pressed() ) );
    connect(_setInfo, SIGNAL( home_pressed() ),
            this, SLOT( on_home_pressed() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIViews::MACHINE);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIViews::SETTINGS);
}

void MainWindow::on_home_pressed()
{
    ui->stackedWidget->setCurrentIndex(UIViews::MAIN);
}
