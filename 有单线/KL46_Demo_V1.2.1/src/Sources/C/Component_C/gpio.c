/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#include "gpio.h"     //����gpioͷ�ļ�
#include "assert.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; //�������ָ�����鱣�� GPIOx �ĵ�ַ
volatile struct PORT_MemMap *PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};

/*
************************************************************************
*  �������ƣ�gpio_init
*  ����˵������ʼ��gpio
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            IO          ���ŷ���,0=����,1=���
*            data        �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ ����������Ч��
*  �������أ���
*  �޸�ʱ�䣺2012-3-15 
*  ��    ע��
************************************************************************
*************************************************************************/
void gpio_init (PORTx portx, u8 n, GPIO_CFG cfg, u8 data)
{
    assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) )
           ,"GPIO�˿ڳ�ʼ������");
   
    ASSERT( (n < 32u)  && (data < 2u) );           //���Լ��˿ں������Ƿ������ƽ�Ƿ����

    //ѡ���ܽ� PORTx_PCRx ��ÿ���˿ڶ��и��Ĵ��� PORTx_PCRx
    PORT_PCR_REG(PORTX[portx], n) = (0 | PORT_PCR_MUX(1) | cfg);

    //�˿ڷ���������뻹�����
    if( ( (cfg & 0x01) == GPI) || (cfg == GPI_UP) ||     (cfg == GPI_UP_PF)      )
        //   ���λΪ0������   ||   ��������ģʽ  ||   ��������������Դ�˲���
      {
           GPIO_PDDR_REG(GPIOx[portx]) &= ~(1 << n);  //���ö˿ڷ���Ϊ����
      }
    else
     {
            GPIO_PDDR_REG(GPIOx[portx]) |= (1 << n);    //���ö˿ڷ���Ϊ���
        if(data == 1)//output
        {
            GPIO_SET(portx, n, 1);                  //�Զ˿�������ƣ����Ϊ1
        }
        else
        {
            GPIO_SET(portx, n, 0);                  //�Զ˿�������ƣ����Ϊ0
        }
    }
}


/*************************************************************************
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            data        �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ
*  �������أ���
*  �޸�ʱ�䣺2012-1-16   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_set (PORTx portx, u8 n, u8 data)
{
    ASSERT( (n < 32u)  && (data < 2u) );           //���Լ��˿ں������Ƿ������ƽ�Ƿ����
   if(data == 1)               
        GPIO_SET(portx, n, 1);  
    else
        GPIO_SET(portx, n, 0);  

}

/*************************************************************************
*  �������ƣ�gpio_turn
*  ����˵������ת����״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void gpio_turn (PORTx portx, u8 n)
{
    ASSERT( n < 32u );           //ʹ�ö��Լ�����ź�
    GPIO_TURN(portx, n);
}



/*************************************************************************
*  �������ƣ�gpio_get
*  ����˵������ȡ��������״̬
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��
*************************************************************************/
u8 gpio_get(PORTx portx,u8 n)           //��ȡ����״̬
{
    ASSERT( n < 32u );                  //ʹ�ö��Լ�����ź�
    return GPIO_GET(portx,n);
}


//added by ���� start

/*************************************************************************
*  �������ƣ�gpio_interrupt_init
*  ����˵����IO�жϳ�ʼ��
*  ����˵����PORTx              �˿ںţ�ֻ��ѡPORTA��
*            n                  �˿����źţ�1,2,5,6,7,12,13,14,15��
             IO_INT_MODEn       �жϴ�����ʽ
*  �������أ���
*  �޸�ʱ�䣺2012-1-15   �Ѳ���
*  ��    ע��ֻ������PORTA �ж�
*************************************************************************/
void gpio_interrupt_init(PORTx portx, u8 n, IO_INT_MODEn mode)
{
  assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) || (portx==PORTD) )
           ,"GPIO�˿ڳ�ʼ������");
  
  switch(portx){
  case PORTA :
    switch(n){
    case 1:
       /* ����PA1�ܽ�ΪGPIO����*/
      PORTA_PCR1 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA1Ϊ�����ش��� */
      PORTA_PCR1 |= PORT_PCR_IRQC(mode); 
    break;
    case 2:
      /* ����PA2�ܽ�ΪGPIO����*/
      PORTA_PCR2 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA2Ϊ�����ش��� */
      PORTA_PCR2 |= PORT_PCR_IRQC(mode); 
    break;
    case 5:
       /* ����PA5�ܽ�ΪGPIO����*/
      PORTA_PCR5 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA5Ϊ�����ش��� */
      PORTA_PCR5 |= PORT_PCR_IRQC(mode); 
    break;
    case 6:
       /* ����PA6�ܽ�ΪGPIO����*/
      PORTA_PCR6 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA6Ϊ�����ش��� */
      PORTA_PCR6 |= PORT_PCR_IRQC(mode); 
    break;
    case 7:
       /* ����PA7�ܽ�ΪGPIO����*/
      PORTA_PCR7 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA7Ϊ�����ش��� */
      PORTA_PCR7 |= PORT_PCR_IRQC(mode); 
    break;
    case 12:
       /* ����PA12�ܽ�ΪGPIO����*/
      PORTA_PCR12 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA12Ϊ�����ش��� */
      PORTA_PCR12 |= PORT_PCR_IRQC(mode); 
    break;
    case 13:
       /* ����PA13�ܽ�ΪGPIO����*/
      PORTA_PCR13 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA13Ϊ�����ش��� */
      PORTA_PCR13 |= PORT_PCR_IRQC(mode); 
    break;
    case 14:
       /* ����PA14�ܽ�ΪGPIO����*/
      PORTA_PCR14 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA14Ϊ�����ش��� */
      PORTA_PCR14 |= PORT_PCR_IRQC(mode); 
    break;
    case 15:
       /* ����PA15�ܽ�ΪGPIO����*/
      PORTA_PCR15 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* ����PA15Ϊ�����ش��� */
      PORTA_PCR15 |= PORT_PCR_IRQC(mode); 
    break;
    default :break;
    }
    break;
    
  case PORTD :
    break;
    
  default :break;
  }
 
}
/************************************************
 *ֻ��ʹ��PORTA 1,2,5,6,7,12,13,14,15
 *
 ************************************************/
void gpio_interrupt_dma_dis(PORTx portx, u8 n)
{
    assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) || (portx==PORTD) )
           ,"GPIO�˿ڳ�ʼ������");
  
    switch(portx){
  case PORTA :
    switch(n){
    case 1:
       PORTA_PCR1 &=INI_PORTx_DIS; 
    break;
    case 2:
       PORTA_PCR2 &=INI_PORTx_DIS;
    break;
    case 5:
      PORTA_PCR5 &=INI_PORTx_DIS; 
    break;
    case 6:
      PORTA_PCR6 &=INI_PORTx_DIS; 
    break;
    case 7:
      PORTA_PCR7 &=INI_PORTx_DIS; 
    break;
    case 12:
      PORTA_PCR12 &=INI_PORTx_DIS; 
    break;
    case 13:
      PORTA_PCR13 &=INI_PORTx_DIS; 
    break;
    case 14:
     PORTA_PCR14 &=INI_PORTx_DIS;  
    break;
    case 15:
      PORTA_PCR15 &=INI_PORTx_DIS; 
    break;
    default :break;
    }
    break;
    
  case PORTD :
    //uartPrintf("PORTD �Ѿ���������ͷ���ݲɼ�");
    break;
    
  default :break;
  }
}

// added end