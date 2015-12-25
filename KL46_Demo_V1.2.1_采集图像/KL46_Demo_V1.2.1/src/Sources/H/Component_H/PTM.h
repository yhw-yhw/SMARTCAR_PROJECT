/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#ifndef __PTM_H__
#define __PTM_H__ 
#include "common.h"
#define   RRESOLUTON    10000u   //����PWM��ռ�ձȵ��ڵķֱ���

typedef enum TPM_CHn
{   
 //ͨ����       TPM0    TPM1   
  TPM_CH0,//    C1     PTA12   
  TPM_CH1,//    C2     PTA13       
  TPM_CH2,//    C3     ��      
  TPM_CH3,//    C4     ��       
  TPM_CH4,//    C8     ��       
  TPM_CH5 //    C9     ��       
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
void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty);//��ѡ��Χ:TPM0,TPM1

/**TPM2������������ã��ⲿ�������뵽�˿�PTC12*/
void TPM_counter_init(void);//TPM2ģ����Ϊ��������
uint16 TPM_counter_value(void);
void TPM_counter_clean(void);



#endif 
