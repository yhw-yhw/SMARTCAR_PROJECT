/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "common.h"

#define GPIO_SET(PORTx,n,x)          GPIO_SET_##x((PORTx),(n))                                  //���������ƽ
#define GPIO_TURN(PORTx,n)           (GPIO_PDOR_REG(GPIOx[(PORTx)]) ^=  (1<<(n)))               //��ת�����ƽ
#define GPIO_GET(PORTx,n)            ((GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n))&0x1)                 //��ȡ��������״̬

#define GPIO_SET_1(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) |=  (1<<(n))      //�������Ϊ�ߵ�ƽ      
#define GPIO_SET_0(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) &= ~(1<<(n))      //�������Ϊ�͵�ƽ      

/*���Ⲣ�ڲ���ʱһ��ע���ڳ�ʼ����ʱ��һλһζ���������������*/
//��IO��4λ����
#define GPIO_SET_4bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xf<<(n)) )|(((data)&0x0f)<<(n)))   //д4λ���ݣ�nΪ���λ���źţ�
#define GPIO_GET_4bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xf)                                                        //��4λ���ݣ�nΪ���λ���źţ�

//��IO��8λ����
#define GPIO_SET_8bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((data)&0xff)<<(n)))  //д8λ���ݣ�nΪ���λ���źţ�  
#define GPIO_GET_8bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xff)                                                       //��8λ���ݣ�nΪ���λ���źţ�

//��IO��16λ����
#define GPIO_SET_16bit(PORTx,n,data)  GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])&~(0xffff<<(n)) )|(((data)&0xffff)<<(n)))   //д16λ���ݣ�nΪ���λ���źţ�
#define GPIO_GET_16bit(PORTx,n)       (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xffff)                                                         //��16λ���ݣ�nΪ���λ���źţ�

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


//����ܽŷ���
typedef enum GPIO_CFG
{
    //�����ֵ���ܸģ�����
    GPI         = 0,                          //����ܽ����뷽��      GPIOx_PDDRn�0��ʾ���룬1��ʾ���
    GPO         = 1,                          //����ܽ��������

    GPI_DOWN    = 0x02,                       //��������              PORTx_PCRn��ҪPE=1��PS=0
    GPI_UP      = 0x03,                       //��������              PORTx_PCRn��ҪPE=1��PS=1
    GPI_PF      = 0x10,                       //���룬����Դ�˲���,�˲���Χ��10 MHz ~ 30 MHz ����֧�ָ��ٽӿڣ�>=2MHz��  0b10000           Passive Filter Enable
    GPI_DOWN_PF = GPI_DOWN | GPI_PF ,         //��������������Դ�˲���
    GPI_UP_PF   = GPI_UP   | GPI_PF ,         //��������������Դ�˲���

    GPO_HDS     = 0x41,                        //�������������   0b100 0001    High drive strength
    GPO_SSR     = 0x05,                        //������仯��          0b101     Slow slew rate
    GPO_HDS_SSR = GPO_HDS | GPO_SSR,           //������������������仯��
} GPIO_CFG;  //���λΪ0���϶������룻GPI_UP �� GPI_UP_PF�����λΪ1������Ϊ���



void gpio_init (PORTx portx, u8 n, GPIO_CFG cfg, u8 data);
void gpio_set (PORTx portx, u8 n, u8 data);
void gpio_turn (PORTx portx, u8 n);
u8 gpio_get(PORTx portx,u8 n);



// add by johnlee start
    
//�жϴ���ö������
typedef enum IO_INT_MODEn
{
    IO_INT_HIGH_M=8,        //�͵�ƽ����
    IO_INT_RISING_M=9,        //�������ش���
    IO_INT_FALLING_M=10,        //�½�������
    IO_INT_R_F_M=11,        //��������
    IO_INT_LOW_M=12        //�ߵ�ƽ����
}IO_INT_MODEn;

/*IO�жϱ�־λ */
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

/*�ж�ʹ��*/
#define INI_PORTA_EN_MASK        INT_PORTA-16
/*�жϽ��û�DMA��������*/
#define INI_PORTx_DIS            0xFFF0FFFF



void gpio_interrupt_init(PORTx portx, u8 n, IO_INT_MODEn mode);   
void gpio_interrupt_dma_dis(PORTx portx, u8 n);

// add by johnlee end


#endif 
