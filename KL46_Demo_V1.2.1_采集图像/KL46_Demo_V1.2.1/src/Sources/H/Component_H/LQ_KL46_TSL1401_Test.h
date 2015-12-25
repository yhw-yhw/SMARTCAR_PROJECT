/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@aliyun.com
������汾��V2.0
�������¡�2013��12��24��
�������Ϣ�ο����е�ַ�� 
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
------------------------------------
ʹ�ñ����������ܿƼ�cortex-M0����������
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