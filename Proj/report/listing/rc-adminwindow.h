#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <mysqlcpp/include/mysqlx/xdevapi.h>

using namespace mysqlx;

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(Session *sess = nullptr, QWidget *parent = nullptr);
    ~AdminWindow();

    void setUserID(int id);
signals:
    void home_pressed(); /**< Dummy signal to indicate return to main Window */

private slots:
    void on_activatedCheckBox_stateChanged(int arg1);

    void on_goBackBtn_pressed();

    void on_statisticsBtn_2_pressed();

    void on_stationsComboBox_activated(int index);

    void on_logoutBtn_pressed();

    void on_poweredCheckBox_stateChanged(int arg1);

    void on_brandComboBox_activated(int index);

    void on_usersBtn_2_pressed();

    void on_goBackBtn_2_pressed();

    void on_usersComboBox_activated(int index);

    void on_saveChangesBtn_pressed();

    void on_discardChangesBtn_pressed();

    void on_goBackBtn_3_pressed();

    void on_adsToActivateBtn_2_pressed();

    void on_testOperationBtn_2_pressed();

    void on_goBackBtn_4_pressed();

    void on_transferVideosBtn_pressed();

    void on_acceptAdBtn_pressed();

    void on_denyAdBtn_pressed();

    void on_adsToActComboBox_activated(int index);

    void on_deleteUserBtn_pressed();

private:
    Ui::AdminWindow *ui;
    Session *sess;
    int user_id;
};

#endif // ADMINWINDOW_H
