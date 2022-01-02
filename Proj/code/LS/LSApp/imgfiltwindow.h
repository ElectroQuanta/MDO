#ifndef IMGFILTWINDOW_H
#define IMGFILTWINDOW_H

#include <QWidget>

namespace Ui {
class ImgFiltWindow;
}

class ImgFiltWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImgFiltWindow(QWidget *parent = nullptr);
    ~ImgFiltWindow();

private:
    Ui::ImgFiltWindow *ui;
};

#endif // IMGFILTWINDOW_H
