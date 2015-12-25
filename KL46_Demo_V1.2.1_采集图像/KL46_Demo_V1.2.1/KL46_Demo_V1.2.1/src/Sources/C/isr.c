/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/

#include "includes.h"
#include "isr.h"

/**********************************************************************************************
��ʱ��0 �Ͷ�ʱ��1����һ���ж����������ǼĴ������Ǹ��Եġ���������·ͬʱ����ʱ����Ҫ�ж���������һ
����ʱ���������ж�
********************************************************************************************/
#define PIT_COUNT_TIME  25*1000
void PIT0_IRQHandler(void)
{ 
  PIT_Flag_Clear(PIT0);   //����жϱ�־λ
  
  static u8 PITcounter = 0;
  PITcounter++;
  if(PITcounter==4)
    PITcounter = 0;
  uartPrintf("%d\n",PITcounter);
  
    KL46_LED_Turn();
  //����ʱ��Ƭ��ѯ
  switch(PITcounter)
  {
    case 0:
      //�ɼ�ͼ��
      break;
          
    case 1:
      //ͼ���� ע��ͼ���ع���Ҫһ��ʱ�䣬��������case�ٶ��PIT��ʱ���ں��ٲɼ�
      break;   
    case 2:
      //
      break;
    case 3: //���ٲ����е����������
     /* g_nSpeedControlCount ++;//����
      if(g_nSpeedControlCount >= SPEED_CONTROL_COUNT)//10ms����1��
      {
        trueSpeed = lptmr_counter_value();
        lptmr_counter_clean();
        have_new_speed=1;
        g_nSpeedControlCount = 0; 	
        //˫�����Ҫ����1��TPM_counter
      }
      //�ٶȿ����㷨
      if(have_new_speed==1)//��������ٶȲŽ��е������PID
      {
        motorCtrl();
        have_new_speed=0;
      }
      steerCtrl();//���ж������
      */
 
      break;
          
    default:
      	  assert(0,"״̬����\n");
  }
}


void UART0_IRQHandler(void)
{
  DisableInterrupts;
  
  char ch;
  //����һ���ֽ����ݲ��ط�
  ch=uart_getchar(UART0);
 
  uart_putchar (UART0, ch); 
  
  EnableInterrupts;  
}


/*PORTA �жϷ����� 
  ע�⣺PA0,PA3,PA4,PA20������ϵͳ�ܽţ�����ʹ�ã�
  ע�⣺DMA�����ܽŲ�������ⲿ�жϷ�����
  */
void PORTA_IRQHandler(void){
  
  //PA1 �ж�  
  if((PORTA_ISFR&PORTx1_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA1 Interrupt");
    PORTA_ISFR |= PORTx1_ISFR_MASK;//ͨ��д��1���������PA1 �жϱ�־
  }
  //PA5 �ж� 
  else if((PORTA_ISFR&PORTx5_ISFR_MASK)!=0)
  {
    uartPrintf("b");
    PORTA_ISFR |= PORTx5_ISFR_MASK;//ͨ��д��1���������PA2 �жϱ�־
  }
  
  //PA6 �ж�      
  else if((PORTA_ISFR&PORTx6_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA6 Interrupt");
    PORTA_ISFR |= PORTx6_ISFR_MASK;//ͨ��д��1���������PA2 �жϱ�־
  }
  
  //PA7 �ж�      
  else if((PORTA_ISFR&PORTx7_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA7 Interrupt");
    PORTA_ISFR |= PORTx7_ISFR_MASK;//ͨ��д��1���������PA2 �жϱ�־
  }
  //PA12 �ж� 
  else if((PORTA_ISFR&PORTx12_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA12 Interrupt");
    PORTA_ISFR |= PORTx12_ISFR_MASK;//ͨ��д��1���������PA12 �жϱ�־
  }
  
  //PA13 �ж�      
  else if((PORTA_ISFR&PORTx13_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA13 Interrupt");
    PORTA_ISFR |= PORTx13_ISFR_MASK;//ͨ��д��1���������PA13 �жϱ�־
  }
  
  //PA14 �ж�              //��Ϊ���ж�
  else if((PORTA_ISFR&PORTx14_ISFR_MASK)!=0)
  {
    PORTA_ISFR |= PORTx14_ISFR_MASK;//ͨ��д��1���������PA14 �жϱ�־
    temp_counter = 0;
    temp_row = 0;
    en_href_interrupt();//�����ж�
  }
  
  //PA15 �ж�               //��Ϊ���ж�
  else if((PORTA_ISFR&PORTx15_ISFR_MASK)!=0)
  {
    PORTA_ISFR |= PORTx15_ISFR_MASK;//ͨ��д��1���������PA15 �жϱ�־
    //��ʼ�µ�DMA
    new_dma(PicBuffer+temp_row);
    //�������
    temp_counter++;
    if(temp_counter%2==0)
      temp_row++;
    //��ʶ�ɼ�һ��ͼ�����
    if (temp_row == ROW)
    {
      complete_flag = 1;
      dis_href_interrupt();
      dis_vsyn_interrupt();
    }
  }
    //�ر����ж�
  //�����ж���������� 
  else
  {
      uartPrintf("����PORTA�ж��������� else-if ���");
  }
}
