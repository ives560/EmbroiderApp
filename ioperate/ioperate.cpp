#include "ioperate.h"

IOperate::IOperate()
{
    pressed=false;
    pressstate=0;
    fd=open("/dev/IoCheck",O_RDWR);
    if(fd<0)
       printf("can't open /dev/IoCheck");
}

IOperate::~IOperate()
{
   int err= close(fd);
   if(err<0)
       printf("close /dev/IoCheck fail");
}
//获得口状态
//gpio: 要查询的gpio口
bool IOperate::GetIoValue(int gpio)
{
    unsigned long val=-11;
    ioctl(fd,gpio,&val);
    return (bool)val;
}
