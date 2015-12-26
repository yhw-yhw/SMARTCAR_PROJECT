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

#include "sysinit.h"	//头文件
#include "MKL46Z4.h"   //寄存器映像头文件
#include "uart.h"
//全局变量声明
int mcg_clk_khz;
int core_clk_khz;
int periph_clk_khz;
int pll_clk_khz;
int uart0_clk_khz;
uint32 uart0_clk_hz,mcg_clk_hz;
int PLL0_PRDIV=0,PLL0_VDIV=0;
int Bus_Fre=0;

//-------------------------------------------------------------------------*
//函数名: sysinit                                                          *
//功  能: 系统设置                                                         * 
//参  数: 无						  	           *	
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
void sysinit ()
{
  PLLx pllx;
    /*时能端口时钟*/
  SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                      | SIM_SCGC5_PORTB_MASK
                      | SIM_SCGC5_PORTC_MASK
                      | SIM_SCGC5_PORTD_MASK
                      | SIM_SCGC5_PORTE_MASK );
  pllx=MCG_CLK_Freq;
  if(CLK0_FREQ_HZ==8000000)
   {
     
     switch(pllx)
     {
     case PLL72:
         {
          PLL0_PRDIV=3;      // divider eference by 3 = 8/3 MHz
          PLL0_VDIV=27;     // multiply reference by 27 = 72 MHz  24  64
          Bus_Fre=36000;
          break;
         }
      case PLL70:
        {
         PLL0_PRDIV=3;      // divider eference by 3 = 8/3 MHz
         PLL0_VDIV=26;     // multiply reference by 27 = 72 MHz  24  64
         Bus_Fre=35000;
         break;
        }
      case PLL66:
        {
         PLL0_PRDIV=3;      // divider eference by 3 = 8/3 MHz
         PLL0_VDIV=25;     // multiply reference by 27 = 72 MHz  24  64
         Bus_Fre=33000;
         break;
        }
      case PLL64:
        {
         PLL0_PRDIV=3;      // divider eference by 3 = 8/3 MHz
         PLL0_VDIV=24;     // multiply reference by 27 = 72 MHz  24  64
         Bus_Fre=32000;
         break;
       }
     default:
        break;
     }
     
    }
        
        // 释放保留与ackiso：如果从vlls1 vlls2回收，只有一个效果，或vlls3
        // 如果ackiso设置必须在调用pll_init清楚ackiso。或PLL初始化挂在等待证监会初始化，如果在低功耗模式OSC的启用使它先确认， 如果I / O需要使应答前输出和模块的第一保持。
        if (PMC_REGSC &  PMC_REGSC_ACKISO_MASK)
        PMC_REGSC |= PMC_REGSC_ACKISO_MASK;
        SIM_CLKDIV1 = ( 0
                        | SIM_CLKDIV1_OUTDIV1(0)
                        | SIM_CLKDIV1_OUTDIV4(1) );
 
       /* 锁相环将CLKOUT分为内核，系统，和Flash时钟是来自它*/ 
       mcg_clk_hz = pll_init(CLK0_FREQ_HZ,  /* clkin0频率 */
                             LOW_POWER,     /* 等低功耗模式振荡器 */
                             CLK0_TYPE,     /* 晶体振荡器的时钟输入 */
                             PLL0_PRDIV,    /* 锁相环的预分频器值 */
                             PLL0_VDIV,     /* 锁相倍频*/
                             0);            /*不使用输出从该锁相环作为mcgout*/
      /* 检查返回值pll_init()确保没有错误*/
        SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; // 设置pllfllsel选择该时钟源的锁相环
       uart0_clk_khz = ((mcg_clk_hz / 2) / 1000); // uart0时钟频率将为锁相环频率的一半
       /* 使用从pll_init函数定义变量的值，在Khz的核心时钟和外设时钟。这些变量可以被其他需要时钟的功能的系统时钟*/
	 
        mcg_clk_khz = mcg_clk_hz / 1000;
  	core_clk_khz = mcg_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> 28)+ 1);
        periph_clk_khz = core_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> 16)+ 1);
        
        /* 使能引脚中断的中断按钮- PTA4 ，此引脚也可以用来作为NMI中断，但由于NMI水平敏感每个按钮将导致多个中断。*/
        /* 通过GPIO中断而不是意味着我们可以配置为边缘，敏感的中断而=一个中断每按下按钮。*/
       // enable_abort_button();
         
          
        

}

/********************************************************************/
void enable_abort_button(void)
{
    /* 配置PA4管脚为GPIO功能*/
    PORTA_PCR4 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // GPIO is alt1 function for this pin
    
    /* 配置PA4为上升沿触发 */
    PORTA_PCR4 |= PORT_PCR_IRQC(0x9); 
     
    /* 使相关联的IRQ的NVIC */
#ifndef CMSIS
    enable_irq(INT_PORTA-16);      
#else
   // NVIC_EnableIRQ(PORTA_IRQn);
#endif
}




int pll_init(int crystal_val, unsigned char hgo_val, unsigned char erefs_val, signed char prdiv_val, signed char vdiv_val, unsigned char mcgout_select)
{
  unsigned char frdiv_val;
  unsigned char temp_reg;
  unsigned char prdiv, vdiv;
  short i;
  int ref_freq;
  int pll_freq;

  // check if in FEI mode
  if (!((((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x0) && // check CLKS mux has selcted FLL output
      (MCG_S & MCG_S_IREFST_MASK) &&                                  // check FLL ref is internal ref clk
      (!(MCG_S & MCG_S_PLLST_MASK))))                                 // check PLLS mux has selected FLL
  {
    return 0x1;                                                     // return error code
  }

  // check external frequency is less than the maximum frequency
  if  (crystal_val > 50000000) {return 0x21;}

  // check crystal frequency is within spec. if crystal osc is being used as PLL ref
  if (erefs_val)
  {
    if ((crystal_val < 3000000) || (crystal_val > 32000000)) {return 0x22;} // return 1 if one of the available crystal options is not available
  }

  // make sure HGO will never be greater than 1. Could return an error instead if desired.
  if (hgo_val > 0)
  {
    hgo_val = 1; // force hgo_val to 1 if > 0
  }

  // Check PLL divider settings are within spec.
  if ((prdiv_val < 1) || (prdiv_val > 25)) {return 0x41;}
  if ((vdiv_val < 24) || (vdiv_val > 50)) {return 0x42;}

  // Check PLL reference clock frequency is within spec.
  ref_freq = crystal_val / prdiv_val;
  if ((ref_freq < 2000000) || (ref_freq > 4000000)) {return 0x43;}

  // Check PLL output frequency is within spec.
  pll_freq = (crystal_val / prdiv_val) * vdiv_val;
  if ((pll_freq < 48000000) || (pll_freq > 100000000)) {return 0x45;}

  // configure the MCG_C2 register
  // the RANGE value is determined by the external frequency. Since the RANGE parameter affects the FRDIV divide value
  // it still needs to be set correctly even if the oscillator is not being used
      
  temp_reg = MCG_C2;
  temp_reg &= ~(MCG_C2_RANGE0_MASK | MCG_C2_HGO0_MASK | MCG_C2_EREFS0_MASK); // clear fields before writing new values
    
  if (crystal_val <= 8000000)
  {
    temp_reg |= (MCG_C2_RANGE0(1) | (hgo_val << MCG_C2_HGO0_SHIFT) | (erefs_val << MCG_C2_EREFS0_SHIFT));
  }
  else
  {
    temp_reg |= (MCG_C2_RANGE0(2) | (hgo_val << MCG_C2_HGO0_SHIFT) | (erefs_val << MCG_C2_EREFS0_SHIFT));
  }
  MCG_C2 = temp_reg;
  
  // determine FRDIV based on reference clock frequency
  // since the external frequency has already been checked only the maximum frequency for each FRDIV value needs to be compared here.
  if (crystal_val <= 1250000) {frdiv_val = 0;}
  else if (crystal_val <= 2500000) {frdiv_val = 1;}
  else if (crystal_val <= 5000000) {frdiv_val = 2;}
  else if (crystal_val <= 10000000) {frdiv_val = 3;}
  else if (crystal_val <= 20000000) {frdiv_val = 4;}
  else {frdiv_val = 5;}

  // Select external oscillator and Reference Divider and clear IREFS to start ext osc
  // If IRCLK is required it must be enabled outside of this driver, existing state will be maintained
  // CLKS=2, FRDIV=frdiv_val, IREFS=0, IRCLKEN=0, IREFSTEN=0
  temp_reg = MCG_C1;
  temp_reg &= ~(MCG_C1_CLKS_MASK | MCG_C1_FRDIV_MASK | MCG_C1_IREFS_MASK); // Clear values in these fields
  temp_reg |= (MCG_C1_CLKS(2) | MCG_C1_FRDIV(frdiv_val)); // Set the required CLKS and FRDIV values
  MCG_C1 = temp_reg;

  // if the external oscillator is used need to wait for OSCINIT to set
  if (erefs_val)
  {
    for (i = 0 ; i < 20000 ; i++)
    {
      if (MCG_S & MCG_S_OSCINIT0_MASK) break; // jump out early if OSCINIT sets before loop finishes
    }
  if (!(MCG_S & MCG_S_OSCINIT0_MASK)) return 0x23; // check bit is really set and return with error if not set
  }

  // wait for Reference clock Status bit to clear
  for (i = 0 ; i < 2000 ; i++)
  {
    if (!(MCG_S & MCG_S_IREFST_MASK)) break; // jump out early if IREFST clears before loop finishes
  }
  if (MCG_S & MCG_S_IREFST_MASK) return 0x11; // check bit is really clear and return with error if not set

  // Wait for clock status bits to show clock source is ext ref clk
  for (i = 0 ; i < 2000 ; i++)
  {
    if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x2) break; // jump out early if CLKST shows EXT CLK slected before loop finishes
  }
  if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2) return 0x1A; // check EXT CLK is really selected and return with error if not

  // Now in FBE
  // It is recommended that the clock monitor is enabled when using an external clock as the clock source/reference.
  // It is enabled here but can be removed if this is not required.
  MCG_C6 |= MCG_C6_CME0_MASK;
  
  // Configure PLL
  // Configure MCG_C5
  // If the PLL is to run in STOP mode then the PLLSTEN bit needs to be OR'ed in here or in user code.
  temp_reg = MCG_C5;
  temp_reg &= ~MCG_C5_PRDIV0_MASK;
  temp_reg |= MCG_C5_PRDIV0(prdiv_val - 1);    //set PLL ref divider
  MCG_C5 = temp_reg;

  // Configure MCG_C6
  // The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk
  // The loss of lock interrupt can be enabled by seperately OR'ing in the LOLIE bit in MCG_C6
  temp_reg = MCG_C6; // store present C6 value
  temp_reg &= ~MCG_C6_VDIV0_MASK; // clear VDIV settings
  temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(vdiv_val - 24); // write new VDIV and enable PLL
  MCG_C6 = temp_reg; // update MCG_C6

  // wait for PLLST status bit to set
  for (i = 0 ; i < 2000 ; i++)
  {
    if (MCG_S & MCG_S_PLLST_MASK) break; // jump out early if PLLST sets before loop finishes
  }
  if (!(MCG_S & MCG_S_PLLST_MASK)) return 0x16; // check bit is really set and return with error if not set

  // Wait for LOCK bit to set
  for (i = 0 ; i < 4000 ; i++)
  {
    if (MCG_S & MCG_S_LOCK0_MASK) break; // jump out early if LOCK sets before loop finishes
  }
  if (!(MCG_S & MCG_S_LOCK0_MASK)) return 0x44; // check bit is really set and return with error if not set

  // Use actual PLL settings to calculate PLL frequency
  prdiv = ((MCG_C5 & MCG_C5_PRDIV0_MASK) + 1);
  vdiv = ((MCG_C6 & MCG_C6_VDIV0_MASK) + 24);

  // now in PBE

  MCG_C1 &= ~MCG_C1_CLKS_MASK; // clear CLKS to switch CLKS mux to select PLL as MCG_OUT

  // Wait for clock status bits to update
  for (i = 0 ; i < 2000 ; i++)
  {
    if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x3) break; // jump out early if CLKST = 3 before loop finishes
  }
  if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3) return 0x1B; // check CLKST is set correctly and return with error if not

  // Now in PEE
  
  return ((crystal_val / prdiv) * vdiv); //MCGOUT equals PLL output frequency
} // pll_init

