/********************************************************   
��ƽ    ̨��KL46��Сϵͳ��
���ײ���ơ�Johnlee
���ο�������
�������¡�2014��12��22��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
��˵����Ŀǰ����������ֻ������ͷ��ʹ�ã���������ò���������ͷ������dma.c�￴˵��
*********************************************************/

#ifndef __DMA_H__
#define __DMA_H__ 
	
#include "common.h"
#include "sysinit.h"
#include "gpio_cfg.h"
#include "gpio.h"
typedef enum DMA_CHn
{
    DMA_CH0,
    DMA_CH1,
    DMA_CH2,
    DMA_CH3,
}DMA_CHn;

typedef enum DMA_REQUEST_MODEn
{
    DMA_REQ_M1=1,        //����������
    DMA_REQ_M2=2,        //�½�������
    DMA_REQ_M3=3,        //��������
}DMA_REQUEST_MODEn;

typedef enum DMA_BYTEn      //DMAÿ�δ����ֽ���
{
    DMA_BYTE1=0,
    DMA_BYTE2=1,
    DMA_BYTE4=2,
    DMA_BYTE16=4
}DMA_BYTEn;
void DMA_PORTx2BUFF_Init(DMA_CHn CHn,uint32 SADDR,void * DADDR, PTxn ptxn,DMA_BYTEn byten,u32 count, DMA_REQUEST_MODEn mode);
void START_DMA(void * DADDR,u32 TransferLength);
#endif