/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#include "PTM.h"               //ָʾ����������ͷ�ļ�   
#include "includes.h"
#include "ASSERT.h"
extern int Bus_Fre;
/*************************************************************************
*                      
*
*  �������ƣ�void KL46_PWM_Init(TPMn n,uint32 Fre, TPM_CHn ch,uint32 duty)
*  ����˵��: ����PWM��
*  ����˵����  n     ģ��         TPM0  TPM1  TPM2
*             ch    ͨ����        TPM_CH0 TPM_CH1  TPM_CH2  TPM_CH3  TPM_CH4  TPM_CH5
*            Fre  ģ��PWMƵ��    ÿ��ģ��ĸ���ͨ��Ƶ�ʱ�����ͬ   
*            duty  ռ�ձ�         ��ʼ����ģ���ռ�ձ�  ���ȿɵ���RRESOLUTON
*  �������أ���
*  �޸�ʱ�䣺2013-11-19
*  ����    ������
*************************************************************************/
void KL46_PWM_Init(TPMn n, TPM_CHn ch,uint32 Fre,uint32 duty)
{
  

   ASSERT( (n == TPM0) || ( (n == n || n == n ) && (ch <= TPM_CH1))); //���ģ���ͨ���ĺ�����
   //ASSERT( Bus_Fre <= (Fre/2) );       //���Ƶ�ʵĺ�����     

  switch(n)
  {
  case TPM0:
    {
    SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;   //enable TPM clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;  //lect PLL as clock source of 
    TPM0_SC |= TPM_SC_PS(0) | TPM_SC_CMOD(1);
    TPM0_MOD = Bus_Fre*1000/Fre;  
  //  ASSERT( duty <= TPM0_MOD );       //���ռ�ձȵĺ����� 
    switch(ch)
    {
    case TPM_CH0:
      {
        PORTC_PCR1 = PORT_PCR_MUX(4); //enable as TPM0_CH5
        TPM0_C0SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C0V =duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    case TPM_CH1:
      {
        PORTC_PCR2 = PORT_PCR_MUX(4); //enable as TPM0_CH5
        TPM0_C1SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C1V = duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    case TPM_CH2:
      {
        PORTC_PCR3 = PORT_PCR_MUX(4); //enable as TPM0_CH5
        TPM0_C2SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C2V = duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    case TPM_CH3:
      {
        PORTC_PCR4 = PORT_PCR_MUX(4); //enable as TPM0_CH5
        TPM0_C3SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C3V = duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    case TPM_CH4:
      {
        PORTC_PCR8 = PORT_PCR_MUX(3); //enable as TPM0_CH5
        TPM0_C4SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C4V = duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    case TPM_CH5:
      {
        PORTC_PCR9 = PORT_PCR_MUX(3); //enable as TPM0_CH5
        TPM0_C5SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
        TPM0_C5V = duty*TPM0_MOD/RRESOLUTON;
        break;
      }
    default:
      break;
    }
    
    
    break;
    }
    case TPM1:
    {
    SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;   //enable TPM clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;  //lect PLL as clock source of 
   
    TPM1_MOD =  Bus_Fre*1000/(Fre*8);
    TPM1_SC |= TPM_SC_PS(3) | TPM_SC_CMOD(1);//�ĳ���8��Ƶ
   // ASSERT( duty <= TPM1_MOD );       //���ռ�ձȵĺ�����
    switch(ch)
    {
     case TPM_CH0:
       {
         PORTA_PCR12 = PORT_PCR_MUX(3); //enable as TPM0_CH5
         TPM1_C0SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
         TPM1_C0V = duty*TPM1_MOD/RRESOLUTON;
         break;
       }
     case TPM_CH1:
       {
         PORTA_PCR13 = PORT_PCR_MUX(3); //enable as TPM0_CH5
         TPM1_C1SC = TPM_CnSC_MSB_MASK |TPM_CnSC_ELSB_MASK;  //PWM edge aligned
         TPM1_C1V = duty*TPM1_MOD/RRESOLUTON;
         break;
       }
      default:
         break;
    }
      break;
    }
    default:
        break;
  } 
  
}
void TPM_counter_init()//TPM0_CH0
{
    TPM_CLKINn ch=CLK_CH0;//PTC12�����Ը���ΪPTC13
  
    SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;   //enable TPM clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;  //lect PLL as clock source of 
    TPM2_SC = TPM_SC_PS(0) | TPM_SC_CMOD(2);//ѡ���ⲿʱ�Ӽ���������
    TPM2_CNT=0;
    switch (ch) 
    {
      case CLK_CH0:
        PORTC_PCR12 = PORT_PCR_MUX(4);//B16ѡ����ΪTPM_CLKIN
        break;
      case CLK_CH1:
        PORTC_PCR13 = PORT_PCR_MUX(4);//B17ѡ����ΪTPM_CLKIN
        break;
      default:
        ASSERT(0);
    }
  
}
uint16 TPM_counter_value(void)
{
  return TPM2_CNT;
}
void TPM_counter_clean(void)
{
  TPM2_CNT=0;
}

/*************************************************************************
*                            LQ_1401CD_Test
*
*  �������ƣ�void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty)
*  ����˵��: �ı�PWMռ�ձ� 
*  ����˵����  n     ģ��         TPM0  TPM1  TPM2
*             ch    ͨ����        TPM_CH0 TPM_CH1  TPM_CH2  TPM_CH3  TPM_CH4  TPM_CH5
*             duty  ռ�ձ�         ��ʼ����ģ���ռ�ձ�  ���ȿɵ���RRESOLUTON
*  �������أ���
*  �޸�ʱ�䣺2013-11-19
*  ����    ������
*************************************************************************/
void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty)
{
    u32 mod;

  ASSERT( (n == TPM0) || ( (n == n || n == n ) && (ch <= TPM_CH1))); //���ģ���ͨ���ĺ�����
   
  switch(n)
  {
  case TPM0:
    {
 //    ASSERT( duty <= TPM0_MOD );       //���ռ�ձȵĺ����� 
    mod = TPM_MOD_REG(TPM0_BASE_PTR); 
    switch(ch)
    {
    case TPM_CH0:
      {
        TPM0_C0V =duty*mod/RRESOLUTON;
        break;
      }
    case TPM_CH1:
      {
        TPM0_C1V = duty*mod/RRESOLUTON;
        break;
      }
    case TPM_CH2:
      {
        TPM0_C2V = duty*mod/RRESOLUTON;
        break;
      }
    case TPM_CH3:
      {
        TPM0_C3V = duty*mod/RRESOLUTON;
        break;
      }
    case TPM_CH4:
      {
        TPM0_C4V = duty*mod/RRESOLUTON;
        break;
      }
    case TPM_CH5:
      {
        TPM0_C5V = duty*mod/RRESOLUTON;
        break;
      }
    default:
      break;
    }
    break;
    }
    case TPM1:
    {
  //  ASSERT( duty <= TPM1_MOD );       //���ռ�ձȵĺ�����
    mod = TPM_MOD_REG(TPM1_BASE_PTR); 
    switch(ch)
    {
     case TPM_CH0:
       {
         TPM1_C0V = duty*mod/RRESOLUTON;
         break;
       }
     case TPM_CH1:
       {
         TPM1_C1V = duty*mod/RRESOLUTON;
         break;
       }
      default:
         break;
    }
      break;
    }
    default:
        break;
  } 
}

