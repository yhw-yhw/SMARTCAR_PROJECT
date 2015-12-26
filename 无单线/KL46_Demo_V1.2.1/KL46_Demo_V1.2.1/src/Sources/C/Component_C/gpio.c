/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#include "gpio.h"     //包含gpio头文件
#include "assert.h"

volatile struct GPIO_MemMap *GPIOx[5] = {PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR}; //定义五个指针数组保存 GPIOx 的地址
volatile struct PORT_MemMap *PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};

/*
************************************************************************
*  函数名称：gpio_init
*  功能说明：初始化gpio
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*            IO          引脚方向,0=输入,1=输出
*            data        输出初始状态,0=低电平,1=高电平 （对输入无效）
*  函数返回：无
*  修改时间：2012-3-15 
*  备    注：
************************************************************************
*************************************************************************/
void gpio_init (PORTx portx, u8 n, GPIO_CFG cfg, u8 data)
{
    assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) )
           ,"GPIO端口初始化错误");
   
    ASSERT( (n < 32u)  && (data < 2u) );           //断言检测端口号设置是否合理，电平是否合理

    //选择功能脚 PORTx_PCRx ，每个端口都有个寄存器 PORTx_PCRx
    PORT_PCR_REG(PORTX[portx], n) = (0 | PORT_PCR_MUX(1) | cfg);

    //端口方向控制输入还是输出
    if( ( (cfg & 0x01) == GPI) || (cfg == GPI_UP) ||     (cfg == GPI_UP_PF)      )
        //   最低位为0则输入   ||   输入上拉模式  ||   输入上拉，带无源滤波器
      {
           GPIO_PDDR_REG(GPIOx[portx]) &= ~(1 << n);  //设置端口方向为输入
      }
    else
     {
            GPIO_PDDR_REG(GPIOx[portx]) |= (1 << n);    //设置端口方向为输出
        if(data == 1)//output
        {
            GPIO_SET(portx, n, 1);                  //对端口输出控制，输出为1
        }
        else
        {
            GPIO_SET(portx, n, 0);                  //对端口输出控制，输出为0
        }
    }
}


/*************************************************************************
*  函数名称：gpio_set
*  功能说明：设置引脚状态
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*            data        输出初始状态,0=低电平,1=高电平
*  函数返回：无
*  修改时间：2012-1-16   已测试
*  备    注：
*************************************************************************/
void gpio_set (PORTx portx, u8 n, u8 data)
{
    ASSERT( (n < 32u)  && (data < 2u) );           //断言检测端口号设置是否合理，电平是否合理
   if(data == 1)               
        GPIO_SET(portx, n, 1);  
    else
        GPIO_SET(portx, n, 0);  

}

/*************************************************************************
*  函数名称：gpio_turn
*  功能说明：反转引脚状态
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*  函数返回：无
*  修改时间：2012-1-15   已测试
*  备    注：
*************************************************************************/
void gpio_turn (PORTx portx, u8 n)
{
    ASSERT( n < 32u );           //使用断言检查引脚号
    GPIO_TURN(portx, n);
}



/*************************************************************************
*  函数名称：gpio_get
*  功能说明：读取引脚输入状态
*  参数说明：PORTx       端口号（PORTA,PORTB,PORTC,PORTD,PORTE）
*            n           端口引脚
*  函数返回：无
*  修改时间：2012-1-15   已测试
*  备    注：
*************************************************************************/
u8 gpio_get(PORTx portx,u8 n)           //读取引脚状态
{
    ASSERT( n < 32u );                  //使用断言检查引脚号
    return GPIO_GET(portx,n);
}


//added by 大佐 start

/*************************************************************************
*  函数名称：gpio_interrupt_init
*  功能说明：IO中断初始化
*  参数说明：PORTx              端口号（只能选PORTA）
*            n                  端口引脚号（1,2,5,6,7,12,13,14,15）
             IO_INT_MODEn       中断触发方式
*  函数返回：无
*  修改时间：2012-1-15   已测试
*  备    注：只开发了PORTA 中断
*************************************************************************/
void gpio_interrupt_init(PORTx portx, u8 n, IO_INT_MODEn mode)
{
  assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) || (portx==PORTD) )
           ,"GPIO端口初始化错误");
  
  switch(portx){
  case PORTA :
    switch(n){
    case 1:
       /* 配置PA1管脚为GPIO功能*/
      PORTA_PCR1 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA1为上升沿触发 */
      PORTA_PCR1 |= PORT_PCR_IRQC(mode); 
    break;
    case 2:
      /* 配置PA2管脚为GPIO功能*/
      PORTA_PCR2 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA2为上升沿触发 */
      PORTA_PCR2 |= PORT_PCR_IRQC(mode); 
    break;
    case 5:
       /* 配置PA5管脚为GPIO功能*/
      PORTA_PCR5 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA5为上升沿触发 */
      PORTA_PCR5 |= PORT_PCR_IRQC(mode); 
    break;
    case 6:
       /* 配置PA6管脚为GPIO功能*/
      PORTA_PCR6 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA6为上升沿触发 */
      PORTA_PCR6 |= PORT_PCR_IRQC(mode); 
    break;
    case 7:
       /* 配置PA7管脚为GPIO功能*/
      PORTA_PCR7 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA7为上升沿触发 */
      PORTA_PCR7 |= PORT_PCR_IRQC(mode); 
    break;
    case 12:
       /* 配置PA12管脚为GPIO功能*/
      PORTA_PCR12 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA12为上升沿触发 */
      PORTA_PCR12 |= PORT_PCR_IRQC(mode); 
    break;
    case 13:
       /* 配置PA13管脚为GPIO功能*/
      PORTA_PCR13 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA13为上升沿触发 */
      PORTA_PCR13 |= PORT_PCR_IRQC(mode); 
    break;
    case 14:
       /* 配置PA14管脚为GPIO功能*/
      PORTA_PCR14 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA14为上升沿触发 */
      PORTA_PCR14 |= PORT_PCR_IRQC(mode); 
    break;
    case 15:
       /* 配置PA15管脚为GPIO功能*/
      PORTA_PCR15 = PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    
      /* 配置PA15为上升沿触发 */
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
 *只能使用PORTA 1,2,5,6,7,12,13,14,15
 *
 ************************************************/
void gpio_interrupt_dma_dis(PORTx portx, u8 n)
{
    assert( !(((portx==PORTA)  && (n==0)) || ((portx==PORTA)  && (n==3)) || ((portx==PORTA)  && (n==20)) || (portx==PORTD) )
           ,"GPIO端口初始化错误");
  
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
    //uartPrintf("PORTD 已经用作摄像头数据采集");
    break;
    
  default :break;
  }
}

// added end