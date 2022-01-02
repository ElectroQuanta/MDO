#ifndef SHARWINDOW_H
#define SHARWINDOW_H

#include <QWidget>

namespace Ui {
class SharWindow;
}

class SharWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SharWindow(QWidget *parent = nullptr);
    ~SharWindow();

private:
    Ui::SharWindow *ui;
};

#endif // SHARWINDOW_H
