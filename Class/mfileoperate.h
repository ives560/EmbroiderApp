#ifndef MFILEOPERATE_H
#define MFILEOPERATE_H
//
//文件读写类
//
#include<QFile>
#include<QWidget>
#include"commonType.h"

class MFileOperate
{
public:
    MFileOperate();
    ~MFileOperate();
    LiCodArray CutSegment(int select,char cutsize);
    void AddCutSegmentToArray(SegmentInfo*array,QPoint point,int index);

private:
    void ReadGraphFile();

public:

    QFile m_file;
    bool IsOpen;
    LineCoord m_CurCoord;
    int m_RxFrameNum;//接收针号
    int m_TxFrameNum;//发送针号

    int m_SegArCount; //segmentarray数组当前个数
    SegmentInfo* segmentArray[MAX_SEGMENT_SUM];

};

#endif // MFILEOPERATE_H
