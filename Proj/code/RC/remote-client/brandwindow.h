#ifndef BRANDWINDOW_H
#define BRANDWINDOW_H

#include <QWidget>

namespace Ui {
class BrandWindow;
}

class BrandWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BrandWindow(QWidget *parent = nullptr);
    ~BrandWindow();
signals:
    void home_pressed(); /**< Dummy signal to indicate return to main Window */

private slots:
    void on_logoutBtn_pressed();

    void on_goBackBtn_pressed();

    void on_rentedBtn_pressed();

    void on_stationsComboBox_activated(int index);

    void on_goBackBtn_2_pressed();

    void on_toRentBtn_pressed();

    void on_stationsComboBox_2_activated(int index);

    void on_calendarWidget_clicked(const QDate &date);

    void on_uploadBtn_pressed();

    void on_rentBtn_pressed();

private:
    Ui::BrandWindow *ui;
};

#endif // BRANDWINDOW_H
