/*******************************************************************************
                              北京邮电大学 KL46学习例程
【Designed and Updated】BuptSmartCar 2011
【E-mail  】498339494@qq.com
【软件版本】V1.1
【最后更新】2014年11月24日
------------------------------------------------
【dev.env.】IAR 6.6
【Target  】KL46 
【 说  明 】仅做内部使用，请勿外传
【 参  考 】龙丘开发例程
【Crystal 】50.000Mhz
  
摄像头接口：

接口说明：
          拨码开关：PTA5 PTA17 PTA16 PTA14
          舵机    ：PTA13   注意舵机接线的地方红线--7V  黑线--GND  白线--A13 不能直接插上，需要调线的顺序
          电机1    ：PTC1     PTC2 
          电机2    ：PTC3     PTC4 
          串口    ：B16  B17  波特率 115200  收不到信号可以把收发反转一个
          编码器1  ：LPT模块：PTC5 
          编码器2  ：TPM模块: PTC12

          ADC口：
                  DAD0:PTE20  DAD1:PTE16 DAD2:PTE18 DAD3:PTE22，还有很多管脚可以用。参见adc.h
          
说明：1.不建议修改主频
     2.不建议修改管脚功能（修改的话可能会引起部分冲突）
     3.底层如果有问题随时发到邮箱：498339494@qq.com。我们会及时修改。
*******************************************************************************/


/*
  v1.1.3版本做了很多修改，修复了一些bug，并且更易于智能车使用

  1.为了贴近K60，gpio的所有函数都变成了小写。
  2.uart底层已经全部重写，修复UART0无法使用的问题。
  3.uart中断的使能更易于使用，与K60中断使用相同(uart_irq_EN,uart_irq_DIS)。
  4.修复舵机口PWM波频率不对的问题。
  5.修改目录结构,并规则了所有文件命名：如：KL46_ADC.h改成adc.h等。
  6.加入BUPT，同时复位时串口输出测量的内核频率与总线频率
  7.adc底层重写，修复不能采样8/10/16bit的问题
  
  除了少数模块之外，基本上大家照着K60去编程就行。
------By Hyoga
*/

      
                       
#include "includes.h"
#include "global.h"
#include "stdlib.h"

#if 0
#include "vectors.h"
//翻转LED测试 
//测试情况:成功,可以看到LED翻转
void main(void)
{
  
   KL46_LED_Init();         //LED初始化
   //pit_init_ms(1000);       //用PIT0，定时周期1ms
   //pit_irq_EN();
  // EnableInterrupts;//开所有中断
   while(1)
   {
      delayms(1000);
      KL46_LED_Turn();//翻转LED
   }
}


#elif 0
#include "vectors.h"
/******************************************
 *外部中断辅助测试 
 *说明：产生上升沿，触发外部中断; 
 *PTB3产生上升沿
 *PTB23 LED指示程序运行
 *接线说明：测试中本人用了2个板子，板子1下载测试程序，并将PTB3接到板子2的PTB2口
            板子2下载程序 “DMA读取I/O口PORTD 0--7数据”；
 *运行：2个板子共地，并上电开始运行，先将板子2重启，此时看到串口输出BUFF数组是0
        板子1重启，看到BUFF数组中包含了从PORTD0-7中的数据（悬空为高电平）。
 *******************************************/
void main(void)
{
   KL46_LED_Init();         //LED初始化
   gpio_init(PORTB,3,GPO ,0);
   
   while(1)
   {
      delayms(10);
      gpio_turn(PORTB,3);
      KL46_LED_Turn();//翻转LED
   }
}

#elif 0
/****************************************
 *外部中断测试
 *测试情况：测试成功
 *
 *警告：底层中断只开放了PORTA1,2,5,6,7,12,13,14,15
 ****************************************/
#include "vectors.h"
void main(void)
{
   DisableInterrupts;           //关总中断
   KL46_LED_Init(); 
   gpio_interrupt_init(PORTA, 15u, IO_INT_R_F_M); //io PORTAA15中断
   enable_irq(INI_PORTA_EN_MASK); //打开IO中断 
   
    uart_init (UART0,115200);//配置串口0  波特率115200
   //if()
   //{}
   EnableInterrupts;            //开总中断
   while(1)
   {
     KL46_LED_Turn();//翻转LED
     //gpio_turn(PORTB,3);
     delayms(500);
   }
}

#elif 0
#include "vectors.h"
/******************************************
 *DMA辅助测试 
 *说明：产生固定数量的上升沿，触发DMA，有多少上升沿就会有多少次DMA传输 ; 
 *PTB3产生上升沿
 *PTB23 LED指示程序运行
 *接线说明：测试中本人用了2个板子，板子1下载测试程序，并将PTB3接到板子2的PTB2口
            板子2下载程序 “DMA读取I/O口PORTD 0--7数据”；
 *运行：2个板子共地，并上电开始运行，先将板子2重启，此时看到串口输出BUFF数组是0
        板子1重启，看到BUFF数组中包含了从PORTD0-7中的数据（悬空为高电平）。
 *******************************************/
void main(void)
{
   KL46_LED_Init();         //LED初始化
   gpio_init(PORTB,3,GPO ,0);
   for(int i=0; i< 10; i++)
   {
      gpio_turn(PORTB,3);
      delayus(10);
   }
   while(1)
   {
      delayms(500);
      KL46_LED_Turn();//翻转LED
   }
}

#elif 0
//DMA读取I/O口PORTD 0--7数据
//测试完成
//效果：在串口助手会看到的数字
//串口接法如下：
/*******************************************************************************
TO 摄像头组：
这个函数 DMA_PORTx2BUFF_Init(DMA_CH0 ,BUFF, PTA2,DMA_BYTE1,20); 只要将数组（数组）
按你们自己的需求定义数组名和长度，PTA2换成你们自己的引脚，但是请注意产看自定义类
型PTxn，在该类型中的引脚才能使用。其他的参数不建议修改，特别是通道号DMA_CH0，绝不
要修改，因为底层是写死的通道0.
注意不要跟其他引脚复用
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
  uart_init (UART0,115200);//配置串口0  波特率115200  
  
  u8 x=0;
  
   while(1)
   {     
     delayms(200);
     uartPrintf("x=%d\n",BUFF[(x++)%20]);
   }
}




#elif 0
//uartPrintf测试
//成功
//效果：在串口助手会接受递增的数字
//串口接法如下：
/*******************************************************************************
核心板上的RX（B16）接蓝牙串口的TX
核心板上的TX（B17）接蓝牙串口的RX
若各项配置都正确，仍不能接收。把两根线换一下
*******************************************************************************/
#include "vectors.h"
void main(void)
{
   uart_init (UART0,115200);//配置串口0  波特率115200   
   s32 x=1;
   while(1)   
   {     
     delayms(500);
     uartPrintf("%d\n",x++);
   }
}

#elif 0
//中断法读串口【UART0】数据  测试结果：测试成功 
//效果：在串口助手中发送一个字符，串口助手会显示该字符
#include "includes.h"
#include "vectors.h"

void main(void)
{
   
   DisableInterrupts;//关掉所有中断后再开始设置
   uart_init (UART0,115200);//配置串口0  波特率115200  
   uart_irq_EN(UART0);  //中断使能  
   
   EnableInterrupts;//开所有中断
   while(1)   
   {               
   }
}

#elif 0
//GPIO测试
//串口输出电平
#include "vectors.h"
void main(void)
{
    uart_init (UART0,115200);//配置串口1  波特率115200  
    gpio_init (PORTC, 4, GPO, 0);  //初始化C4口：输出口，初始化低电平
   
   while(1)   
   { 
     delayms(1000);
     
     gpio_set (PORTC, 4, 1);   //置位C4为高电平
     u8 getGpioTmp1 = gpio_get(PORTC,4);   //获取C4引脚的值
     
     gpio_turn(PORTC,4);   //反转C4引脚的值
     u8 getGpioTmp2 = gpio_get(PORTC,4);   //获取C4引脚的值
     
     uartPrintf("%d %d \n",getGpioTmp1,getGpioTmp2);
    }
}



#elif 0
//PIT测试   测试结果：成功
//效果:串口打印 0 1 2 3
#include "vectors.h"
void main(void)
{
   
   KL46_LED_Init();         //LED初始化
   DisableInterrupts;//关掉所有中断后再开始设置
   uart_init (UART0,115200);//配置串口0  波特率115200  
   
   uartPrintf("init uart over\n");
   pit_init_ms(10);       //用PIT0，定时周期1ms
   pit_irq_EN();
   EnableInterrupts;//开所有中断
  
  while(1)
  {
    
  }
}
#elif 0
//LPT测试   测试结果：成功
//C5为输入捕捉口
//使用方法：将C4与C5口连接
//效果:测量脉冲数 约300个
#include "vectors.h"
void main(void)
{
   KL46_LED_Init();         //LED初始化
   
   uart_init (UART0,115200);//配置串口0  波特率115200  
      
   lptmr_counter_init();//LPT计数脉冲模式初始化
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
      lptmr_counter_clean();//计数器归0
   }
}
#elif 1
//电机、舵机PWM输出测试
//测试成功,A13,C1C2,C3C4均有不同占空比的方波输出

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//关掉所有中断后再开始设置
   KL46_LED_Init();         //LED初始化
   
   motor_init();
   steer_init();
   delayms(900);
   PWMSetMotor(1400);//%90
   //PWMSetMotor2(7000);//%70
   PWMSetSteer(1400);//%50*/
   
   uart_init (UART0,115200);//配置串口0  波特率115200
   uart_irq_EN(UART0);  //中断使能  
    
   EnableInterrupts;//开所有中断
   
   trueSpeed = 1310; 
   int testFlag=0;
   while(1)
   { 
     PWMSetSteer(trueSpeed);//舵机测试    //2100  顺max   700顺min
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
	 
     /*PWMSetMotor(1000);//电机测试
     delayms(3000);
     PWMSetMotor(2000);//%90
     delayms(3000);*/
   }
}
#elif 0
//TPM中的TPM2作为脉冲计数器测试
//测试方法：将PTC12与PTC4相接
//测试结果：成功

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//关掉所有中断后再开始设置
   KL46_LED_Init();         //LED初始化
   TPM_counter_init();//PTC12输入外部脉冲
   uart_init(UART0,115200);//配置串口0  波特率115200  
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
//ADC测试
//成功

#include "vectors.h"
void main(void)
{
   DisableInterrupts;//关掉所有中断后再开始设置
   KL46_LED_Init();         //LED初始化
   uart_init(UART0,115200);
   uartPrintf("start!");
  
   adc_init(DAD0);//PTE20
   EnableInterrupts;//开所有中断
  
   while(1)
   { 
     delayms(800);
     uartPrintf("%d\n",ad_once(DAD0,ADC_8bit));
   }
}

#elif 0
//程序模板
#include "vectors.h"
char temp[16];
void main(void)
{
   
   DisableInterrupts;//关掉所有中断后再开始设置
   
   KL46_LED_Init();         //LED初始化
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
 摄像头测试
 通过串口将图像传回电脑
 接线请参考camera.h
 已测试通过
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
  
  uart_init (UART0,115200);//配置串口0  波特率115200  
  enable_irq(INI_PORTA_EN_MASK); //打开A口中断 
  
  //motor_init();
  delayms(3000);
  //PWMSetMotor(1400);//%90   //1000慢悠悠
  //PWMSetMotor2(1400);//%70
  uart_irq_EN(UART0);  //中断使能 
  
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


//自主测试
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
  
  uart_init (UART0,115200);//配置串口0  波特率115200  
  enable_irq(INI_PORTA_EN_MASK); //打开A口中断 
  uart_irq_EN(UART0);  //中断使能
  
  motor_init();
  delayms(6000);
  PWMSetMotor(1000);//%90   //1000慢悠悠
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
  //串口号为4放在外，为5放在里
  
 DisableInterrupts;
  uart_init (UART0,115200);//配置串口0  波特率115200  
  uart_irq_EN(UART0);  //串口中断使能
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
  
  enable_irq(INI_PORTA_EN_MASK); //打开A口中断 
  
  pta5 = gpio_get(PORTA, 5);
  pta17 = gpio_get(PORTA, 17);
  pta16= gpio_get(PORTA,16);
  
  motor_init();
  steer_init();
  PWMSetSteer(1400)   
  delayms(3000);
  if(pta5==0&&pta17==0)
  {
    //PWMSetMotor(1200);//%90   //1000慢悠悠 
    //PWMSetMotor2(1200);
  }
  else if(pta5==1&&pta17==0)
  {
    //PWMSetMotor(1400);//%90   //1000慢悠悠 
    //PWMSetMotor2(1400);
  }
  else if(pta5==0&&pta17==1)
  {
    //PWMSetMotor(2000);//%90   //1000慢悠悠 
    //PWMSetMotor2(2000);
  }
  else 
  {
    //PWMSetMotor(2500);//%90   //1000慢悠悠 
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
  //串口号为4放在外，为5放在里
  
 DisableInterrupts;
  uart_init (UART0,115200);//配置串口0  波特率115200  
  uart_irq_EN(UART0);  //串口中断使能
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
  
  enable_irq(INI_PORTA_EN_MASK); //打开A口中断 
  
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
    //PWMSetMotor(1200);//%90   //1000慢悠悠 
    //PWMSetMotor2(1200);
  }
  else if(pta5==1&&pta17==0)
  {
    //PWMSetMotor(1400);//%90   //1000慢悠悠 
    //PWMSetMotor2(1400);
  }
  else if(pta5==0&&pta17==1)
  {
    //PWMSetMotor(2000);//%90   //1000慢悠悠 
    //PWMSetMotor2(2000);
  }
  else 
  {
    //PWMSetMotor(2500);//%90   //1000慢悠悠 
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

