#include "serialport.h"

SerialPort::SerialPort()
{
    m_handle=Open("/dev/ttyS3");
    if(m_handle>0)
    {
        setBaudRate(m_handle,115200);
    }
    else
        printf("Can't Open Serial Port!\n");

    if(setParity(m_handle,8,1,'N')==false)
        printf("Set Parity Error\n");

}
//
SerialPort::~SerialPort()
{
    close(m_handle);
}
//读串口数据
void SerialPort::ReadPort(char *data, int maxsize)
{
    read(m_handle,data,maxsize);
}
//写串口数据
void SerialPort::writePort(char *data, int maxsize)
{
    write(m_handle,data,maxsize);
}
//打开串口
int SerialPort::Open(char *dev)
{
    int fd = open( dev, O_RDWR | O_NOCTTY | O_NDELAY);         //| O_NOCTTY | O_NDELAY
    if (-1 == fd)
    {
         perror("Can't Open Serial Port");
         return -1;
     }
     else
     return fd;
}
//
int SerialPort::bytesAvailable()
{
    int numBytes;
    if (ioctl(m_handle, FIONREAD, &numBytes)<0)
        numBytes=0;
    return numBytes;
}
//
int speed_arr[] = {B115200,B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
int name_arr[] = {115200,57600,38400,  19200,  9600,  4800,  2400,  1200,  300};
/**
*@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void
*/
void SerialPort::setBaudRate(int fd, int speed)
{
    int   i;
            int   status;
            struct termios   Opt;
            tcgetattr(fd, &Opt);
            for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
            {
                    if  (speed == name_arr[i])
                    {
                            tcflush(fd, TCIOFLUSH);
                            cfsetispeed(&Opt, speed_arr[i]);
                            cfsetospeed(&Opt, speed_arr[i]);
                            status = tcsetattr(fd, TCSANOW, &Opt);//原为fd1
                            if  (status != 0)
                            {
                                    perror("tcsetattr fd1");
                                    return;
                            }
                            tcflush(fd,TCIOFLUSH);
                    }
            }
}
/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd     类型  int  打开的串口文件句柄
*@param  databits 类型  int 数据位   取值 为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N,E,O,,S
*/
bool SerialPort::setParity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;
            if  ( tcgetattr( fd,&options)  !=  0) {
                    perror("SetupSerial 1");
                    return false;
            }
            options.c_cflag &= ~CSIZE;
            switch (databits) /*设置数据位数*/
            {
            case 7:
                    options.c_cflag |= CS7;
                    break;
            case 8:
                    options.c_cflag |= CS8;
                    break;
            default:
                    fprintf(stderr,"Unsupported data size\n"); return false;
            }
    switch (parity)
    {
            case 'n':
            case 'N':
                    options.c_cflag &= ~PARENB;   /* Clear parity enable */
                    options.c_iflag &= ~INPCK;     /* Enable parity checking */
                    break;
            case 'o':
            case 'O':
                    options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
                    options.c_iflag |= INPCK;             /* Disnable parity checking */
                    break;
            case 'e':
            case 'E':
                    options.c_cflag |= PARENB;     /* Enable parity */
                    options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
                    options.c_iflag |= INPCK;       /* Disnable parity checking */
                    break;
            case 'S':
            case 's':  /*as no parity*/
                options.c_cflag &= ~PARENB;
                    options.c_cflag &= ~CSTOPB;break;
            default:
                    fprintf(stderr,"Unsupported parity\n");
                    return false;
            }
    /* 设置停止位*/
    switch (stopbits)
    {
            case 1:
                    options.c_cflag &= ~CSTOPB;
                    break;
            case 2:
                    options.c_cflag |= CSTOPB;
               break;
            default:
                     fprintf(stderr,"Unsupported stop bits\n");
                     return false;
     }
    /*******自己添加设置从c_iflag c_lflag c_oflag 将终端设置为非规范方式输入*******/
   // options.c_lflag &=~(ICANON|ISIG|ECHO|ECHOE);
   // options.c_iflag &=~(ICRNL|IGNCR);
   // options.c_oflag &=~OPOST;
    options.c_cflag|=CREAD|CLOCAL;
    options.c_lflag&=(~(ICANON|ECHO|ECHOE|ECHOK|ECHONL|ISIG));
    options.c_iflag&=(~(INPCK|IGNPAR|PARMRK|ISTRIP|ICRNL|IXANY));
    options.c_iflag&=(~(INLCR|ICRNL|IGNCR));
    options.c_oflag&=(~OPOST);
    options.c_cflag&=(~CRTSCTS);
    options.c_iflag&=(~(IXON|IXOFF|IXANY));
    /* Set input parity option */
    if (parity != 'n')
            options.c_iflag |= INPCK;
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
            perror("SetupSerial 3");
            return false;
    }
    return true;
}
