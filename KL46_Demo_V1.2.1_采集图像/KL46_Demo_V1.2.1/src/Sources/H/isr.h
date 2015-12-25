/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#ifndef __ISR_H
#define __ISR_H 1

#undef  VECTOR_038
#define VECTOR_038 PIT0_IRQHandler
extern void PIT0_IRQHandler(void);



#undef VECTOR_028
#define VECTOR_028 UART0_IRQHandler
extern void UART0_IRQHandler(void);

#undef VECTOR_046
#define VECTOR_046 PORTA_IRQHandler
extern void PORTA_IRQHandler(void);




#endif