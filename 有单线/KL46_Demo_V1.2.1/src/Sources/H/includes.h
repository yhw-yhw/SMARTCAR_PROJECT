/********************************************************   
【平    台】龙丘KL46最小系统版
【编    写】龙丘
【Designed】by Chiu Sir
【E-mail  】chiusir@aliyun.com
【软件版本】V2.0
【最后更新】2013年12月24日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
------------------------------------
使用北京龙邱智能科技cortex-M0开发工具箱
*********************************************************/
/*-------------------------------------------------------------------------*/
//文件名: includes.h                                                       *
//说  明: 总头文件,本文件包含:                                             *
//        主函数(main)文件中用到的头文件、外部函数声明及有关常量命名       *
//-------------------------------------------------------------------------*
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include "common.h"                   //通用函数头文件
#include "gpio_cfg.h"
#include "PTM.h" 
#include "pit.h"
#include "lptmr.h"
#include "i2c.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "KL46_light.h"                  //小灯构件头文件
#include "OLED_12864_T.h"
#include "vectors.h"
#include "fun.h"
#include "motor.h"
#include "steer.h"
#include "assert.h"
#include "global.h"
#include "ccd.h"
#include "dma.h"
#include "camera.h"




#endif
