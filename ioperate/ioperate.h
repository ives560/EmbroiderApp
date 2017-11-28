#ifndef IOPERATE_H
#define IOPERATE_H
//
//IO口状态读取类
//

#include<sys/types.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
/*******************************************/
#define GPIO_TO_PIN(bank, gpio) (32 * (bank) + (gpio))
/*******************************************/
#define KEY_MENU_RIGHT GPIO_TO_PIN(1,25)
#define KEY_BACK_ENTER GPIO_TO_PIN(1,26)
#define KEY_LEFT_DOWN  GPIO_TO_PIN(1,27)
/*******************************************/
//static const int row_gpios[]={KEY_MENU_RIGHT,KEY_BACK_ENTER,KEY_LEFT_DOWN};
/******************************************/
class IOperate
{
public:
    IOperate();
    ~IOperate();
    bool GetIoValue(int gpio);
private:
    int fd;
public:
    bool pressed;//
    int pressstate;//
    int presscount;//
};

#endif // IOPERATE_H
