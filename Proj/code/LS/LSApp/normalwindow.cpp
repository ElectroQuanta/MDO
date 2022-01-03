#include "normalwindow.h"
#include "ui_normalwindow.h"


NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindow)
{
    ui->setupUi(this);

}

NormalWindow::~NormalWindow() { delete ui; }


/* ----- DUMMY ------------- */
void NormalWindow::on_pushButton_clicked(){
    emit home_pressed();
}
/* ----- END DUMMY ------------- */
