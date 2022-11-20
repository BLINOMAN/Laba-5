#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>



class MyWidget : public QWidget
{
    Q_OBJECT

public:
   explicit MyWidget(QWidget *parent = nullptr);

signals:

protected:
   void paintEvent(QPaintEvent *event);
   void wheelEvent(QWheelEvent *event);
   void keyPressEvent(QKeyEvent *event);
   void keyReleaseEvent(QKeyEvent *event);
};

#endif
