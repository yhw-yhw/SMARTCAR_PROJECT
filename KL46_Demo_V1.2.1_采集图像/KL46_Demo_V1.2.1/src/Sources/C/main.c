/*******************************************************************************
                              �����ʵ��ѧ KL46ѧϰ����
��Designed and Updated��BuptSmartCar 2011
��E-mail  ��498339494@qq.com
������汾��V1.1
�������¡�2014��11��24��
------------------------------------------------
��dev.env.��IAR 6.6
��Target  ��KL46 
�� ˵  �� �������ڲ�ʹ�ã������⴫
�� ��  �� �����𿪷�����
��Crystal ��50.000Mhz
  
����ͷ�ӿڣ�

�ӿ�˵����
          ���뿪�أ�PTA5 PTA17 PTA16 PTA14
          ���    ��PTA13   ע�������ߵĵط�����--7V  ����--GND  ����--A13 ����ֱ�Ӳ��ϣ���Ҫ���ߵ�˳��
          ���1    ��PTC1     PTC2 
          ���2    ��PTC3     PTC4 
          ����    ��B16  B17  ������ 115200  �ղ����źſ��԰��շ���תһ��
          ������1  ��LPTģ�飺PTC5 
          ������2  ��TPMģ��: PTC12

          ADC�ڣ�
                  DAD0:PTE20  DAD1:PTE16 DAD2:PTE18 DAD3:PTE22�����кܶ�ܽſ����á��μ�adc.h
          
˵����1.�������޸���Ƶ
     2.�������޸ĹܽŹ��ܣ��޸ĵĻ����ܻ����𲿷ֳ�ͻ��
     3.�ײ������������ʱ�������䣺498339494@qq.com�����ǻἰʱ�޸ġ�
*******************************************************************************/


/*
  v1.1.3�汾���˺ܶ��޸ģ��޸���һЩbug�����Ҹ��������ܳ�ʹ��

  1.Ϊ������K60��gpio�����к����������Сд��
  2.uart�ײ��Ѿ�ȫ����д���޸�UART0�޷�ʹ�õ����⡣
  3.uart�жϵ�ʹ�ܸ�����ʹ�ã���K60�ж�ʹ����ͬ(uart_irq_EN,uart_irq_DIS)��
  4.�޸������PWM��Ƶ�ʲ��Ե����⡣
  5.�޸�Ŀ¼�ṹ,�������������ļ��������磺KL46_ADC.h�ĳ�adc.h�ȡ�
  6.����BUPT��ͬʱ��λʱ��������������ں�Ƶ��������Ƶ��
  7.adc�ײ���д���޸����ܲ���8/10/16bit������
  
  ��������ģ��֮�⣬�����ϴ������K60ȥ��̾��С�
------By Hyoga
*/

      
                       
#include "includes.h"
#include "global.h"
#include "stdlib.h"

#if 0
#include "vectors.h"
//��תLED���� 
//�������:�ɹ�,���Կ���LED��ת
void main(void)
{
  
   KL46_LED_Init();         //LED��ʼ��
   //pit_init_ms(1000);       //��PIT0����ʱ����1ms
   //pit_irq_EN();
  // EnableInterrupts;//�������ж�
   while(1)
   {
      delayms(1000);
      KL46_LED_Turn();//��תLED
   }
}


#elif 0
#include "vectors.h"
/******************************************
 *�ⲿ�жϸ������� 
 *˵�������������أ������ⲿ�ж�; 
 *PTB3����������
 *PTB23 LEDָʾ��������
 *����˵���������б�������2�����ӣ�����1���ز��Գ��򣬲���PTB3�ӵ�����2��PTB2��
            ����2���س��� ��DMA��ȡI/O��PORTD 0--7���ݡ���
 *���У�2�����ӹ��أ����ϵ翪ʼ���У��Ƚ�����2��������ʱ�����������BUFF������0
        ����1����������BUFF�����а����˴�PORTD0-7�е����ݣ�����Ϊ�ߵ�ƽ����
 *******************************************/
void main(void)
{
   KL46_LED_Init();         //LED��ʼ��
   gpio_init(PORTB,3,GPO ,0);
   
   while(1)
   {
      delayms(10);
      gpio_turn(PORTB,3);
      KL46_LED_Turn();//��תLED
   }
}

#elif 0
/****************************************
 *�ⲿ�жϲ���
 *������������Գɹ�
 *
 *���棺�ײ��ж�ֻ������PORTA1,2,5,6,7,12,13,14,15
 ****************************************/
#include "vectors.h"
void main(void)
{
   DisableInterrupts;           //�����ж�
   KL46_LED_Init(); 
   gpio_interrupt_init(PORTA, 15u, IO_INT_R_F_M); //io PORTAA15�ж�
   enable_irq(INI_PORTA_EN_MASK); //��IO�ж� 
   
    uart_init (UART0,115200);//���ô���0  ������115200
   //if()
   //{}
   EnableInterrupts;            //�����ж�
   while(1)
   {
     KL46_LED_Turn();//��תLED
     //gpio_turn(PORTB,3);
     delayms(500);
   }
}

#elif 0
#include "vectors.h"
/******************************************
 *DMA�������� 
 *˵���������̶������������أ�����DMA���ж��������ؾͻ��ж��ٴ�DMA���� ; 
 *PTB3����������
 *PTB23 LEDָʾ��������
 *����˵���������б�������2�����ӣ�����1���ز��Գ��򣬲���PTB3�ӵ�����2��PTB2��
            ����2���س��� ��DMA��ȡI/O��PORTD 0--7���ݡ���
 *���У�2�����ӹ��أ����ϵ翪ʼ���У��Ƚ�����2��������ʱ�����������BUFF������0
        ����1����������BUFF�����а����˴�PORTD0-7�е����ݣ�����Ϊ�ߵ�ƽ����
 *******************************************/
void main(void)
{
   KL46_LED_Init();         //LED��ʼ��
   gpio_init(PORTB,3,GPO ,0);
   for(int i=0; i< 10; i++)
   {
      gpio_turn(PORTB,3);
      delayus(10);
   }
   while(1)
   {
      delayms(500);
      KL46_LED_Turn();//��תLED
   }
}

#elif 0
//DMA��ȡI/O��PORTD 0--7����
//�������
//Ч�����ڴ������ֻῴ��������
//���ڽӷ����£�
/*******************************************************************************
TO ����ͷ�飺
������� DMA_PORTx2BUFF_Init(DMA_CH0 ,BUFF, PTA2,DMA_BYTE1,20); ֻҪ�����飨���飩
�������Լ����������������ͳ��ȣ�PTA2���������Լ������ţ�������ע������Զ�����
��PTxn���ڸ������е����Ų���ʹ�á������Ĳ����������޸ģ��ر���ͨ����DMA_CH0������
Ҫ�޸ģ���Ϊ�ײ���д����ͨ��0.
ע�ⲻҪ���������Ÿ���
*******************************************************************************/
#include "vectors.h"


void main(void)
{ 
  u8 BUFF[20];
  gpio_init(PORTD,0,GPI ,0);
  gpio_init(PORTD,1,GPI ,0);
  gpio_init(PORTD,2,GPI ,0);
  gpio_init(PORTD,3,GPI ,0);
  gpio_init(PORTD,4,GPI ,0);
  gpio_init(PORTD,5,GPI ,0);
  gpio_init(PORTD,6,GPI ,0);
  gpio_init(PORTD,7,GPI ,0);
  for(int i=0 ; i<19; i++){
    BUFF[i]=0;
  }
  BUFF[19]=1;
  DMA_PORTx2BUFF_Init(DMA_CH0 ,(uint32)&GPIOD_PDIR,BUFF, PTA2,DMA_BYTE1,20, DMA_REQ_M3);
  uart_init (UART0,115200);//���ô���0  ������115200  
  
  u8 x=0;
  
   while(1)
   {     
     delayms(200);
     uartPrintf("x=%d\n",BUFF[(x++)%20]);
   }
}




#elif 0
//uartPrintf����
//�ɹ�
//Ч�����ڴ������ֻ���ܵ���������
//���ڽӷ����£�
/*******************************************************************************
���İ��ϵ�RX��B16�����������ڵ�TX
���İ��ϵ�TX��B17�����������ڵ�RX
���������ö���ȷ���Բ��ܽ��ա��������߻�һ��
*******************************************************************************/
#include "vectors.h"
void main(void)
{
   uart_init (UART0,115200);//���ô���0  ������115200   
   s32 x=1;
   while(1)   
   {     
     delayms(500);
     uartPrintf("%d\n",x++);
   }
}

#elif 0
//�жϷ������ڡ�UART0������  ���Խ�������Գɹ� 
//Ч�����ڴ��������з���һ���ַ����������ֻ���ʾ���ַ�
#include "includes.h"
#include "vectors.h"

void main(void)
{
   
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   uart_init (UART0,115200);//���ô���0  ������115200  
   uart_irq_EN(UART0);  //�ж�ʹ��  
   
   EnableInterrupts;//�������ж�
   while(1)   
   {               
   }
}

#elif 0
//GPIO����
//���������ƽ
#include "vectors.h"
void main(void)
{
    uart_init (UART0,115200);//���ô���1  ������115200  
    gpio_init (PORTC, 4, GPO, 0);  //��ʼ��C4�ڣ�����ڣ���ʼ���͵�ƽ
   
   while(1)   
   { 
     delayms(1000);
     
     gpio_set (PORTC, 4, 1);   //��λC4Ϊ�ߵ�ƽ
     u8 getGpioTmp1 = gpio_get(PORTC,4);   //��ȡC4���ŵ�ֵ
     
     gpio_turn(PORTC,4);   //��תC4���ŵ�ֵ
     u8 getGpioTmp2 = gpio_get(PORTC,4);   //��ȡC4���ŵ�ֵ
     
     uartPrintf("%d %d \n",getGpioTmp1,getGpioTmp2);
    }
}



#elif 0
//PIT����   ���Խ�����ɹ�
//Ч��:���ڴ�ӡ 0 1 2 3
#include "vectors.h"
void main(void)
{
   
   KL46_LED_Init();         //LED��ʼ��
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   uart_init (UART0,115200);//���ô���0  ������115200  
   
   uartPrintf("init uart over\n");
   pit_init_ms(10);       //��PIT0����ʱ����1ms
   pit_irq_EN();
   EnableInterrupts;//�������ж�
  
  while(1)
  {
    
  }
}
#elif 0
//LPT����   ���Խ�����ɹ�
//C5Ϊ���벶׽��
//ʹ�÷�������C4��C5������
//Ч��:���������� Լ300��
#include "vectors.h"
void main(void)
{
   KL46_LED_Init();         //LED��ʼ��
   
   uart_init (UART0,115200);//���ô���0  ������115200  
      
   lptmr_counter_init();//LPT��������ģʽ��ʼ��
   gpio_init(PORTC, 4,GPO, 0); 
   gpio_set (PORTC, 4, 1); 
 
   while(1)
   { 
      for(int i=1;i<=600;i++)
      {
        for(int j=1;j<=5000;j++){};
        gpio_turn(PORTC, 4);
      }
      int x=lptmr_counter_value();
      uartPrintf("%d\n",x);
      lptmr_counter_clean();//��������0
   }
}
#elif 1
//��������PWM�������
//���Գɹ�,A13,C1C2,C3C4���в�ͬռ�ձȵķ������

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   KL46_LED_Init();         //LED��ʼ��
   
   motor_init();
   steer_init();
   delayms(900);
   PWMSetMotor(1400);//%90
   //PWMSetMotor2(7000);//%70
   PWMSetSteer(1400);//%50*/
   
   uart_init (UART0,115200);//���ô���0  ������115200
   uart_irq_EN(UART0);  //�ж�ʹ��  
    
   EnableInterrupts;//�������ж�
   
   trueSpeed = 1310; 
   int testFlag=0;
   while(1)
   { 
     PWMSetSteer(trueSpeed);//�������    //2100  ˳max   700˳min
     //uartPrintf("%d\n",trueSpeed);
     delayms(100);
	 /*
	 if(trueSpeed==1600)
	 	testFlag=1;
	 if(trueSpeed==1140)
	   	testFlag=0;
	 
	 if(testFlag==0)
	   	trueSpeed+=10;
	 else
	   	trueSpeed-=10; 
	 */
	 
     /*PWMSetMotor(1000);//�������
     delayms(3000);
     PWMSetMotor(2000);//%90
     delayms(3000);*/
   }
}
#elif 0
//TPM�е�TPM2��Ϊ�������������
//���Է�������PTC12��PTC4���
//���Խ�����ɹ�

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   KL46_LED_Init();         //LED��ʼ��
   TPM_counter_init();//PTC12�����ⲿ����
   uart_init(UART0,115200);//���ô���0  ������115200  
   gpio_init(PORTC, 4,GPO, 0);
   delayms(900);
   while(1)
   { 
     for(int i=1;i<=800;i++)
     {
        for(int j=1;j<=5000;j++){};
        gpio_turn(PORTC, 4);
     }
     uartPrintf("%d\n", TPM_counter_value());
     TPM_counter_clean();
   }
}

#elif 0
//ADC����
//�ɹ�

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   KL46_LED_Init();         //LED��ʼ��
   uart_init(UART0,115200);
   uartPrintf("start!");
  
   adc_init(DAD0);//PTE20
   EnableInterrupts;//�������ж�
  
   while(1)
   { 
     delayms(800);
     uartPrintf("%d\n",ad_once(DAD0,ADC_8bit));
   }
}

#elif 0
//����ģ��
#include "vectors.h"
char temp[16];
void main(void)
{
   
   DisableInterrupts;//�ص������жϺ��ٿ�ʼ����
   
   KL46_LED_Init();         //LED��ʼ��
   delayms(67);
   
   uart_init(UART0,115200);
 //  uartPrintf("sdfgdsfgsdg\n");
   
 //  lptmr_counter_init();
   
   //TPM_counter_init();
   
   //motor_init();
  /// steer_init();/////
   CCD_init();

   int cnt=0;
   DisableInterrupts;
   while(1)
   { 
     
    /*StartIntegration_Front();
    delayms(5);
    ImageCapture_Front(Pixel);
    
     
    SendImageData(Pixel);
    delayms(20);*/
   }
}



/*
 ����ͷ����
 ͨ�����ڽ�ͼ�񴫻ص���
 ������ο�camera.h
 �Ѳ���ͨ��
*/
#elif 0
#include "includes.h"
#include "camera.h"
void main()
{
  gpio_init(PORTD,0,GPI ,0);
  gpio_init(PORTD,1,GPI ,0);
  gpio_init(PORTD,2,GPI ,0);
  gpio_init(PORTD,3,GPI ,0);
  gpio_init(PORTD,4,GPI ,0);
  gpio_init(PORTD,5,GPI ,0);
  gpio_init(PORTD,6,GPI ,0);
  gpio_init(PORTD,7,GPI ,0);
  
  uart_init (UART0,115200);//���ô���0  ������115200  
  enable_irq(INI_PORTA_EN_MASK); //��A���ж� 
  
  //motor_init();
  delayms(3000);
  //PWMSetMotor(1400);//%90   //1000������
  //PWMSetMotor2(1400);//%70
  uart_irq_EN(UART0);  //�ж�ʹ�� 
  
  EnableInterrupts;
  camera_init();
  
  while(1)
  {
    get_photo();
    //show_photo();
    //uartPrintf("complete!\n");
	VSCN();
  }
}


//��������
#elif 0
#include "includes.h"
void main()
{
  DisableInterrupts; 
  
  gpio_init(PORTD,0,GPI ,0);
  gpio_init(PORTD,1,GPI ,0);
  gpio_init(PORTD,2,GPI ,0);
  gpio_init(PORTD,3,GPI ,0);
  gpio_init(PORTD,4,GPI ,0);
  gpio_init(PORTD,5,GPI ,0);
  gpio_init(PORTD,6,GPI ,0);
  gpio_init(PORTD,7,GPI ,0);
  
  uart_init (UART0,115200);//���ô���0  ������115200  
  enable_irq(INI_PORTA_EN_MASK); //��A���ж� 
  uart_irq_EN(UART0);  //�ж�ʹ��
  
  motor_init();
  delayms(6000);
  PWMSetMotor(1000);//%90   //1000������
  PWMSetMotor2(1000);//%70
  //pit_init_ms(10);
  //pit_irq_EN();
  
  EnableInterrupts;
  camera_init();
  
  //steer_init();
  //TPM_counter_init();
  //PWMSetSteer(1400);//%20*
  while(1)
  {
    get_photo();
    show_photo();
    uartPrintf("complete!\n");
  }
}

#elif 0
#include "includes.h"
#include "vectors.h"

void main()
{
  u8 pta5, pta17, pta16;
  //���ں�Ϊ4�����⣬Ϊ5������
  
 DisableInterrupts;
  uart_init (UART0,115200);//���ô���0  ������115200  
  uart_irq_EN(UART0);  //�����ж�ʹ��
  //DisableInterrupts;


  gpio_init(PORTA,5,GPI ,0);
  gpio_init(PORTA,17,GPI ,0);
  gpio_init(PORTA,16,GPI ,0);
  gpio_init(PORTD,0,GPI ,0);
  gpio_init(PORTD,1,GPI ,0);
  gpio_init(PORTD,2,GPI ,0);
  gpio_init(PORTD,3,GPI ,0);
  gpio_init(PORTD,4,GPI ,0);
  gpio_init(PORTD,5,GPI ,0);
  gpio_init(PORTD,6,GPI ,0);
  gpio_init(PORTD,7,GPI ,0);
  
  enable_irq(INI_PORTA_EN_MASK); //��A���ж� 
  
  pta5 = gpio_get(PORTA, 5);
  pta17 = gpio_get(PORTA, 17);
  pta16= gpio_get(PORTA,16);
  
  motor_init();
  steer_init();
  PWMSetSteer(1400)   
  delayms(3000);
  if(pta5==0&&pta17==0)
  {
    //PWMSetMotor(1200);//%90   //1000������ 
    //PWMSetMotor2(1200);
  }
  else if(pta5==1&&pta17==0)
  {
    //PWMSetMotor(1400);//%90   //1000������ 
    //PWMSetMotor2(1400);
  }
  else if(pta5==0&&pta17==1)
  {
    //PWMSetMotor(2000);//%90   //1000������ 
    //PWMSetMotor2(2000);
  }
  else 
  {
    //PWMSetMotor(2500);//%90   //1000������ 
    //PWMSetMotor2(2500);
  }
  
   
  
  //pidSteerIni();
  
  EnableInterrupts;
  
  camera_init(); 
  while(1)
  {
    get_photo();
    GetBlackLine();
    steerCtrl();
    //show_photo();
    //uartPrintf("complete!\n");
  }
}

#elif 0
#include "includes.h"
#include "vectors.h"
extern int flag;
void main()
{
  u8 pta5, pta17, pta16;
  //���ں�Ϊ4�����⣬Ϊ5������
  
 DisableInterrupts;
  uart_init (UART0,115200);//���ô���0  ������115200  
  uart_irq_EN(UART0);  //�����ж�ʹ��
  //DisableInterrupts;


  gpio_init(PORTA,5,GPI ,0);
  gpio_init(PORTA,17,GPI ,0);
  gpio_init(PORTA,16,GPI ,0);
  gpio_init(PORTD,0,GPI ,0);
  gpio_init(PORTD,1,GPI ,0);
  gpio_init(PORTD,2,GPI ,0);
  gpio_init(PORTD,3,GPI ,0);
  gpio_init(PORTD,4,GPI ,0);
  gpio_init(PORTD,5,GPI ,0);
  gpio_init(PORTD,6,GPI ,0);
  gpio_init(PORTD,7,GPI ,0);
  
  enable_irq(INI_PORTA_EN_MASK); //��A���ж� 
  
  pta5 = gpio_get(PORTA, 5);
  pta17 = gpio_get(PORTA, 17);
  pta16= gpio_get(PORTA,16);
  
  motor_init();
  steer_init();
  PWMSetSteer(1400);   
  delayms(3000);
  PWMSetSteer(700);   
  delayms(3000);
  PWMSetSteer(2100);   
  delayms(3000);
  if(pta5==0&&pta17==0)
  {
    //PWMSetMotor(1200);//%90   //1000������ 
    //PWMSetMotor2(1200);
  }
  else if(pta5==1&&pta17==0)
  {
    //PWMSetMotor(1400);//%90   //1000������ 
    //PWMSetMotor2(1400);
  }
  else if(pta5==0&&pta17==1)
  {
    //PWMSetMotor(2000);//%90   //1000������ 
    //PWMSetMotor2(2000);
  }
  else 
  {
    //PWMSetMotor(2500);//%90   //1000������ 
    //PWMSetMotor2(2500);
  }
  
   
  
  //pidSteerIni();
  
  EnableInterrupts;
  
  camera_init(); 
  while(1)
  {
    if(flag==1)
    {
      get_photo();
      GetBlackLine();
      steerCtrl();
      //show_photo();
      //uartPrintf("complete!\n");
    }
    else
    {
      get_photo();
      show_photo();
      uartPrintf("complete!\n");
    }
  }
}
#endif

