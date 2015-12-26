/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#include "PTM.h"               //指示灯驱动程序头文件   
#include "includes.h"
#include "ASSERT.h"
extern int Bus_Fre;
/*************************************************************************
*                      
*
*  函数名称：void KL46_PWM_Init(TPMn n,uint32 Fre, TPM_CHn ch,uint32 duty)
*  功能说明: 产生PWM波
*  参数说明：  n     模块         TPM0  TPM1  TPM2
*             ch    通道号        TPM_CH0 TPM_CH1  TPM_CH2  TPM_CH3  TPM_CH4  TPM_CH5
*            Fre  模块PWM频率    每个模块的各个通道频率必须相同   
*            duty  占空比         初始化后模块的占空比  精度可调节RRESOLUTON
*  函数返回：无
*  修改时间：2013-11-19
*  作者    ：龙丘
*************************************************************************/
void KL46_PWM_Init(TPMn n, TPM_CHn ch,uint32 Fre,uint32 duty)
{
  

   ASSERT( (n == TPM0) || ( (n == n || n == n ) && (ch <= TPM_CH1))); //检查模块和通道的合理性
   //ASSERT( Bus_Fre <= (Fre/2) );       //检查频率的合理性     

  switch(n)
  {
  case TPM0:
    {
    SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;   //enable TPM clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;  //lect PLL as clock source of 
    TPM0_SC |= TPM_SC_PS(0) | TPM_SC_CMOD(1);
    TPM0_MOD = Bus_Fre*1000/Fre;  
  //  ASSERT( duty <= TPM0_MOD );       //检查占空比的合理性 
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
    TPM1_SC |= TPM_SC_PS(3) | TPM_SC_CMOD(1);//改成了8分频
   // ASSERT( duty <= TPM1_MOD );       //检查占空比的合理性
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
    TPM_CLKINn ch=CLK_CH0;//PTC12，可以更改为PTC13
  
    SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;   //enable TPM clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;  //lect PLL as clock source of 
    TPM2_SC = TPM_SC_PS(0) | TPM_SC_CMOD(2);//选择外部时钟计数器出发
    TPM2_CNT=0;
    switch (ch) 
    {
      case CLK_CH0:
        PORTC_PCR12 = PORT_PCR_MUX(4);//B16选择作为TPM_CLKIN
        break;
      case CLK_CH1:
        PORTC_PCR13 = PORT_PCR_MUX(4);//B17选择作为TPM_CLKIN
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
*  函数名称：void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty)
*  功能说明: 改变PWM占空比 
*  参数说明：  n     模块         TPM0  TPM1  TPM2
*             ch    通道号        TPM_CH0 TPM_CH1  TPM_CH2  TPM_CH3  TPM_CH4  TPM_CH5
*             duty  占空比         初始化后模块的占空比  精度可调节RRESOLUTON
*  函数返回：无
*  修改时间：2013-11-19
*  作者    ：龙丘
*************************************************************************/
void TPM_PWM_Duty(TPMn n,TPM_CHn ch,uint32 duty)
{
    u32 mod;

  ASSERT( (n == TPM0) || ( (n == n || n == n ) && (ch <= TPM_CH1))); //检查模块和通道的合理性
   
  switch(n)
  {
  case TPM0:
    {
 //    ASSERT( duty <= TPM0_MOD );       //检查占空比的合理性 
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
  //  ASSERT( duty <= TPM1_MOD );       //检查占空比的合理性
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

