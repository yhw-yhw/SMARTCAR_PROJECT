/********************************************************   
��ƽ    ̨��KL46��Сϵͳ��
���ײ���ơ�Hyoga
���ο�������
�������¡�2014��11��24��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/

#include "uart.h"
#include "includes.h"
#include "sysinit.h"	//ͷ�ļ�
#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

extern int Bus_Fre;
extern int periph_clk_khz;
/*********************************************************************************************************************
*                            LQ_KL46Z256
*
*  �������ƣ�void uart_init (UART_MemMapPtr uartch, int baud)
*  ����˵��������0,1,2��ʼ��
*  ����˵����channel  ���ں� ���������uart0,uart1��uart2
             baud    ���ò�����
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*  ����    ��Hyoga
*************************************************************************************************************************/

void uart_init (UARTn uartn, int baud)
{
    register uint16 sbr;
    uint32 temp;
    int sysclk;
    sysclk=periph_clk_khz;
    if(uartn==UART0)
    {
       uint8 i;
    uint32 calculated_baud = 0;
    uint32 baud_diff = 0;
    uint32 osr_val = 0;
    uint32 sbr_val, uart0clk;
    uint32 baud_rate;
    uint32 reg_temp = 0;
    
    sysclk=Bus_Fre;                       
    
    SIM_SCGC4 |= SIM_SCGC4_uart0_MASK; //�򿪴�0��ʱ��
   
    if(uart0_RX == PTE21)
       PORTE_PCR21 = PORT_PCR_MUX(0x4);      //��PTE21��ʹ��uart0_RXD
    else if(uart0_RX == PTA1)
       PORTA_PCR1   = PORT_PCR_MUX(0x2);     //��PTA1��ʹ��uart0_RXD
    else if(uart0_RX == PTA15)
       PORTA_PCR15  = PORT_PCR_MUX(0x3);     //��PTA15��ʹ��uart0_RXD
    else if(uart0_RX == PTB16)
       PORTB_PCR16 = PORT_PCR_MUX(0x3);      //��PTB16��ʹ��uart0_RXD
    else if(uart0_RX == PTD6)
       PORTD_PCR6 = PORT_PCR_MUX(0x3);      //��PTB16��ʹ��uart0_RXD
  
    if(uart0_TX == PTE20)
       PORTE_PCR20 = PORT_PCR_MUX(0x4);     //��PTE20��ʹ��uart0_TXD
    else if(uart0_TX ==  PTA2)
       PORTA_PCR2  = PORT_PCR_MUX(0x2);     //��PTA2��ʹ��uart0_TXD
    else if(uart0_TX == PTA14)
       PORTA_PCR14 = PORT_PCR_MUX(0x3);     //��PTA14��ʹ��uart0_TXD
    else if(uart0_TX == PTB17)
       PORTB_PCR17 = PORT_PCR_MUX(0x3);     //��PTB17��ʹ��uart0_TXD
    else if(uart0_TX == PTD7)
       PORTD_PCR7 =  PORT_PCR_MUX(0x3);     //��PTD7��ʹ��uart0_TXD

    SIM_SOPT2 |= SIM_SOPT2_uart0SRC(1); // ѡ��pllfllclk��Ϊʱ��Դ
    
    uart0_C2 &= ~(uart0_C2_TE_MASK | uart0_C2_RE_MASK);// �����üĴ���ǰ�ر�uart0
  
    if ((sysclk > 50000) || (sysclk < 32))// ���ʱ��ֵ�Ƿ���Ч
    {
        sysclk = 0;
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_uart0SRC_MASK;
        reg_temp |= SIM_SOPT2_uart0SRC(0);
        SIM_SOPT2 = reg_temp;
	while(1)// ����õ�������Ч��������ѭ��
	{}
    }
    
   
    baud_rate = baud;// ��ʼ��������
    uart0clk = sysclk * 1000;// ����ʱ�ӵ�λhz
    i = 4;// ʹ����Ϳ��ܵ�OSRֵ����ĵ�һ�������ʡ�
    sbr_val = (uint32)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));
    if (calculated_baud > baud_rate)
        baud_diff = calculated_baud - baud_rate;
    else
        baud_diff = baud_rate - calculated_baud;
    osr_val = i;
    // ѡ����ѵ�OSRֵ
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));
        
        if (calculated_baud > baud_rate)
            temp = calculated_baud - baud_rate;
        else
            temp = baud_rate - calculated_baud;
        
        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i; 
        }
    }
    
    assert(baud_diff < ((baud_rate / 100) * 3),"UART0���������ô���");
    
        // �����4����8��OSRȻ������֮�䣬�ز�������򿪡� 
        if ((osr_val >3) && (osr_val < 9))
            uart0_C5|= uart0_C5_BOTHEDGE_MASK;
        
        // Setup OSR value 
        reg_temp = uart0_C4;
        reg_temp &= ~uart0_C4_OSR_MASK;
        reg_temp |= uart0_C4_OSR(osr_val-1);
    
        // Write reg_temp to C4 register
        uart0_C4 = reg_temp;
        
        reg_temp = (reg_temp & uart0_C4_OSR_MASK) + 1;
        sbr_val = (uint32)((uart0clk)/(baud_rate * (reg_temp)));
        
         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = uart0_BDH & ~(uart0_BDH_SBR(0x1F));
   
        uart0_BDH = reg_temp |  uart0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        uart0_BDL = (uint8)(sbr_val & uart0_BDL_SBR_MASK);
        
        /* Enable receiver and transmitter */
        uart0_C2 |= (uart0_C2_TE_MASK
                    | uart0_C2_RE_MASK );
        
        return;
    }
    else if (uartn==UART1)
    {
        
          if(uart1_RX == PTE1)
             PORTE_PCR1 = PORT_PCR_MUX(0x3);      //��PTE1��ʹ��uart1_RXD
          else if(uart1_RX == PTA18)
             PORTA_PCR18 = PORT_PCR_MUX(0x3);     //��PTA18��ʹ��uart1_RXD
          else if(uart1_RX == PTC3)
             PORTA_PCR3  = PORT_PCR_MUX(0x3);     //��PTC3��ʹ��uart1_RXD
    
          if(uart1_TX == PTE0)
             PORTE_PCR0 = PORT_PCR_MUX(0x3);     //��PTE0��ʹ��uart1_TXD
          else if(uart1_TX ==  PTA19)
             PORTA_PCR19= PORT_PCR_MUX(0x3);     //��PTA19��ʹ��uart1_TXD
          else if(uart1_TX == PTC4)
             PORTC_PCR4 = PORT_PCR_MUX(0x3);     //��PTC4��ʹ��uart1_TXD
          SIM_SCGC4 |= SIM_SCGC4_uart1_MASK;
          
          /* Make sure that the transmitter and receiver are disabled while we 
       * change settings.
       */
      
      UART_C2_REG(uart1) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

      /* Configure the uart for 8-bit mode, no parity */
      UART_C1_REG(uart1) = 0;	/* We need all default settings, so entire register is cleared */
    
      /* Calculate baud settings */
      sbr = (uint16)((sysclk*1000)/(baud * 16));
        
      /* Save off the current value of the uartx_BDH except for the SBR field */
      temp = UART_BDH_REG(uart1) & ~(UART_BDH_SBR(0x1F));
    
      UART_BDH_REG(uart1) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
      UART_BDL_REG(uart1) = (uint8)(sbr & UART_BDL_SBR_MASK);
  
      /* Enable receiver and transmitter */
      UART_C2_REG(uart1) |= (UART_C2_TE_MASK| UART_C2_RE_MASK );
         
     }
     else
     { 
          if(uart2_RX == PTD2)
             PORTD_PCR2 = PORT_PCR_MUX(0x3);      //��PTD2��ʹ��uart2_RXD
          else if(uart2_RX == PTD4)
             PORTD_PCR4 = PORT_PCR_MUX(0x3);      //��PTD4��ʹ��uart2_RXD
          else if(uart2_RX == PTE17) 
             PORTE_PCR17= PORT_PCR_MUX(0x3);      //��PTE17��ʹ��uart2_RXD
          else if(uart2_RX == PTE23) 
             PORTE_PCR23= PORT_PCR_MUX(0x4);      //��PTE23��ʹ��uart2_RXD
    
          if(uart2_TX == PTD3)
             PORTD_PCR3 = PORT_PCR_MUX(0x3);     //��PTD3��ʹ��uart2_TX
          else if(uart2_TX ==  PTD5)
             PORTD_PCR5= PORT_PCR_MUX(0x3);      //��PTD5��ʹ��uart2_TX
          else if(uart2_TX == PTE16)
             PORTE_PCR16 = PORT_PCR_MUX(0x3);    //��PTE16��ʹ��uart2_TX
          else if(uart2_TX == PTE22)
             PORTE_PCR22 = PORT_PCR_MUX(0x4);    //��PTE22��ʹ��uart2_TX
           SIM_SCGC4 |= SIM_SCGC4_uart2_MASK;
           
           /* Make sure that the transmitter and receiver are disabled while we 
       * change settings.
       */
      
      UART_C2_REG(uart2) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

      /* Configure the uart for 8-bit mode, no parity */
      UART_C1_REG(uart2) = 0;	/* We need all default settings, so entire register is cleared */
    
      /* Calculate baud settings */
      sbr = (uint16)((sysclk*1000)/(baud * 16));
        
      /* Save off the current value of the uartx_BDH except for the SBR field */
      temp = UART_BDH_REG(uart2) & ~(UART_BDH_SBR(0x1F));
    
      UART_BDH_REG(uart2) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
      UART_BDL_REG(uart2) = (uint8)(sbr & UART_BDL_SBR_MASK);
  
      /* Enable receiver and transmitter */
      UART_C2_REG(uart2) |= (UART_C2_TE_MASK| UART_C2_RE_MASK );
      }
    
}
/*********************************************************************************************************************
*                            LQ_KL46Z256
*
*  �������ƣ�void uart_putchar (UART_MemMapPtr channel, char ch)
*  ����˵��������0,1,2����һ���ֽ�
*  ����˵����channel  ���ں� ���������uart0,uart1��uart2
             ch      ��Ҫ���͵��ֽ�
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*************************************************************************************************************************/
void uart_putchar (UARTn uartn, char ch)
{
  switch (uartn)
  {
    case UART0:
        /* Wait until space is available in the FIFO */
      while(!(uart0_S1_REG(uart0) & uart0_S1_TDRE_MASK));
      /* Send the character */
      uart0_D_REG(uart0) = (uint8)ch;
      break;
    case UART1:
      /* Wait until space is available in the FIFO */
      while(!(UART_S1_REG(uart1) & UART_S1_TDRE_MASK));
      /* Send the character */
      UART_D_REG(uart1) = (uint8)ch;
      break;
    case UART2:
      /* Wait until space is available in the FIFO */
      while(!(UART_S1_REG(uart2) & UART_S1_TDRE_MASK));
      /* Send the character */
      UART_D_REG(uart2) = (uint8)ch;
      break;
  }
    
 }
/*********************************************************************************************************************
*                            LQ_KL46Z256
*
*  �������ƣ�char uart_getchar (UART_MemMapPtr channel)
*  ����˵��������0,1,2����һ���ֽ�
*  ����˵����channel  ���ں� ���������uart0,uart1��uart2
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*  ����    ��Hyoga
*************************************************************************************************************************/
char uart_getchar (UARTn uartn)
{
  switch (uartn)
  {
    case UART0:
     while (!(uart0_S1_REG(uart0) & uart0_S1_RDRF_MASK));
     return uart0_D_REG(uart0);
     break;
    case UART1:
      /* Wait until character has been received */
      while (!(UART_S1_REG(uart1) & UART_S1_RDRF_MASK));
      /* Return the 8-bit data from the receiver */
      return UART_D_REG(uart1);
      break;
    case UART2:
      /* Wait until character has been received */
      while (!(UART_S1_REG(uart2) & UART_S1_RDRF_MASK));
      /* Return the 8-bit data from the receiver */
      return UART_D_REG(uart2);
      break;
    default:
      break;
  }
  return -1;
}
/*********************************************************************************************************************
*                            LQ_KL46Z256
*
*  �������ƣ�void uart_sendN1 (UART_MemMapPtr uartch ,uint8* buff,uint16 len)
*  ����˵��������0,1,2�����ַ���
*  ����˵����channel     ���ں� ���������uart0,uart1��uart2
*            Buff       ��Ҫ���͵��ֽ�
*            len       �ַ����ĳ���
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*  ����    ������
*************************************************************************************************************************/
void uart_sendN (UARTn uartn ,uint8* buff,uint16 len)
{
    int i;
	for(i=0;i<len;i++)
    {
		uart_putchar(uartn,buff[i]);
    }
}
/*
************************************************************************
*  �������ƣ�uart_irq_EN
*  ����˵���������ڽ����ж�
*  ����˵����UARTn       ģ��ţ�UART0~UART2��
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*  ��    ע��
************************************************************************
*/
void uart_irq_EN(UARTn uartn)
{
      switch (uartn)
      {
        case UART0:
          uart0_C2_REG(uart0)|=uart0_C2_RIE_MASK;   //����UART�����ж�
          enable_irq(uart0SE_irq_no);			 //���������ŵ�IRQ�ж�
          break;
        case UART1:
          UART_C2_REG(uart1)|=UART_C2_RIE_MASK;   //����UART�����ж�
          enable_irq(uart1SE_irq_no);			 //���������ŵ�IRQ�ж�
          break;
        case UART2:
          UART_C2_REG(uart2)|=UART_C2_RIE_MASK;   //����UART�����ж�
          enable_irq(uart2SE_irq_no);			 //���������ŵ�IRQ�ж�
          break;
        default:
          break;
      }
}

/*************************************************************************
*  �������ƣ�uart_irq_DIS
*  ����˵�����ش��ڽ����ж�
*  ����˵����UARTn       ģ��ţ�UART0~UART2��
*  �������أ���
*  �޸�ʱ�䣺2014-11-24
*  ��    ע��
*************************************************************************/
void uart_irq_DIS(UARTn uartn)
{
      switch (uartn)
      {
        case UART0:
          uart0_C2_REG(uart0)&=~uart0_C2_RIE_MASK;   //��ֹUART�����ж�
          disable_irq(uart0SE_irq_no);			  //�ؽ������ŵ�IRQ�ж�
          break;
        case UART1:
          UART_C2_REG(uart1)&=~UART_C2_RIE_MASK;   //��ֹUART�����ж�
          disable_irq(uart1SE_irq_no);			  //�ؽ������ŵ�IRQ�ж�
          break;
        case UART2:
          UART_C2_REG(uart2)&=~UART_C2_RIE_MASK;   //��ֹUART�����ж�
          disable_irq(uart2SE_irq_no);			  //�ؽ������ŵ�IRQ�ж�
          break;
        default:
          break;
      }
}
/*
************************************************************************
*  �������ƣ�uartSendCh
*  ����˵�������ڷ���һ���ֽ�
*  ����˵����UARTn       ģ���UART0,UART1,UART2
*  �������أ���
*  �޸�ʱ�䣺2012-3-20
*  ��    ע�������ͻس�ʱ���Զ�����һ������   
************************************************************************
*/

void uartSendCh (UARTn uartn, char ch)    
{
    if(ch == '\n')
    {
        uart_putchar(uartn,'\r');
    }
    uart_putchar(uartn,ch);
}

/*
************************************************************************
*  �������ƣ�uartSendString
*  ����˵�������� �����ַ���
*  ����˵����UARTn       ģ���UART0,UART1,UART2
*            buff        ���ͻ�����
*  �������أ���
*  �޸�ʱ�䣺2014-9-18
*  ��    ע��
*************************************************************************/
void uartSendString (UARTn uartn,char* buff)    
{
    while(*buff)uartSendCh(uartn,*buff++);
}
/************************************************************************
*  �������ƣ�uartRecvString
*  ����˵���������ַ���
*  ����˵����UARTn       ģ��ţ�UART0~UART3��
*  �������أ����յ����ֽ�
*  �޸�ʱ�䣺2014-11-24
*  ��    ע��
************************************************************************
*/
void uartRecvString (UARTn uartn,char * buff)
{
    char *buff2=buff;//��¼��ʼ��ַ
    char bC; 
    
    while ((bC=uart_getchar(uartn))!='\r')
    { 	          
  	if(bC=='\b')//�����˸��
        {
              if((int)buff2<(int)buff)
              {
                 uart_putchar(uartn,'\b'); 
                 uart_putchar(uartn,' '); 
                 uart_putchar(uartn,'\b'); 
                 buff--;
              }
        }
        else
        {
                *buff++=bC;
                uart_putchar(uartn,bC);
        }
    } 
    
    *buff='\0';
    uart_putchar(uartn,'\n');
}

/*
****************************************************************************
* ������: uartPrintf                                                       
* ��  ��: ��ʽ����ӡһ���ַ���                                             
* ��  ��:                                                                  
* ��  ��:                                                                 
* ˵  ��: Ĭ��ΪUART_PORT             
�ο�
****************************************************************************
*/
void uartPrintf(char *pcFmt,...)
{
        va_list ap;
        char pbString[256];

        va_start(ap,pcFmt);
        vsprintf(pbString,pcFmt,ap);
        uartSendString(UART_PORT,pbString);
        va_end(ap);
}




