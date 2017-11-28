#ifndef DEVICESTHREAD_H
#define DEVICESTHREAD_H
//
//底层设备线程
//
#include<QThread>
#include<QWidget>
#include<QMutex>
#include"serial/mserialoperate.h"
#include"ioperate/ioperate.h"
#include"Class/commonType.h"
#include"Class/mfileoperate.h"

class DevicesThread:public QThread
{
    Q_OBJECT

public:
    DevicesThread();
    ~DevicesThread();
    SegInfoArray GetGraphicData();
    void StartPrint();
private:
    void run();
    void run_ReadComm();
    void AnanlsisData(QByteArray);
    void run_TimeOutComm();
    void run_ReadIO();
    void run_WriteComm();
    void InitDrawLine();
private:
    QPoint GetNextSendCoord();
    //void GetNextReceiveCoord();
    void GetNextReceiveCoord(QPoint ponit);
private:
    MFileOperate* m_pgraphFile;//文件操作指针
    MSerialOperate* m_pserial; //串口操作指针
    IOperate* m_pioper;        //io操作指针

    bool haverun;
private:
    char m_frameNum;//针号
    int m_TxSegArIndex;//发送线段数组下标
    int m_RxSegArIndex;//接收线段数组下标
    LiCodArray m_TxCodArray;
   // LiCodArray m_RxCodArray;
    QPoint m_RxPoint;
    QPoint m_catLineEndArray[500];
    bool m_Txable;  //串口发送允许
    bool m_Rxable;  //串口接送允许
    bool m_TxIOable;//允许发送断线命令
    bool m_readIOable;  //io状态读取允许
    QTime IOreadTime;
//signals:
//    void IOChanged(int);//改变信号

};

#endif // DEVICESTHREAD_H
