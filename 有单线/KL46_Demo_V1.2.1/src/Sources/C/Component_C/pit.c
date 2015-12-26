/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#include "common.h"
#include "pit.h"
extern int Bus_Fre;
#include "vectors.h"

void pit_init_ms( uint32 MS)
{
    uint32 PIT_INTERRUPT_PERIOD=0;
    PIT_INTERRUPT_PERIOD=Bus_Fre;
    
    
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; // ʹ��PIT
    PIT_MCR  &=  !PIT_MCR_MDIS_MASK | !PIT_MCR_FRZ_MASK;   // MDIS = 0  ������ʱ��;  FRZ=1 ����ģʽ��ʱ���ر�
    
   
    enable_irq(PIT_irq_no);         //ʹ��PIT0�ж�       
    PIT_TCTRL0 =  !PIT_TCTRL_TEN_MASK | !PIT_TCTRL_TIE_MASK | !PIT_TCTRL_CHN_MASK; //�رն�ʱ��
    PIT_LDVAL0 = PIT_INTERRUPT_PERIOD*MS; // 1ms��ʱ
    PIT_TFLG0  =   PIT_TFLG_TIF_MASK; // �����־
    PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
     
    pit_irq_DIS();
}

/*
void Pit_Init_US(uint32 US)
{
    
  uint32 PIT_INTERRUPT_PERIOD=0;
    PIT_INTERRUPT_PERIOD=Bus_Fre;
   SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; // ʹ��PIT
    
     
    enable_irq(INT_PIT - 16);         //ʹ��PIT�ж�
       
    PIT_MCR  =  !PIT_MCR_MDIS_MASK | !PIT_MCR_FRZ_MASK;   // MDIS = 0  ������ʱ��;  FRZ=1 ����ģʽ��ʱ���ر�
    PIT_TCTRL1 =  !PIT_TCTRL_TEN_MASK | !PIT_TCTRL_TIE_MASK | !PIT_TCTRL_CHN_MASK; //�رն�ʱ��
    PIT_LDVAL1 = PIT_INTERRUPT_PERIOD*US/1000; // 1ms��ʱ
    PIT_TFLG1  =   PIT_TFLG_TIF_MASK; // �����־
    PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; 
   
}
*/
/*************************************************************************
*  �������ƣ�pit_irq_EN
*  ����˵����PITn��ʱ�ж�ʹ��
*  ����˵����PITn        ģ��ţ�PIT0��
*  �������أ���
*  �޸�ʱ�䣺2014-9-25
*  ��    ע��
*************************************************************************/
void pit_irq_EN(void)
{
     PIT_TCTRL0  |= PIT_TCTRL_TIE_MASK;    //ʹ�� PITn��ʱ��,����PITn�ж�  
     enable_irq(PIT_irq_no);                      //���������ŵ�IRQ�ж�
}

/*************************************************************************
*  �������ƣ�pit_irq_DIS
*  ����˵����PITn��ʱ�жϹر�
*  ����˵����PITn        ģ��ţ�PIT0��
*  �������أ���
*  �޸�ʱ�䣺2014-9-25
*  ��    ע��
*************************************************************************/
void pit_irq_DIS(void)
{
     PIT_TCTRL0 &= ~PIT_TCTRL_TIE_MASK;    //�� PITn��ʱ��, 
     disable_irq(PIT_irq_no);                      //��IRQ�ж�
}




