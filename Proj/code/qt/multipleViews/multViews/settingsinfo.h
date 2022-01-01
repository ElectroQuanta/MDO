#ifndef SETTINGSINFO_H
#define SETTINGSINFO_H

#include <QWidget>

namespace Ui {
class SettingsInfo;
}

class SettingsInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsInfo(QWidget *parent = nullptr);
    ~SettingsInfo();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

signals:
    void home_pressed();

private:
    Ui::SettingsInfo *ui;
};

#endif // SETTINGSINFO_H
