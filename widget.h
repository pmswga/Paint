#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_open_clicked();

    void on_save_clicked();

    void on_R_valueChanged(int value);

    void on_G_valueChanged(int value);

    void on_B_valueChanged(int value);

    void on_pen_dial_valueChanged(int value);

    void on_pushButton_8_clicked();

private:
    QPen pen;
    QPen pen2;
    QPixmap pixmap;
    QPixmap pixman;
    QPoint lastPoint;
    int r;
    int g;
    int b;
    Ui::Widget *ui;
};

#endif // WIDGET_H
