#ifndef SERIALPORT_H
#define SERIALPORT_H
//
//底层串口驱动类
//

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <sys/ioctl.h>
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/

class SerialPort
{
public:
    SerialPort();
    ~SerialPort();
    int Open(char *dev);
    void setBaudRate(int fd, int speed);
    bool setParity(int fd,int databits,int stopbits,int parity);
    void ReadPort(char*,int);
    void writePort(char*,int);
    int bytesAvailable();
private:
    int m_handle;
};

#endif // SERIALPORT_H
