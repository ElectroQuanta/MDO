#include "imgfiltwindow.h"
#include "ui_imgfiltwindow.h"

ImgFiltWindow::ImgFiltWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImgFiltWindow)
{
    ui->setupUi(this);
}

ImgFiltWindow::~ImgFiltWindow()
{
    delete ui;
}
