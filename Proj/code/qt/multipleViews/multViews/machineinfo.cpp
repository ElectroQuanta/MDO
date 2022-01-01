#include "machineinfo.h"
#include "ui_machineinfo.h"

enum UIPages{
    PAGE1 = 0,
    PAGE2,
};

MachineInfo::MachineInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineInfo)
{
    ui->setupUi(this);

    // set the current view for the stackedwidget
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE1);
}

MachineInfo::~MachineInfo()
{
    delete ui;
}

void MachineInfo::on_pushButton_clicked()
{
    emit home_pressed();
}

void MachineInfo::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE2);
}

void MachineInfo::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(UIPages::PAGE1);
}
