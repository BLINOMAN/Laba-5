#include "mywidget.h"
#include "mainwindow.h"
#include "Signal.h"
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <math.h>

double y_scale_multiplier = 0.15;
double x_scale_multiplier = 2;
bool is_shift_pressed = false;

void draw_graph(QPainter *painter, MyWidget* mw, Signal* sig)
{
    int w_height = mw->height();
    int w_width = mw->width();
    auto distance_x = round(w_width / sig->get_size()) * x_scale_multiplier;
    auto distance_y = round(w_height / std::max(abs(sig->get_max()), abs(sig->get_min()))) * y_scale_multiplier;
    int m_data_size = sig->get_size();
    for(int i = 0; i < m_data_size - 1 ; i++){
        if (i < m_data_size)
            painter->drawLine(10 + i * distance_x, mw->height() / 2 + distance_y * (*sig)[i],
                              10 + (i+1)*distance_x, mw->height() / 2 + distance_y * (*sig)[i + 1]);
    }
}

void draw_axes(QPainter *painter, MyWidget* mw, Signal* sig)
{
    int w_height = mw->height();
    int w_width = mw->width();
    auto distance_x = round(w_width / sig->get_size()) * x_scale_multiplier;
    auto distance_y = round(w_height / std::max(abs(sig->get_max()), abs(sig->get_min()))) * y_scale_multiplier;
    int x_points = w_width / distance_x;
    int y_points = w_height / distance_y;
    auto x_line = QLine(0, w_height / 2, w_width, w_height / 2);
    auto y_line = QLine(10, 0, 10, w_height);
    painter->drawLine(x_line);
    painter->drawLine(y_line);
    for(int i = 0; i < x_points; i++)
    {
        auto x1 = i * distance_x + y_line.x1();
        auto y1 = w_height / 2 - 5;
        auto x2 = i * distance_x + y_line.x2();
        auto y2 = w_height / 2 + 5;
        painter->drawLine(x1, y1, x2, y2);
    }
    for(int i = 0; i < y_points; i++)
    {
        auto x1 = 5;
        auto y1 = i * distance_y;
        auto x2 = 15;
        auto y2 = y1;
        painter->drawLine(x1, w_height / 2 + y1, x2, w_height / 2 + y2);
        painter->drawLine(x1, w_height / 2 - y1, x2, w_height / 2 - y2);
    }
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Signal sig(200, 44100);
    sig.generate_sine(1600, 2);
    draw_graph(&painter, this, &sig);
    draw_axes(&painter, this, &sig);
}

void MyWidget::wheelEvent(QWheelEvent *event)
{
    if(is_shift_pressed)
    {
        if(y_scale_multiplier + 0.0001 * event->delta() < 0)
            y_scale_multiplier = 0.005;
        else
            y_scale_multiplier += 0.0001 * event->delta();
    }
    else
        x_scale_multiplier += 0.001 * event->delta();
    repaint();
    event->accept();
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
       is_shift_pressed = true;
    event->accept();
}

void MyWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
       is_shift_pressed = false;
    event->accept();
}


MyWidget::MyWidget(QWidget *parent) : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
}
