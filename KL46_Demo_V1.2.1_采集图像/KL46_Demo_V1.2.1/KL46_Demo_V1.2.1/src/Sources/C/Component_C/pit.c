/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#include "common.h"
#include "pit.h"
extern int Bus_Fre;
#include "vectors.h"

void pit_init_ms( uint32 MS)
{
    uint32 PIT_INTERRUPT_PERIOD=0;
    PIT_INTERRUPT_PERIOD=Bus_Fre;
    
    
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; // 使能PIT
    PIT_MCR  &=  !PIT_MCR_MDIS_MASK | !PIT_MCR_FRZ_MASK;   // MDIS = 0  开启定时器;  FRZ=1 调试模式定时器关闭
    
   
    enable_irq(PIT_irq_no);         //使能PIT0中断       
    PIT_TCTRL0 =  !PIT_TCTRL_TEN_MASK | !PIT_TCTRL_TIE_MASK | !PIT_TCTRL_CHN_MASK; //关闭定时器
    PIT_LDVAL0 = PIT_INTERRUPT_PERIOD*MS; // 1ms定时
    PIT_TFLG0  =   PIT_TFLG_TIF_MASK; // 清除标志
    PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
     
    pit_irq_DIS();
}

/*
void Pit_Init_US(uint32 US)
{
    
  uint32 PIT_INTERRUPT_PERIOD=0;
    PIT_INTERRUPT_PERIOD=Bus_Fre;
   SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; // 使能PIT
    
     
    enable_irq(INT_PIT - 16);         //使能PIT中断
       
    PIT_MCR  =  !PIT_MCR_MDIS_MASK | !PIT_MCR_FRZ_MASK;   // MDIS = 0  开启定时器;  FRZ=1 调试模式定时器关闭
    PIT_TCTRL1 =  !PIT_TCTRL_TEN_MASK | !PIT_TCTRL_TIE_MASK | !PIT_TCTRL_CHN_MASK; //关闭定时器
    PIT_LDVAL1 = PIT_INTERRUPT_PERIOD*US/1000; // 1ms定时
    PIT_TFLG1  =   PIT_TFLG_TIF_MASK; // 清除标志
    PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; 
   
}
*/
/*************************************************************************
*  函数名称：pit_irq_EN
*  功能说明：PITn定时中断使能
*  参数说明：PITn        模块号（PIT0）
*  函数返回：无
*  修改时间：2014-9-25
*  备    注：
*************************************************************************/
void pit_irq_EN(void)
{
     PIT_TCTRL0  |= PIT_TCTRL_TIE_MASK;    //使能 PITn定时器,并开PITn中断  
     enable_irq(PIT_irq_no);                      //开接收引脚的IRQ中断
}

/*************************************************************************
*  函数名称：pit_irq_DIS
*  功能说明：PITn定时中断关闭
*  参数说明：PITn        模块号（PIT0）
*  函数返回：无
*  修改时间：2014-9-25
*  备    注：
*************************************************************************/
void pit_irq_DIS(void)
{
     PIT_TCTRL0 &= ~PIT_TCTRL_TIE_MASK;    //关 PITn定时器, 
     disable_irq(PIT_irq_no);                      //关IRQ中断
}




