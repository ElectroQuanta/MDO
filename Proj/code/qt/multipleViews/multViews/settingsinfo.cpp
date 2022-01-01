#include "settingsinfo.h"
#include "ui_settingsinfo.h"

enum UIPages{
    PAGE1 = 0,
    PAGE2,
};

SettingsInfo::SettingsInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsInfo)
{
    ui->setupUi(this);
    // set the current view for the stackedwidget
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE1);
}

SettingsInfo::~SettingsInfo()
{
    delete ui;
}

void SettingsInfo::on_pushButton_clicked()
{
    emit home_pressed();
}

void SettingsInfo::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE2);
}

void SettingsInfo::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE1);
}
