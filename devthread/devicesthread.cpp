#include "devicesthread.h"
#include<QTime>
//
//底层设备线程
//
DevicesThread::DevicesThread()
{
    m_Txable=false;  //串口发送允许
    m_Rxable=false;  //串口接送允许
    m_TxIOable=false;//允许发送断线命令
    m_readIOable=false;  //io状态读取允许
    m_pserial=new MSerialOperate();
    m_pgraphFile=new MFileOperate();
    m_pioper=new IOperate();
    InitDrawLine();
    IOreadTime=QTime::currentTime();
    haverun=true;
    start();
}

DevicesThread::~DevicesThread()
{
    haverun=false;
    wait();
    delete m_pserial;
    delete m_pgraphFile;
    delete m_pioper;
    delete[] m_TxCodArray.Items;
   // delete[] m_RxCodArray.Items;
}
//
void DevicesThread::InitDrawLine()
{
    m_TxSegArIndex=0;
    m_RxSegArIndex=0;
    m_TxCodArray=m_pgraphFile->CutSegment(m_TxSegArIndex,20);
    m_catLineEndArray[m_TxSegArIndex].setX(m_TxCodArray.Items[m_TxCodArray.Count-1].end_x);
    m_catLineEndArray[m_TxSegArIndex].setY(m_TxCodArray.Items[m_TxCodArray.Count-1].end_y);
    m_RxPoint.setX(0);
    m_RxPoint.setY(0);
}
//线程运行函数
void DevicesThread::run()
{
    while(haverun)
    {
        //run_ReadIO();
        run_WriteComm();
        run_ReadComm();
        //run_TimeOutComm();
    }
}
//判断串口是否超时
void DevicesThread::run_TimeOutComm()
{
    if(m_pserial->TimeOutCheck()==true)
        m_pserial->TimeOutRetry();
}
//读取串口
void DevicesThread::run_ReadComm()
{
    QByteArray buffer=  m_pserial->ReceiveData();
    if(buffer.isEmpty()==false)
        AnanlsisData(buffer);
}
//解析读到的数据
//buffer: 串口接收到的数据数组
void DevicesThread::AnanlsisData(QByteArray buffer)
{
    QPoint point;
    int cmd=(buffer[2]&0x7f);
    switch(cmd)//命令字节
    {
        case SERIAL_PRINT_CMD:
            m_pserial->AnanlsisResponse(buffer);
            m_Txable=true;
            break;
        case SERIAL_ACTIVESEND_CMD:
            point= m_pserial->AnanlsisResponseCoordCMD(buffer);

            //GetNextReceiveCoord(point);
            //GetNextReceiveCoord();//获得接收到的打印坐标
            break;
        case SERIAL_QUERYSTATE_CMD:
            break;
        default:      
            break;
    }
}
//DSP返回的当前坐标
//point: 当前坐标点
void DevicesThread::GetNextReceiveCoord(QPoint point)
{
   // m_pserial->m_RxFrame=m_pserial->m_RxFrame+1;
    if(m_RxSegArIndex<m_pgraphFile->m_SegArCount)
    {
        if(point.x()==m_catLineEndArray[m_RxSegArIndex].x())
        {
            if(point.y()==m_catLineEndArray[m_RxSegArIndex].y())
                m_RxSegArIndex++;
            //qDebug("m_RxSegArIndex=%d",m_RxSegArIndex);
        }
    }
   // qDebug("RxPoint.x=%d,RxPoint.y=%d",point.x(),point.y());
    m_RxPoint=point;
}
//向串口写数据
void DevicesThread::run_WriteComm()
{
    if(m_TxIOable==true)
    {
        m_TxIOable=false;
        m_pserial->SendStopPrintCMD();
    }
    else if(m_Txable==true)//可以向串口写数据
    {
        if(m_pserial->CheckFrame()==true)//检查针号
        {
             QPoint point=GetNextSendCoord();//获得要发送的坐标点
             //qDebug("TxPoint.x=%d,TxPoint.y=%d",point.x(),point.y());
             if((point.x()>=0)&&(point.y()>=0))//坐标点为有效
             {
                 m_pserial->SendPrintCMD(point);//发送坐标数据命令
                 m_RxPoint=point;
                 m_Txable=false;
             }
             else
             {
                 m_Txable=false;
                 delete[] m_TxCodArray.Items;
                 InitDrawLine();
             }
        }
    }
}
//获得下一个打印坐标
QPoint DevicesThread::GetNextSendCoord()
{
    if(m_TxCodArray.Count==m_TxCodArray.curtIndex)
    {
        m_TxSegArIndex++;
        m_RxSegArIndex++;
        if(m_TxSegArIndex<(m_pgraphFile->m_SegArCount-1))//小于线段个数
        {
            delete[] m_TxCodArray.Items;
            m_TxCodArray=m_pgraphFile->CutSegment(m_TxSegArIndex,20);//20, 2毫米
            /**************************************/
            m_catLineEndArray[m_TxSegArIndex].setX(m_TxCodArray.Items[m_TxCodArray.Count-1].end_x);
            m_catLineEndArray[m_TxSegArIndex].setY(m_TxCodArray.Items[m_TxCodArray.Count-1].end_y);
            //qDebug("m_catLineEndArray[m_TxSegArIndex].setX=%d",m_catLineEndArray[m_TxSegArIndex].x());
            //qDebug("m_catLineEndArray[m_TxSegArIndex].setY=%d",m_catLineEndArray[m_TxSegArIndex].y());
        }
        else
            return QPoint(-1,-1);
    }
    LineCoord coord=m_TxCodArray.Items[m_TxCodArray.curtIndex];
    QPoint point=QPoint(coord.end_x,coord.end_y);
    m_TxCodArray.curtIndex++;
    return point;
}
//读取io状态
//先消抖
void DevicesThread::run_ReadIO()
{
    QTime curtime=QTime::currentTime();
    int spen=IOreadTime.msecsTo(curtime);
    if(spen>=20)//延时消抖
    {
        IOreadTime=curtime;
        bool change= m_pioper->GetIoValue(KEY_MENU_RIGHT);
        if(change==true)
        {
            m_pioper->presscount++;
            if(m_pioper->presscount==3)//读3次change都为真，消抖完成
            {
                if(m_pioper->pressstate==0)
                {
                    m_pioper->pressstate=1;
                   if(m_pioper->pressed==false)
                   {
                       m_pioper->pressed=true;
                       m_Txable=false;
                   }
                   else
                   {
                       m_pioper->pressed=false;
                       m_Txable=true;
                   }
                   printf("Button KEY_MENU_RIGHT Pressed!\n");
                }
            }
        }
        else
        {
           m_pioper->pressstate=0;
           m_pioper->presscount=0;
        }
    }
}
//启动打印
void DevicesThread::StartPrint()
{
    m_Txable=true;
}
/*********************************************************/
//获得画图数据

SegInfoArray DevicesThread::GetGraphicData()
{
    SegInfoArray infoarry;
    int curindex=m_RxSegArIndex;
    infoarry.curtIndex=curindex;//接收到的当前线段
    //LineCoord coord=m_RxCodArray.Items[m_RxCodArray.curtIndex];//串口接收到的当前位子
    infoarry.Count=m_pgraphFile->m_SegArCount+1;
    infoarry.Items= new SegmentInfo[infoarry.Count];

    int i;
    for(i=0;i<curindex;i++)
        infoarry.Items[i]=*m_pgraphFile->segmentArray[i];

    m_pgraphFile->AddCutSegmentToArray(infoarry.Items,m_RxPoint,curindex);

    for(i=curindex+2;i<infoarry.Count;i++)
        infoarry.Items[i]=*m_pgraphFile->segmentArray[i-1];
    return infoarry;
}
