/************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[CCD.c] 
* 描  述 ：CCD相关程序
* 原创   ：野火嵌入式开发工作室
*设计改进：Hyoga
*  Email ：498339494@qq.com
*最后更新：2014-03-30
* 说  明 ：本模块包含：前后CCD采样、自适应曝光、寻线、原版CCD上位机发送程序等
***********************************************************************/

#ifndef _CCD_H_
#define _CCD_H_

#include "common.h"
#include "uart.h"
#include "adc.h"
#include "gpio.h"
#include "global.h"
#include "fun.h"

/*
   CCD前： PE4 为SI，PE5 为CLK,PE2为AO ad6a
   CCD后： PB22 为SI，PB23 为CLK，PE3为AO ad7a
*/


#define SI_SetVal_Front()   GPIO_SET(PORTE,4,1)
#define SI_ClrVal_Front()   GPIO_SET(PORTE,4,0)
#define CLK_ClrVal_Front()  GPIO_SET(PORTE,5,0)
#define CLK_SetVal_Front()  GPIO_SET(PORTE,5,1)
#define AO_Front DAD0

#define SI_SetVal_Back()    GPIO_SET(PORTB,22,1)
#define SI_ClrVal_Back()    GPIO_SET(PORTB,22,0)
#define CLK_ClrVal_Back()   GPIO_SET(PORTB,23,0)
#define CLK_SetVal_Back()   GPIO_SET(PORTB,23,1)
#define AO_Back AD7a



void SamplingDelay(void);

void SendImageData(unsigned char * ImageData);

void SendHex(unsigned char hex);
void SendHexPID(s16 hex);

u8 PixelAverage(u8 len, u8 *data);

void ImageCapture_Front(u8 * ImageData);
void ImageCapture_Back(unsigned char * ImageData);

void StartIntegration_Front(void);
void StartIntegration_Back(void);

void CCD_init(void);


#endif  //_FTM_H_



