#ifndef MACHINEINFO_H
#define MACHINEINFO_H

#include <QWidget>

namespace Ui {
class MachineInfo;
}

class MachineInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MachineInfo(QWidget *parent = nullptr);
    ~MachineInfo();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

signals:
    void home_pressed();

private:
    Ui::MachineInfo *ui;
};

#endif // MACHINEINFO_H
