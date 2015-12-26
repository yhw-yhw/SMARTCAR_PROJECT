/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#ifndef __LPTMR_H__
#define __LPTMR_H__


//void time_delay_ms(unsigned int count_val);/*不要使用该函数与Pulse Counter模式冲突*/
void lptmr_clear_registers();

uint16 lptmr_counter_value();//PTC5
void lptmr_counter_init(void);
void lptmr_counter_clean(void);

#endif 
