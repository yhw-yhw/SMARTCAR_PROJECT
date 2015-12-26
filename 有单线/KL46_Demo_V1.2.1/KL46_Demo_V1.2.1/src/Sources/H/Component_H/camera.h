/*
*说明：
*本文件包含了所有摄像头相关的配置
*OV7620摄像头图像为640*480，由于这里像素中断经过了4分频，所以列数为640/4=160
*摄像头为隔行扫描，每次只采到半幅图即240行，为节省内存只能扔掉一半的行定义为120
*提取黑线的算法请放到get_black_line()中
*注意：本文件定义的图像大小足以使用，再大会超出KL46自带内存，编译通不过
*图像左侧含有行消隐区，暂时未找到原因（列宽改为了210!）
*2015/1/11 by Sky
*邮箱：sky10834@163.com
*/
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "dma.h"
#include "uart.h"

#define COLUMN          210   //总列数
#define ROW             120   //总行数
#define TRIGER_PORT     PTA2  //定义像素中断触发管脚
#define HREF_PORT       PORTA //行中断管脚
#define HREF_NUM        15    //行中断管脚号
#define VSYN_PORT       PORTA //场中断管脚
#define VSYN_NUM        14    //场中断管脚号

extern u8 PicBuffer[ROW][COLUMN];//图像缓冲区
extern u8 complete_flag;         //采图完成标志
extern u8 temp_row;              //记录当前传输行
extern u8 temp_counter;          //2分计数用

void camera_init();              //DMA初始化
void new_dma(void * DADDR);     //开始DMA传输
void en_href_interrupt();        //行中断打开
void en_vsyn_interrupt();        //打开场中断
void dis_href_interrupt();       //关闭行中断
void dis_vsyn_interrupt();       //关闭场中断
void get_photo();                //开始采集图像
void show_photo();               //串口传输图像
void get_black_line();           //自己的图像处理算法


#endif