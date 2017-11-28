#ifndef PAINTAREA_H
#define PAINTAREA_H
//
//文本编辑控件
//
#include <QWidget>
#include<QPainter>
#include"Class/commonType.h"

#include"devthread/devicesthread.h"

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);

private:
    void PaintGrid(QPainter* paint,SegInfoArray array);
    void PaintCurrentCoord(QPainter* paint, SegmentInfo pt);
    void PaintBackGround(QPainter* paint);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
public:
    DevicesThread* m_devThread;
    bool startprint;


};

#endif // PAINTAREA_H
