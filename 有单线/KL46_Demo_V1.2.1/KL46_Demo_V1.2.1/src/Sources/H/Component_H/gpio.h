/********************************************************   
【平    台】龙丘KL46最小系统版
【原版】龙丘
【设计与改进】BUPTSmartCar 2011级
【最后更新】2014年10月2日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
*********************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "common.h"

#define GPIO_SET(PORTx,n,x)          GPIO_SET_##x((PORTx),(n))                                  //设置输出电平
#define GPIO_TURN(PORTx,n)           (GPIO_PDOR_REG(GPIOx[(PORTx)]) ^=  (1<<(n)))               //翻转输出电平
#define GPIO_GET(PORTx,n)            ((GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n))&0x1)                 //读取引脚输入状态

#define GPIO_SET_1(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) |=  (1<<(n))      //设置输出为高电平      
#define GPIO_SET_0(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) &= ~(1<<(n))      //设置输出为低电平      

/*设这并口操作时一定注意在初始化的时候一位一味的配置输出，输入*/
//对IO口4位操作
#define GPIO_SET_4bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xf<<(n)) )|(((data)&0x0f)<<(n)))   //写4位数据（n为最低位引脚号）
#define GPIO_GET_4bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xf)                                                        //读4位数据（n为最低位引脚号）

//对IO口8位操作
#define GPIO_SET_8bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((data)&0xff)<<(n)))  //写8位数据（n为最低位引脚号）  
#define GPIO_GET_8bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xff)                                                       //读8位数据（n为最低位引脚号）

//对IO口16位操作
#define GPIO_SET_16bit(PORTx,n,data)  GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])&~(0xffff<<(n)) )|(((data)&0xffff)<<(n)))   //写16位数据（n为最低位引脚号）
#define GPIO_GET_16bit(PORTx,n)       (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xffff)                                                         //读16位数据（n为最低位引脚号）

#define HIGH  1u
#define LOW   0u

extern volatile  struct GPIO_MemMap *GPIOx[5];
extern volatile struct  PORT_MemMap *PORTX[5];

typedef enum PORTx
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE
} PORTx;


//定义管脚方向
typedef enum GPIO_CFG
{
    //这里的值不能改！！！
    GPI         = 0,                          //定义管脚输入方向      GPIOx_PDDRn里，0表示输入，1表示输出
    GPO         = 1,                          //定义管脚输出方向

    GPI_DOWN    = 0x02,                       //输入下拉              PORTx_PCRn需要PE=1，PS=0
    GPI_UP      = 0x03,                       //输入上拉              PORTx_PCRn需要PE=1，PS=1
    GPI_PF      = 0x10,                       //输入，带无源滤波器,滤波范围：10 MHz ~ 30 MHz 。不支持高速接口（>=2MHz）  0b10000           Passive Filter Enable
    GPI_DOWN_PF = GPI_DOWN | GPI_PF ,         //输入下拉，带无源滤波器
    GPI_UP_PF   = GPI_UP   | GPI_PF ,         //输入上拉，带无源滤波器

    GPO_HDS     = 0x41,                        //输出高驱动能力   0b100 0001    High drive strength
    GPO_SSR     = 0x05,                        //输出慢变化率          0b101     Slow slew rate
    GPO_HDS_SSR = GPO_HDS | GPO_SSR,           //输出高驱动能力、慢变化率
} GPIO_CFG;  //最低位为0，肯定是输入；GPI_UP 和 GPI_UP_PF的最低位为1，其他为输出



void gpio_init (PORTx portx, u8 n, GPIO_CFG cfg, u8 data);
void gpio_set (PORTx portx, u8 n, u8 data);
void gpio_turn (PORTx portx, u8 n);
u8 gpio_get(PORTx portx,u8 n);



// add by johnlee start
    
//中断触发枚举类型
typedef enum IO_INT_MODEn
{
    IO_INT_HIGH_M=8,        //低电平触发
    IO_INT_RISING_M=9,        //上升沿沿触发
    IO_INT_FALLING_M=10,        //下降沿请求
    IO_INT_R_F_M=11,        //边沿请求
    IO_INT_LOW_M=12        //高电平触发
}IO_INT_MODEn;

/*IO中断标志位 */
#define PORTx0_ISFR_MASK        0x00000001
#define PORTx1_ISFR_MASK        0x00000002
#define PORTx2_ISFR_MASK        0x00000004
#define PORTx3_ISFR_MASK        0x00000008
#define PORTx4_ISFR_MASK        0x00000010
#define PORTx5_ISFR_MASK        0x00000020
#define PORTx6_ISFR_MASK        0x00000040
#define PORTx7_ISFR_MASK        0x00000080
#define PORTx8_ISFR_MASK        0x00000100
#define PORTx9_ISFR_MASK        0x00000200
#define PORTx10_ISFR_MASK        0x00000400
#define PORTx11_ISFR_MASK        0x00000800
#define PORTx12_ISFR_MASK        0x00001000
#define PORTx13_ISFR_MASK        0x00002000
#define PORTx14_ISFR_MASK        0x00004000
#define PORTx15_ISFR_MASK        0x00008000
#define PORTx16_ISFR_MASK        0x00010000
#define PORTx17_ISFR_MASK        0x00020000
#define PORTx18_ISFR_MASK        0x00040000
#define PORTx19_ISFR_MASK        0x00080000
#define PORTx20_ISFR_MASK        0x00100000
#define PORTx21_ISFR_MASK        0x00200000
#define PORTx22_ISFR_MASK        0x00400000
#define PORTx23_ISFR_MASK        0x00800000
#define PORTx24_ISFR_MASK        0x01000000
#define PORTx25_ISFR_MASK        0x02000000
#define PORTx26_ISFR_MASK        0x04000000
#define PORTx27_ISFR_MASK        0x08000000
#define PORTx28_ISFR_MASK        0x10000000
#define PORTx29_ISFR_MASK        0x20000000
#define PORTx30_ISFR_MASK        0x40000000
#define PORTx31_ISFR_MASK        0x80000000

/*中断使能*/
#define INI_PORTA_EN_MASK        INT_PORTA-16
/*中断禁用或DMA触发禁用*/
#define INI_PORTx_DIS            0xFFF0FFFF



void gpio_interrupt_init(PORTx portx, u8 n, IO_INT_MODEn mode);   
void gpio_interrupt_dma_dis(PORTx portx, u8 n);

// add by johnlee end


#endif 
