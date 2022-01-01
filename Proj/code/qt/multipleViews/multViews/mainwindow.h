#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "machineinfo.h"
#include "settingsinfo.h"
#include "ui_machineinfo.h"
#include "ui_settingsinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_home_pressed();

private:
    Ui::MainWindow *ui;
    // declare pointers to other UIs
    MachineInfo *_machInfo;
    SettingsInfo *_setInfo;
};
#endif // MAINWINDOW_H
