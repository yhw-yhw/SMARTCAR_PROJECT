/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/

#include "includes.h"
#include "isr.h"

/**********************************************************************************************
定时器0 和定时器1共用一个中断向量，但是寄存器都是各自的。因此如果两路同时开启时，需要判定到底是哪一
个定时器产生了中断
********************************************************************************************/
#define PIT_COUNT_TIME  25*1000
void PIT0_IRQHandler(void)
{ 
  PIT_Flag_Clear(PIT0);   //清除中断标志位
  
  static u8 PITcounter = 0;
  PITcounter++;
  if(PITcounter==4)
    PITcounter = 0;
  uartPrintf("%d\n",PITcounter);
  
    KL46_LED_Turn();
  //进行时间片轮询
  switch(PITcounter)
  {
    case 0:
      //采集图像
      break;
          
    case 1:
      //图像处理 注：图像曝光需要一定时间，可以增加case再多个PIT定时周期后再采集
      break;   
    case 2:
      //
      break;
    case 3: //测速并进行电机与舵机控制
     /* g_nSpeedControlCount ++;//测速
      if(g_nSpeedControlCount >= SPEED_CONTROL_COUNT)//10ms控速1次
      {
        trueSpeed = lptmr_counter_value();
        lptmr_counter_clean();
        have_new_speed=1;
        g_nSpeedControlCount = 0; 	
        //双电机还要再用1个TPM_counter
      }
      //速度控制算法
      if(have_new_speed==1)//测出了新速度才进行电机控制PID
      {
        motorCtrl();
        have_new_speed=0;
      }
      steerCtrl();//进行舵机控制
      */
 
      break;
          
    default:
      	  assert(0,"状态错误\n");
  }
}


void UART0_IRQHandler(void)
{
  DisableInterrupts;
  
  char ch;
  //接收一个字节数据并回发
  ch=uart_getchar(UART0);
 
  uart_putchar (UART0, ch); 
  
  EnableInterrupts;  
}


/*PORTA 中断服务函数 
  注意：PA0,PA3,PA4,PA20已用作系统管脚，不能使用，
  注意：DMA触发管脚不能添加外部中断服务函数
  */
void PORTA_IRQHandler(void){
  
  //PA1 中断  
  if((PORTA_ISFR&PORTx1_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA1 Interrupt");
    PORTA_ISFR |= PORTx1_ISFR_MASK;//通过写“1”操作清除PA1 中断标志
  }
  //PA5 中断 
  else if((PORTA_ISFR&PORTx5_ISFR_MASK)!=0)
  {
    uartPrintf("b");
    PORTA_ISFR |= PORTx5_ISFR_MASK;//通过写“1”操作清除PA2 中断标志
  }
  
  //PA6 中断      
  else if((PORTA_ISFR&PORTx6_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA6 Interrupt");
    PORTA_ISFR |= PORTx6_ISFR_MASK;//通过写“1”操作清除PA2 中断标志
  }
  
  //PA7 中断      
  else if((PORTA_ISFR&PORTx7_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA7 Interrupt");
    PORTA_ISFR |= PORTx7_ISFR_MASK;//通过写“1”操作清除PA2 中断标志
  }
  //PA12 中断 
  else if((PORTA_ISFR&PORTx12_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA12 Interrupt");
    PORTA_ISFR |= PORTx12_ISFR_MASK;//通过写“1”操作清除PA12 中断标志
  }
  
  //PA13 中断      
  else if((PORTA_ISFR&PORTx13_ISFR_MASK)!=0)
  {
    uartPrintf("PORTA13 Interrupt");
    PORTA_ISFR |= PORTx13_ISFR_MASK;//通过写“1”操作清除PA13 中断标志
  }
  
  //PA14 中断              //作为场中断
  else if((PORTA_ISFR&PORTx14_ISFR_MASK)!=0)
  {
    PORTA_ISFR |= PORTx14_ISFR_MASK;//通过写“1”操作清除PA14 中断标志
    temp_counter = 0;
    temp_row = 0;
    en_href_interrupt();//打开行中断
  }
  
  //PA15 中断               //作为行中断
  else if((PORTA_ISFR&PORTx15_ISFR_MASK)!=0)
  {
    PORTA_ISFR |= PORTx15_ISFR_MASK;//通过写“1”操作清除PA15 中断标志
    //开始新的DMA
    new_dma(PicBuffer+temp_row);
    //行数标记
    temp_counter++;
    if(temp_counter%2==0)
      temp_row++;
    //标识采集一副图像完成
    if (temp_row == ROW)
    {
      complete_flag = 1;
      dis_href_interrupt();
      dis_vsyn_interrupt();
    }
  }
    //关闭行中断
  //其他中断请自行添加 
  else
  {
      uartPrintf("其他PORTA中断请继续添加 else-if 语句");
  }
}
