#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    startprint=false;
    m_devThread=0;
    this->resize(350,350);
    startTimer(1000);
}

void PaintArea::timerEvent(QTimerEvent *)
{
    this->update();//重绘界面
}
//鼠标单机事件
//调试用，使串口开始发送数据
void PaintArea::mousePressEvent(QMouseEvent *)
{
    if(startprint==false)
    {
        startprint=true;
        m_devThread->StartPrint();
    }
}
//画图事件
void PaintArea::paintEvent(QPaintEvent *)
{
    QImage img;
    img=QImage(350,350,QImage::Format_RGB32);
    img.fill(qRgb(255,255,255));
    QPainter imgpaint(&img);
    imgpaint.setWindow(-4,-345,350,350);
   // PaintBackGround(&imgpaint);
    SegInfoArray array=m_devThread->GetGraphicData();
    PaintGrid(&imgpaint,array);
    PaintCurrentCoord(&imgpaint,array.Items[array.curtIndex]);
    delete[] array.Items;
    QPainter painter(this);
    painter.drawImage(0,0,img);
}
//画全部图案
//paint:
//array:
void PaintArea::PaintGrid(QPainter* paint,SegInfoArray array)
{
    QPen pen(QPen(QColor(255,0,0),1));
    paint->setPen(pen);

    int i;
    for(i=0;i<array.Count;i++)
    {
        if(i>array.curtIndex)
        {
            pen.setColor(QColor(200,200,0));
            paint->setPen(pen);
        }
        SegmentInfo seg=array.Items[i];
        int s_x=seg.start_x/GRAPH_RATIO;
        int s_y=-(seg.start_y/GRAPH_RATIO);
        int e_x=seg.end_x/GRAPH_RATIO;
        int e_y=-(seg.end_y/GRAPH_RATIO);
        switch(seg.type)
        {
            case 0: paint->drawLine(s_x,s_y,e_x,e_y); break;
            case 1:  break;
            case 2:
                pen.setStyle(Qt::DotLine); paint->setPen(pen);
                paint->drawLine(s_x,s_y,e_x,e_y);
                pen.setStyle(Qt::SolidLine); paint->setPen(pen);
                break;
        }
    }
}
//画背景图
void PaintArea::PaintBackGround(QPainter* paint)
{
    paint->setPen(QPen(QColor(200,200,0),1));
    paint->drawRect(1,-1,348,-348);
    paint->setPen(QPen(QColor(200,200,0),1));
    paint->drawRect(35,-35,280,-280);

    for(int i=0;i<7;i++)
        paint->drawLine(35,-(35+(i+1)*40),315,-(35+(i+1)*40));
    for(int j=0;j<4;j++)
        paint->drawLine((35+(j+1)*70),-35,(35+(j+1)*70),-315);
}
//画电机运行到的当前坐标位子，红圆圈
//paint: 画图对象
//pt: 当前坐标位子
void PaintArea::PaintCurrentCoord(QPainter* paint, SegmentInfo pt)
{
    QPen pen=QPen(QPen(QColor(255,0,0),1));
    paint->setPen(pen);
    paint->drawEllipse((pt.end_x-2)/GRAPH_RATIO,-(pt.end_y-2)/GRAPH_RATIO,4,4);
}


