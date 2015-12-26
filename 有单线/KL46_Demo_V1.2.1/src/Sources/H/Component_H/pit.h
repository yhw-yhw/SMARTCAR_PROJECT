#ifndef __PIT_H__
#define __PIT_H__


typedef enum PITn
{
  PIT0,
  PIT1
}PITn;

void pit_init_ms(uint32 MS);
//void Pit_Init_US(uint32 US);//智能车中不推荐使用us级定时中断

void pit_irq_EN(void);
void pit_irq_DIS(void);

#define PIT_Flag_Clear(PITn)  PIT_TFLG(PITn)= PIT_TFLG_TIF_MASK 

#endif