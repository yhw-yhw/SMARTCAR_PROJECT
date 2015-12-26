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
//-------------------------------------------------------------------------*
// �ļ���:sysinit.h                                                        *
// ˵  ��: ϵͳ����ͷ�ļ�                                                  *
//-------------------------------------------------------------------------*

#ifndef _SYSINIT_H_
#define _SYSINIT_H_
    //1 ͷ�ļ�
    #include "common.h"

#define CLK0_FREQ_HZ        8000000        //������ؾ���Ĵ�С��λhz
#define MCG_CLK_Freq        PLL64         //����ʱ��Ƶ�ʣ���λMHz  

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



