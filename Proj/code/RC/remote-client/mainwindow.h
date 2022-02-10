#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "adminwindow.h"
#include "brandwindow.h"
#include <mysqlcpp/include/mysqlx/xdevapi.h>
#include <QTimer>
#include <pthread.h>

using namespace mysqlx;

/**
 * @brief The Ad_t struct
 *
 * Structure that encapsulates all the data of an Ad that needs to be sent
 */
struct Ad_t
{
    std::string fname; /**< File name */
    std::string link;  /**< Link ti download the file */
    std::string frag_id;  /**< Fragrance ID */
    std::string filter_id; /**< Filter ID */
    std::string timeSlot_id; /**< Time Slot ID */
    std::string enabled; /**< If the ad is enabled */
}typedef Ad;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**< Mutexes */
    pthread_mutex_t _m_connected;
    pthread_mutex_t _m_send_to_ls;
    pthread_mutex_t _m_update_local_system;

    /**< Conditional variables */
    pthread_cond_t _cond_update_local_system;
    pthread_cond_t _send_to_ls;

    /**< Conection state */
    bool connected = false;

    /**< Threads */
    pthread_t updt_ls;
    pthread_t server;
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
    void timeout_handler();
    static void* update_local_system_thr(void*);
    void upload_and_update(void*);
    static void* server_thr(void*);
    static void* receive_from_ls_thr(void*);
    static void* send_to_ls_thr(void*);
    bool isConnected();
    void connectionEnable(bool);
private:
    Ui::MainWindow *ui;
    AdminWindow *_adminWind;
    BrandWindow *_brandWind;
    Session *sess;
    QTimer *update_ls;
    int update_ls_remaining;
    std::vector<pthread_t> threads;
    pthread_t receive, _send;
    int sock;
    Ad ad_to_send;
};
#endif // MAINWINDOW_H
