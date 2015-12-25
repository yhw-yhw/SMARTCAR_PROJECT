/************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[CCD.c] 
* ��  �� ��CCD��س���
* ԭ��   ��Ұ��Ƕ��ʽ����������
*��ƸĽ���Hyoga
*  Email ��498339494@qq.com
*�����£�2014-03-30
* ˵  �� ����ģ�������ǰ��CCD����������Ӧ�ع⡢Ѱ�ߡ�ԭ��CCD��λ�����ͳ����
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
   CCDǰ�� PE4 ΪSI��PE5 ΪCLK,PE2ΪAO ad6a
   CCD�� PB22 ΪSI��PB23 ΪCLK��PE3ΪAO ad7a
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



