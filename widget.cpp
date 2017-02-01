#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pixmap = QPixmap(ui->label->width(),ui->label->height());
    pixmap.fill();
    pen = QPen( QBrush( Qt::black), 5.0f );
    r = 0;
    g = 0;
    b = 0;

    ui->label->setPixmap(pixmap);

    ui->label->installEventFilter(this);
    ui->red_color->installEventFilter(this);
    ui->orange_color->installEventFilter(this);
    ui->yellow_color->installEventFilter(this);
    ui->green_color->installEventFilter(this);
    ui->blue_color->installEventFilter(this);
    ui->purple_color->installEventFilter(this);
    ui->pushButton_8->installEventFilter(this);
    ui->R->installEventFilter(this);
    ui->G->installEventFilter(this);
    ui->B->installEventFilter(this);
    ui->setcolor->installEventFilter(this);
    ui->pen_dial->installEventFilter(this);
    ui->clear_pixmap->installEventFilter(this);


    ui->red_color->setStyleSheet("Background-color: red;");
    ui->orange_color->setStyleSheet("Background-color: #ffa500");
    ui->yellow_color->setStyleSheet("Background-color: yellow");
    ui->green_color->setStyleSheet("Background-color: green");
    ui->blue_color->setStyleSheet("Background-color: blue");
    ui->purple_color->setStyleSheet("Background-color: #C400AB");

    pen2 = QPen(QBrush(Qt::black), 61.0f);
    QBrush st(QColor(Qt::black),Qt::Dense7Pattern);
    pixman = QPixmap(ui->label_3->width(),ui->label_3->height());
    pixman.fill();
    QPainter p2(&pixman);
    p2.setPen(Qt::SolidLine);
    p2.setBrush(st);
    p2.drawRect(0,0,ui->label_3->width(),ui->label_3->height());
    p2.end();
    ui->label_3->setPixmap(pixman);
    
    this->setFixedSize(this->width(), this->height());
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->label and event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mous = (QMouseEvent*)event;
        QPainter p(&pixmap);
        p.setPen(pen);
        p.drawPoint(mous->pos());
        p.end();
        lastPoint = mous->pos();
        ui->label->setPixmap(pixmap);
    }
    if(obj == ui->label and event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mous = (QMouseEvent*)event;
        QPainter p(&pixmap);
        p.setPen(pen);
        p.drawLine(lastPoint,mous->pos());
        p.end();
        lastPoint = mous->pos();
        ui->label->setPixmap(pixmap);
    }
    if(obj == ui->red_color and event->type() == QEvent::MouseButtonPress) pen.setColor(Qt::red);
    if(obj == ui->orange_color and event->type() == QEvent::MouseButtonPress) pen.setColor(QColor(255, 128, 0));
    if(obj == ui->yellow_color and event->type() == QEvent::MouseButtonPress) pen.setColor(Qt::yellow);
    if(obj == ui->green_color and event->type() == QEvent::MouseButtonPress) pen.setColor(Qt::green);
    if(obj == ui->blue_color and event->type() == QEvent::MouseButtonPress) pen.setColor(Qt::blue);
    if(obj == ui->purple_color and event->type() == QEvent::MouseButtonPress) pen.setColor(QColor(196, 0, 171));
    if(obj == ui->setcolor and event->type() == QEvent::MouseButtonPress)
    {
        bool ok = true;
        r = ui->lineEdit->text().toInt(&ok,10);
        g = ui->lineEdit_2->text().toInt(&ok,10);
        b = ui->lineEdit_3->text().toInt(&ok,10);
        if((r <= 255 or g <= 255 or b <= 255)) pen.setColor(QColor(r,g,b));
        else ui->info->text() = "Введены неверные значения";
    }
    if(obj == ui->pen_dial and event->type() == QEvent::MouseButtonPress and QEvent::MouseMove)
    {
    }
    if(obj == ui->clear_pixmap and event->type() == QEvent::MouseButtonPress)
    {
        pixmap.fill(QColor(Qt::white));
        ui->label->setPixmap(pixmap);
    }
    if(obj == ui->label_3 and event->type() == QEvent::MouseButtonPress)
    {
        pen.setBrush(Qt::Dense5Pattern);
        ui->label->setPixmap(pixmap);
    }
}

void Widget::on_open_clicked()
{
    QString file;
    file = QFileDialog::getOpenFileName(this,tr("Открыть файл"),tr("Картинка.jpg"),tr("JPG (*.jpg)"));
    pixmap.load(file);
}

void Widget::on_save_clicked()
{
    QString file;
    file = QFileDialog::getSaveFileName(this,tr("Сохранить файл"),tr("Картинка.jpg"),tr("JPG (*.jpg"));
    pixmap.save(file);
}

void Widget::on_R_valueChanged(int value)
{
    pen.setColor(QColor(value,ui->B->value(),ui->G->value()));
    ui->Value_1->setNum(value);
}

void Widget::on_G_valueChanged(int value)
{
    pen.setColor(QColor(ui->R->value(),value,ui->G->value()));
    ui->Value_2->setNum(value);
}

void Widget::on_B_valueChanged(int value)
{
    pen.setColor(QColor(ui->R->value(),ui->B->value(),value));
    ui->Value_3->setNum(value);
}

void Widget::on_pen_dial_valueChanged(int value)
{
    pen.setWidthF(value);
    ui->label_2->setNum(value);
}

void Widget::on_pushButton_8_clicked()
{

}
