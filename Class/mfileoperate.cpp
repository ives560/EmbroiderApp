#include "mfileoperate.h"
//
//文件读写类
//
MFileOperate::MFileOperate()
{
    m_SegArCount=0;

    m_file.setFileName("/rect.dat");
    IsOpen= m_file.open(QFile::ReadOnly|QFile::Text);
    if(IsOpen==true)
    {
        ReadGraphFile();
    }
}

MFileOperate::~MFileOperate()
{
    if(IsOpen==true)
        m_file.close();
}
//读取图形文件中的数据并保存到结构体数组
void MFileOperate::ReadGraphFile()
{
    char startidx,stopidx,cutype;
    QByteArray line,cut;

    while(!m_file.atEnd())//是否到文件尾
    {
        line= m_file.readLine();//读取文件的一行数据
        line.replace("\n"," ");
        segmentArray[m_SegArCount]=new SegmentInfo;
        memset(segmentArray[m_SegArCount],0,sizeof(SegmentInfo));
        startidx=0; stopidx=0; cutype=0;

        while(line.size()>(startidx+1))//是否到行尾
        {
            stopidx= line.indexOf(" ",startidx+1);
            cut=line.mid(startidx,(stopidx-startidx));
            startidx=stopidx;
            cutype++;
            switch(cutype)//文件中每行存储数据的顺序
            {
                case 1:
                    segmentArray[m_SegArCount]->type=(char)cut.toUShort(); break;
                case 2:
                    segmentArray[m_SegArCount]->start_x=cut.toUShort(); break;
                case 3:
                    segmentArray[m_SegArCount]->start_y=cut.toUShort(); break;
                case 4:
                    segmentArray[m_SegArCount]->end_x=cut.toUShort(); break;
                case 5:
                    segmentArray[m_SegArCount]->end_y=cut.toUShort(); break;
                case 6:
                    segmentArray[m_SegArCount]->circle_x=cut.toUShort(); break;
                case 7:
                    segmentArray[m_SegArCount]->circle_y=cut.toUShort(); break;
                case 8:
                    segmentArray[m_SegArCount]->circle_type=cut.toUShort(); break;
                case 9:
                    segmentArray[m_SegArCount]->rate=cut.toUShort(); break;
            }
        }
        m_SegArCount++;
    }
}
//把当前线段按针距分割
//返回线段坐标数组
//select:要切割的线段在数组中的编号
//cutsize:切割的尺寸大小
LiCodArray MFileOperate::CutSegment(int select,char cutsize)//针距0.1mm,为1，1mm为10
{
    LiCodArray array;
    array.curtIndex=0;

    SegmentInfo *seg=segmentArray[select];
    double rh=seg->end_y-seg->start_y;//起点y轴垂线到终点x轴垂线的距离
    double rw=seg->end_x-seg->start_x;//起点x轴垂线到终点y轴垂线的距离
    double length=sqrt(rh*rh+rw*rw);//起点到终点的距离
    double count=length/cutsize+0.5;
    array.Count =(int)count;

    array.Items=new LineCoord[array.Count];
    array.Items[0].start_x=seg->start_x;
    array.Items[0].start_y=seg->start_y;
    double offset=(cutsize*rw)/length;

    array.Items[0].end_x=seg->start_x+offset;
    offset=(cutsize*rh)/length;

    array.Items[0].end_y=seg->start_y+offset;

    int i;
    for(i=1;i<array.Count;i++)
    {
        array.Items[i].start_x=array.Items[i-1].end_x;
        array.Items[i].start_y=array.Items[i-1].end_y;
        offset=(cutsize*(i+1)*rw)/length;

        array.Items[i].end_x=seg->start_x+offset;
        offset=(cutsize*(i+1)*rh)/length;

        array.Items[i].end_y=seg->start_y+offset;
    }
    return array;
}

//当前运行坐标切割线段为两个线段添加到数组
//array: 线段数组
//point:当前坐标点
//index：要切割的线段在数组中的编号
void MFileOperate::AddCutSegmentToArray(SegmentInfo*array,QPoint point,int index)
{
    array[index].type=segmentArray[index]->type;
    array[index].start_x=segmentArray[index]->start_x;
    array[index].start_y=segmentArray[index]->start_y;
    array[index].end_x=point.x();
    array[index].end_y=point.y();

    array[index+1].type=segmentArray[index]->type;
    array[index+1].start_x=point.x();
    array[index+1].start_y=point.y();
    array[index+1].end_x=segmentArray[index]->end_x;
    array[index+1].end_y=segmentArray[index]->end_y;

}
