/********************************************************   
【平    台】KL46最小系统版
【底层设计】Hyoga
【参考】龙丘
【最后更新】2014年11月24日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#ifndef __UART_H__
#define __UART_H__
	
#include "common.h"

    
//Hyoga注：UART0和(UART1、UART2)使用的模块不一样，为了搞到一起，底层使用方便只能这样搞了
#define UARTn  unsigned int
#define UART0  0x4006A000u
#define UART1  0x4006B000u
#define UART2  0x4006C000u
#define UART_PORT UART0  //uartPrintf向哪个端口输出，可以修改为UART1、UART2


#define uart0_RX PTB16     //串口0，RX可选范围PTE21、PTA1、PTA15、PTB16,PTD6
#define uart0_TX PTB17     //串口0，TX可选范围PTE20、PTA2、PTA14、PTB17,PTD7
#define uart1_RX PTE1     //串口1，RX可选范围PTC3、PTE1 ,PTA18
#define uart1_TX PTE0     //串口1，TX可选范围PTC4、PTE0 ,PTA19  
#define uart2_RX PTD2     //串口2，RX可选范围PTD2，PTD4，PTE17, PTE23
#define uart2_TX PTE22     //串口2，TX可选范围PTD3，PTD5, PTE16，PTE22




#define uart0 uart0_BASE_PTR //小写的uart0、uart1、uart2不要使用
#define uart1 uart1_BASE_PTR
#define uart2 uart2_BASE_PTR


void uart_init (UARTn uartn, int baud);
void uart_putchar (UARTn uartn, char ch);
char uart_getchar (UARTn uartn);
void uart_sendN (UARTn uartn ,uint8* buff,uint16 len);
void uartSendCh (UARTn uartn, char ch);
void uartSendString (UARTn uartn,char* buff);
void uartRecvString (UARTn uartn,char * buff);
void uartPrintf(char *pcFmt,...);


void uart_irq_EN(UARTn uartn);
void uart_irq_DIS(UARTn uartn);
#endif 
