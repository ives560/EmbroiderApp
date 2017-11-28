#ifndef MSERIALOPERATE_H
#define MSERIALOPERATE_H
//
//串口应用类
//
#include<QWidget>
#include<QTime>
#include"Class/commonType.h"
#include"serial/serialport.h"
class MSerialOperate:public QObject
{
public:
    MSerialOperate();
    ~MSerialOperate();

    bool SendPrintCMD(QPoint);
    bool SendStopPrintCMD();
    bool SendMoveCMD(QPoint point);
    bool SendQueryCoordCMD();
    bool SendQueryStateCMD();
    /****************************************/
    bool AnanlsisResponse(QByteArray buffer);
    QPoint AnanlsisResponseCoordCMD(QByteArray buffer);
    /********************************************/
    QByteArray ReceiveData();
    bool CheckFrame();
    /**********************************/
    bool TimeOutCheck();
    void TimeOutRetry();
private:
    char Crc8CheckOut(char* array,int len);

    void TimeOutStop();
    void TimeOutStart();

public:
    bool IsOpen;
    QTime m_timeOut;
    bool timestart;
    uchar m_TxFrame;
    uchar m_RxFrame;
private:
    SerialPort* m_pCom;
    char RxBuffer[20];
    char RxLength;
    char TxBuffer[20];

    char m_timecount;
};

#endif // MSERIALOPERATE_H
