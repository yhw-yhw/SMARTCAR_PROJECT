/********************************************************   
【平    台】KL46最小系统版
【底层设计】Johnlee
【参考】龙丘
【最后更新】2014年12月22日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
【说明】摄像头只能通过PORTD0-7 去读取，所以PORTD0-7不能用于其他，设置为输入
    
【参数】DMA_CHn:通道号：这里写死了通道0，所以传入参数为DMA_CH0
        uint32 SADDR: 源地址，摄像头应该设为(uint32)&GPIOD_PDIR，即把    PORTD0--7     作为数据源输入口
        DADDR ：目的地址，通常是定义一个数组，把数组名作为参数
        PTxn : DMA触发引脚，可定义为上升沿触发，下降沿触发，例如参数为PTA2，则在PTA2上升沿（下降沿）来时或触发一次DMA

        DMA_BYTEn : 每次DMA传输的字节数，可以配置为1字节，2字节或者4字节 
        u32 count : 总共需要传输的字节数，摄像头是改行的像素点的总数。传输完成后DMA就终止了，重启DMA需要重新执行该函数
        DMA_REQUEST_MODEn：DMA请求模式： DMA_REQ_M1为上升沿请求，DMA_REQ_M2为下降沿请求，DMA_REQ_M3为边沿请求
        注意不要跟其他引脚复用
        该DMA 函数仍不健壮，遇到问题请及时反馈346656208@qq.com
*********************************************************/

#include "dma.h"
#include "uart.h"

/************************************************************************************************
【函数说明】此函数可以设置DMA目的地址和传输长度（字节）
【参数】
       DADDR           目的地址，使用时地址+1即可
       TransferLength  每次传输长度（单位：字节）
************************************************************************************************/
void START_DMA(void * DADDR,u32 TransferLength)
{
  //SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;//打开DMA多路复用器时钟

  //SIM_SCGC7|=SIM_SCGC7_DMA_MASK;//打开DMA模块时钟


    DMAMUX0_CHCFG0 = 0x00;              //初始化前先关闭DMA功能
    /*if(((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) 
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))*/
    DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;    //通过写 "1" 清除 传输完成位 
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(TransferLength); // 设置总共传输多少字节 
    DMA_DCR0 |= DMA_DCR_D_REQ_MASK;                        //所有传输完成后自动清除中断请求
    DMA_DCR0 |= DMA_DCR_ERQ_MASK;
    DMA_DAR0 =(uint32)DADDR;         // 设置目的地址
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应51号DMA请求，即PORTC
    DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; // Enable the DMA MUX channel  
}
/***********************************************************************************************/

void DMA_PORTx2BUFF_Init(DMA_CHn CHn,uint32 SADDR,void * DADDR, PTxn ptxn,DMA_BYTEn byten,u32 TransferLength, DMA_REQUEST_MODEn mode)
{
  /********************************************
 *GPIO PORTD Configure
 *
 *******************************************  
gpio_init(PORTD,0,GPI ,0);
gpio_init(PORTD,1,GPI ,0);
gpio_init(PORTD,2,GPI ,0);
gpio_init(PORTD,3,GPI ,0);
gpio_init(PORTD,4,GPI ,0);
gpio_init(PORTD,5,GPI ,0);
gpio_init(PORTD,6,GPI ,0);
gpio_init(PORTD,7,GPI ,0);
 */
  //清除完成标志！
SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;//打开DMA多路复用器时钟

SIM_SCGC7|=SIM_SCGC7_DMA_MASK;//打开DMA模块时钟


    DMAMUX0_CHCFG0 = 0x00;              //初始化前先关闭DMA功能
    if(((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) 
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
      DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;    //通过写 "1" 清除 传输完成位
   
    DMA_SAR0 =SADDR;

    //DMA_SAR0 =(uint32)&GPIOD_PDIR;// 设置DMA源地址为I/O口 PORTD 0-7
    
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(TransferLength); // 设置总共传输多少字节 

    DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK| DMA_DCR_DSIZE_MASK );// 清除源地址读入字节数位和目的地址写入字节数位 
    DMA_DCR0 |= DMA_DCR_D_REQ_MASK;                        //所有传输完成后自动清除中断请求
    switch(byten)
    {
      case DMA_BYTE1:   //摄像头使用默认配置DMA_BYTE1
        DMA_DCR0 |= (DMA_DCR_SSIZE(1)   //源地址每次传输1个字节
             | DMA_DCR_DSIZE(1)             //目的地址每次写入1个字节
             | DMA_DCR_DINC_MASK            //目的地址自增   DMA_DCR_SINC_MASK(源地址自增，若有需要自行添加)
             | DMA_DCR_ERQ_MASK             //使能外部请求位
             | DMA_DCR_EADREQ_MASK           //使能异步DMA请求
             | DMA_DCR_CS_MASK                  //每次外部请求产生一次DMA
              );
      break;
      case DMA_BYTE2:
        DMA_DCR0 |= (DMA_DCR_SSIZE(2)   //源地址每次传输2个字节
             | DMA_DCR_DSIZE(2)             //目的地址每次写入2个字节
             | DMA_DCR_DINC_MASK            //目的地址自增   DMA_DCR_SINC_MASK(源地址自增，若有需要自行添加)
             | DMA_DCR_ERQ_MASK             //使能外部请求位
             | DMA_DCR_EADREQ_MASK           //使能异步DMA请求
             | DMA_DCR_CS_MASK               //每次外部请求产生一次DMA
              );
      break;
      case DMA_BYTE4:
        DMA_DCR0 |= (DMA_DCR_SSIZE(4)   //源地址每次传输4个字节
             | DMA_DCR_DSIZE(4)             //目的地址每次写入4个字节
             | DMA_DCR_DINC_MASK            //目的地址自增   DMA_DCR_SINC_MASK(源地址自增，若有需要自行添加)
             | DMA_DCR_ERQ_MASK             //使能外部请求位
             | DMA_DCR_EADREQ_MASK           //使能异步DMA请求
             | DMA_DCR_CS_MASK               //每次外部请求产生一次DMA
              );
      break;
      default :
        DMA_DCR0 |= (DMA_DCR_SSIZE(1)   //源地址每次传输1个字节
             | DMA_DCR_DSIZE(1)             //目的地址每次写入1个字节
             | DMA_DCR_DINC_MASK            //目的地址自增   DMA_DCR_SINC_MASK(源地址自增，若有需要自行添加)
             | DMA_DCR_ERQ_MASK             //使能外部请求位
             | DMA_DCR_EADREQ_MASK           //使能异步DMA请求
             | DMA_DCR_CS_MASK                  //每次外部请求产生一次DMA
              );
      break;
    }
     
    DMA_DAR0 =(uint32)DADDR;         // 设置目的地址
    
    switch(ptxn)
  {
  case PTA0 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR0 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case  PTA1 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case PTA2 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA
    break;
  case PTA3 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case  PTA4 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR4 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case PTA5 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR5 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
   case PTA6 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR6 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case  PTA7 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR7 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case PTC0 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR0 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;    
    case PTC1 :
      DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case  PTC2 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case PTC3 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
    case PTC7 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR7 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;    
    case PTC8 :
      DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR8 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case  PTC9 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR9 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
  case PTC10 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMA通道0对应51号DMA请求，即PORTC
    PORTC_PCR10 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA，
    break;
    
  default :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMA通道0对应49号DMA请求，即PORTA
    PORTA_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO功能，上升沿DMA
    break;
   }

}