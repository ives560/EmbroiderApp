#include "mserialoperate.h"

MSerialOperate::MSerialOperate()
{
    m_TxFrame=0;
    m_RxFrame=0;
    RxLength=0;
    m_timecount=0;
    timestart=false;
    m_pCom=new SerialPort();
    IsOpen=true;
}

MSerialOperate::~MSerialOperate()
{
   // if(IsOpen==true)

    delete m_pCom;
}
//超时重发
void MSerialOperate::TimeOutRetry()
{
    TimeOutStop();
    RxLength=0;
    m_timecount++;
    if(m_timecount<=3)
    {
        char len=TxBuffer[1];
        m_pCom->writePort(TxBuffer,len);
        TimeOutStart();
    }
    else
    {
        m_timecount=0;
    }
}
//超时检测
bool MSerialOperate::TimeOutCheck()
{
    if(timestart==true)
    {
        QTime curtime=QTime::currentTime();
        int spen=m_timeOut.msecsTo(curtime);
        if(spen>=500)
            return true;
        else
            return false;
    }
    return false;
}
//启动超时检测
void MSerialOperate::TimeOutStart()
{
    m_timeOut=QTime::currentTime();

    timestart=true;
}
//停止超时检测
void MSerialOperate::TimeOutStop()
{
    timestart=false;
}
//从当前位子移动到新位子，打印
bool MSerialOperate::SendPrintCMD(QPoint point)
{
    if(IsOpen==false)
        return false;
    char cmd[10]={SERIAL_FRAME_HEAD,0x0a,SERIAL_PRINT_CMD,0,0x01,0x10,0x02,0x20,0Xff,SERIAL_FRAME_END};
    cmd[3]=(char)m_TxFrame;
    m_TxFrame++;
    cmd[4]=(char)(point.x()>>8);
    cmd[5]=(char)point.x();
    cmd[6]=(char)(point.y()>>8);
    cmd[7]=(char)point.y();

    cmd[8]=Crc8CheckOut(&cmd[2],6);
    m_pCom->writePort(cmd,0x0a);
    memcpy(TxBuffer,cmd,0x0a);
    m_timecount=0;
    TimeOutStart();
    return true;
}
//查询状态命令
bool MSerialOperate::SendQueryStateCMD()
{
    if(IsOpen==false)
        return false;
    char cmd[6]={SERIAL_FRAME_HEAD,6,SERIAL_QUERYSTATE_CMD,0x00,0Xff,SERIAL_FRAME_END};
    cmd[3]=(char)m_TxFrame;
    m_TxFrame++;

    cmd[12]=Crc8CheckOut(&cmd[2],2);
    m_pCom->writePort(cmd,6);
    memcpy(TxBuffer,cmd,6);
    m_timecount=0;
    TimeOutStart();
    return true;
}
//停止当前打印
bool MSerialOperate::SendStopPrintCMD()
{
    if(IsOpen==false)
        return false;
    char cmd[6]={SERIAL_FRAME_HEAD,6,SERIAL_STOPPRINT_CMD,0x00,0Xff,SERIAL_FRAME_END};
    cmd[3]=(char)m_TxFrame;
    m_TxFrame++;

    cmd[12]=Crc8CheckOut(&cmd[2],2);
    m_pCom->writePort(cmd,6);
    memcpy(TxBuffer,cmd,6);
    m_timecount=0;
    TimeOutStart();
    return true;
}
//从当前位子移动到新位子，不打印
bool MSerialOperate::SendMoveCMD(QPoint point)
{
    if(IsOpen==false)
        return false;
    char cmd[10]={SERIAL_FRAME_HEAD,10,SERIAL_MOVE_CMD,0,0x01,0x10,0x02,0x20,0Xff,SERIAL_FRAME_END};
    cmd[3]=(char)m_TxFrame;
    m_TxFrame++;
    cmd[4]=(char)(point.x()>>8);
    cmd[5]=(char)point.x();
    cmd[6]=(char)(point.y()>>8);
    cmd[7]=(char)point.y();

    cmd[8]=Crc8CheckOut(&cmd[2],6);
    m_pCom->writePort(cmd,10);
    memcpy(TxBuffer,cmd,10);
    m_timecount=0;
    TimeOutStart();
    return true;
}
//让dsp返回当前位子
bool MSerialOperate::SendQueryCoordCMD()
{
    if(IsOpen==false)
        return false;

    return true;
}
//串口数据接收
QByteArray MSerialOperate::ReceiveData()
{
    QByteArray array;

    if(m_pCom->bytesAvailable()>0)
    {
        char byte=0;
        m_pCom->ReadPort(&byte,1);
        RxBuffer[RxLength]=byte;
        RxLength++;

        char len=RxBuffer[1];

        if(RxLength==len)
        {
            TimeOutStop();

            char crc=Crc8CheckOut(&RxBuffer[2],(int)(RxBuffer[1]-4));
            char crcinx=RxBuffer[1]-2;
            if(crc==RxBuffer[crcinx])
            {
                 //array=QByteArray(RxBuffer);
                  array=QByteArray(RxBuffer,RxLength);
            }
            memset(RxBuffer,0,RxLength);
            RxLength=0;
        }
    }
    return array;
}
//解析应答数据
bool MSerialOperate::AnanlsisResponse(QByteArray buffer)
{
    bool retn=false;
    char ask=buffer[4];
    if(ask==0x00)//正确应答
        retn=true;
    else if(ask==0x01)//错误应答
        retn=false;
    return retn;
}
//解析当前坐标数据
QPoint MSerialOperate::AnanlsisResponseCoordCMD(QByteArray buffer)
{
    QPoint point;
    uchar xh=(uchar)buffer[4];
    int xval=xh<<8;
    uchar xl=(uchar)buffer[5];
    xval +=xl;
    point.setX(xval);

    uchar yh=(uchar)buffer[6];
    int yval=yh<<8;
    uchar yl=(uchar)buffer[7];
    yval +=yl;
    point.setY(yval);

    m_RxFrame=buffer[3];//接收针号付值
    if(point.x()<0)
        qDebug("point.x()=%d",point.x());

    if(point.y()<0)
        qDebug("point.y()=%d",point.y());
    return point;
}

//检查针号，判断是否可以发送
bool MSerialOperate::CheckFrame()
{
    bool chark=false;
    int spen=m_TxFrame-m_RxFrame;
    if(spen>=0)
    {
        if(spen>=5)
            chark=false;
        else
            chark=true;
    }
    else if(spen<0)
    {
        if(spen>-250)
            chark=false;
        else
            chark=true;
    }
    return chark;
}
//crc校验
char MSerialOperate::Crc8CheckOut(char* array,int len)
{
    uchar i,crc=0;
    while((len--)!=0)
    {
        for(i=0x80;i!=0;i=(i>>1))
        {
            if((crc&0x80)!=0)
            {
                crc=(crc<<1);//crc *=2;
                crc ^=0x07;
            }//
            else
                crc= crc<<1;
            if(((*array)&i)!=0)
                crc ^=0x07;//再加上本位的crc
        }
        array++;
    }
    return crc;
}
