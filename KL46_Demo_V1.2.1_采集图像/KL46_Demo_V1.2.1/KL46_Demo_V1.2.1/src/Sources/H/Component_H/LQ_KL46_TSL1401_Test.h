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
#include "common.h"
#include "includes.h"
#include "gpio.h"
#ifndef _LQ_1401CCD_H
#define _LQ_1401CCD_H
#define  CCD1_TSL_SI_Int    gpio_init (PORTE,4,GPO, 1)   
#define  CCD1_TSL_SCK_Int   gpio_init (PORTE,5,GPO, 1)


#define  CCD1_TSL_AO_Int    KL46_ADC_Init(ADC_8bit);

#define  CCD1_TSL_SI_HIG    GPIO_SET (PORTE,4, 1)
#define  CCD1_TSL_SI_LOW    GPIO_SET (PORTE,4, 0)


#define  CCD1_TSL_SCK_HIG   GPIO_SET (PORTE,5, 1)
#define  CCD1_TSL_SCK_LOW   GPIO_SET (PORTE,5, 0)


#define  CCD1_Pixe_Get      adc_once(DAD0)
void LQ_CCD_Init(void);
void Get_TSL1401(void);
void Image(void) ;
void Dly_us(void);

#endif