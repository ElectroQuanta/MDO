#include "sharwindow.h"
#include "ui_sharwindow.h"

SharWindow::SharWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SharWindow)
{
    ui->setupUi(this);
}

SharWindow::~SharWindow()
{
    delete ui;
}
