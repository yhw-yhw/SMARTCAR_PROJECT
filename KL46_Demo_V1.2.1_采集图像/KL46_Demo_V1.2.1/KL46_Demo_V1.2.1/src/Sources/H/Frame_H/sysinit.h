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
//-------------------------------------------------------------------------*
// 文件名:sysinit.h                                                        *
// 说  明: 系统配置头文件                                                  *
//-------------------------------------------------------------------------*

#ifndef _SYSINIT_H_
#define _SYSINIT_H_
    //1 头文件
    #include "common.h"

#define CLK0_FREQ_HZ        8000000        //定义板载晶振的大小单位hz
#define MCG_CLK_Freq        PLL64         //定义时钟频率，单位MHz  

typedef enum PLLx
{
    PLL72,
    PLL70,
    PLL66,
    PLL64
} PLLx;

#define CLK0_TYPE           0
#define TERM_PORT_NUM       0
#define LOW_POWER  0   
#define CPU_MKL46Z256VMC4

    
void sysinit ();
void enable_abort_button(void);
int pll_init(int crystal_val, unsigned char hgo_val, unsigned char erefs_val, signed char prdiv_val, signed char vdiv_val, unsigned char mcgout_select);
void outSRS(void);

extern int mcg_clk_khz;
extern int core_clk_khz;
extern int periph_clk_khz;
extern int pll_clk_khz;
extern int uart0_clk_khz;
extern uint32 uart0_clk_hz,mcg_clk_hz;
extern int PLL0_PRDIV,PLL0_VDIV;
extern int Bus_Fre;

#endif	



