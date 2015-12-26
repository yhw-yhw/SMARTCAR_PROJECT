/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#ifndef __PTM_H__
#define __PTM_H__ 
#include "common.h"
#define   RRESOLUTON    10000u   //定义PWM波占空比调节的分辨率

typedef enum TPM_CHn
{   
 //通道号       TPM0    TPM1   
  TPM_CH0,//    C1     PTA12   
  TPM_CH1,//    C2     PTA13       
  TPM_CH2,//    C3     ×      
  TPM_CH3,//    C4     ×       
  TPM_CH4,//    C8     ×       
  TPM_CH5 //    C9     ×       
} TPM_CHn;

typedef enum TPMn
{
  TPM0,
  TPM1
} TPMn;
typedef enum TPM_CLKINn
{
  CLK_CH0, //PTC12
  CLK_CH1  //PTC13
} TPM_CLKINn;

void KL46_PWM_Init(TPMn n,TPM_CHn ch,uint32 Fre, uint32 duty);
void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty);//可选范围:TPM0,TPM1

/**TPM2用作脉冲计数用，外部脉冲输入到端口PTC12*/
void TPM_counter_init(void);//TPM2模块作为计数器用
uint16 TPM_counter_value(void);
void TPM_counter_clean(void);



#endif 
