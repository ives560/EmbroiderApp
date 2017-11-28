#ifndef COMMONTYPE_H
#define COMMONTYPE_H
//
//公用自定义数据
//
#include"stdlib.h"
#include"math.h"
#include<QDebug>
#define MAX_SEGMENT_SUM    1024
#define MAX_GRAPH_LENGTH    3000
#define MAX_GRAPH_WIDE      3000
#define GRAPH_RATIO         85      //画到控件中的缩放比例
/***********************************/
#define SERIAL_FRAME_HEAD         0xfe
#define SERIAL_FRAME_END          0xfd

#define SERIAL_PRINT_CMD          0x01//打印命令
#define SERIAL_MOVE_CMD           0x01//移动不打印命令
#define SERIAL_STOPPRINT_CMD      0x10//停止打印命令
#define SERIAL_QUERYPOSTION_CMD   0x21//查询当前位置
#define SERIAL_QUERYSTATE_CMD     0x21//状态查询命令
#define SERIAL_ACTIVESEND_CMD     0xbf&0x7f//主动上传命令
/******************************************/

/**************************************/
//根据图形文件的数据结构，定义出对应的结构体
typedef struct
{
    char           type;
    unsigned short start_x;
    unsigned short start_y;
    unsigned short end_x;
    unsigned short end_y;
    unsigned short circle_x;
    unsigned short circle_y;
    unsigned short circle_type;
    unsigned short rate;

}SegmentInfo;

//线段的起始坐标和结束坐标结构体
typedef struct
{
    unsigned short start_x;
    unsigned short start_y;
    unsigned short end_x;
    unsigned short end_y;

}LineCoord;

//线段数组
typedef struct
{
    int Count;//数组中线段的个数
    int curtIndex;//当前线段在数组中的下标
    LineCoord* Items;//数组指针

}LiCodArray;

//图形文件中的段数组
typedef struct
{
    int Count;//数组中线段的个数
    int curtIndex;//当前线段在数组中的下标
    SegmentInfo* Items;//数组指针

}SegInfoArray;

//指向空类型的数组
typedef struct
{
    int Count;//数组个数
    void* Array;//数组指针
}StrongArray;
/*****************************/
#define IO_ORIGIN_X     0X000001
#define IO_ORIGIN_Y     0X000002
#define IO_BREADLINE    0x000003

#endif // COMMONTYPE_H
