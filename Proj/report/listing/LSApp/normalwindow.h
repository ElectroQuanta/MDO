#ifndef NORMALWINDOW_H
#define NORMALWINDOW_H

#include <QWidget>
namespace Ui {class NormalWindow;}

class NormalWindow : public QWidget
{
    Q_OBJECT
public:
    explicit NormalWindow(QWidget *parent = nullptr);
    ~NormalWindow();
signals:
    void home_pressed(); /**< Dummy signal to indicate return to main Window */
private slots:
    void on_pushButton_clicked(); /**< Dummy button to go to Main Window */
private:
    Ui::NormalWindow *ui;
};
#endif // NORMALWINDOW_H
