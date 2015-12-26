/********************************************************   
【平    台】龙丘KL46最小系统版
【编    写】龙丘
【Designed】by Chiu Sir
【E-mail  】chiusir@aliyun.com
【软件版本】V2.0
【最后更新】2013年12月24日
【相关信息参考下列地址】 
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
------------------------------------
使用北京龙邱智能科技cortex-M0开发工具箱
*********************************************************/

#ifndef _LQ_MMA845x_H
#define _LQ_MMA845x_H
#include "common.h"
#include "includes.h"
#include "KL46_IIC.h"




void accel_init(void);
void hal_dev_mma8451_init(void);
static void pause(void);
uint8 hal_dev_mma8451_read_reg(uint8 addr);
void hal_dev_mma8451_write_reg(uint8 addr, uint8 data);
void accel_init(void);
void accel_read(void);
void accel_test(void);
int iAcclReadX(void) ;
int iAcclReadY(void) ;
int iAcclReadZ(void) ;



#endif