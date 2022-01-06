#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "adminwindow.h"
#include "brandwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    /**
     * @brief closeEvent: Handles the event of closing the app.
     * @param event: the closing event.
     */
    void closeEvent (QCloseEvent *event);

private slots:
    /**
     * @brief on_signInBtn_pressed: Handles the sign In press.
     */
    void on_registerBtn_pressed();
    /**
     * @brief on_registerBtn_pressed: Handles the register press.
     */
    void on_signInBtn_pressed();
    /**
     * @brief on_cancelBtn_pressed: Cancel the register action.
     */
    void on_cancelBtn_pressed();
    /**
     * @brief on_registerBtn_2_pressed: registers a user if everyting is in order
     *
     * It registers a user if it inputs a valid email (with @ and .com), if the password is correctly confirmed and if a username is written.
     */
    void on_registerBtn_2_pressed();
    /**
     * @brief on_forgotBtn_pressed: used when the user forgets his password
     */
    void on_forgotBtn_pressed();
    void onLogoutPressed();
private:
    Ui::MainWindow *ui;
    AdminWindow *_adminWind;
    BrandWindow *_brandWind;
};
#endif // MAINWINDOW_H
