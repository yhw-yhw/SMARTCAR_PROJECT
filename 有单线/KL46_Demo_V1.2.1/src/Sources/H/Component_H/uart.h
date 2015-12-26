/********************************************************   
��ƽ    ̨��KL46��Сϵͳ��
���ײ���ơ�Hyoga
���ο�������
�������¡�2014��11��24��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#ifndef __UART_H__
#define __UART_H__
	
#include "common.h"

    
//Hyogaע��UART0��(UART1��UART2)ʹ�õ�ģ�鲻һ����Ϊ�˸㵽һ�𣬵ײ�ʹ�÷���ֻ����������
#define UARTn  unsigned int
#define UART0  0x4006A000u
#define UART1  0x4006B000u
#define UART2  0x4006C000u
#define UART_PORT UART0  //uartPrintf���ĸ��˿�����������޸�ΪUART1��UART2


#define uart0_RX PTB16     //����0��RX��ѡ��ΧPTE21��PTA1��PTA15��PTB16,PTD6
#define uart0_TX PTB17     //����0��TX��ѡ��ΧPTE20��PTA2��PTA14��PTB17,PTD7
#define uart1_RX PTE1     //����1��RX��ѡ��ΧPTC3��PTE1 ,PTA18
#define uart1_TX PTE0     //����1��TX��ѡ��ΧPTC4��PTE0 ,PTA19  
#define uart2_RX PTD2     //����2��RX��ѡ��ΧPTD2��PTD4��PTE17, PTE23
#define uart2_TX PTE22     //����2��TX��ѡ��ΧPTD3��PTD5, PTE16��PTE22




#define uart0 uart0_BASE_PTR //Сд��uart0��uart1��uart2��Ҫʹ��
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
