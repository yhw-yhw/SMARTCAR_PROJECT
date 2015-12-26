/********************************************************   
��ƽ    ̨��KL46��Сϵͳ��
���ײ���ơ�Johnlee
���ο�������
�������¡�2014��12��22��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
��˵��������ͷֻ��ͨ��PORTD0-7 ȥ��ȡ������PORTD0-7������������������Ϊ����
    
��������DMA_CHn:ͨ���ţ�����д����ͨ��0�����Դ������ΪDMA_CH0
        uint32 SADDR: Դ��ַ������ͷӦ����Ϊ(uint32)&GPIOD_PDIR������    PORTD0--7     ��Ϊ����Դ�����
        DADDR ��Ŀ�ĵ�ַ��ͨ���Ƕ���һ�����飬����������Ϊ����
        PTxn : DMA�������ţ��ɶ���Ϊ�����ش������½��ش������������ΪPTA2������PTA2�����أ��½��أ���ʱ�򴥷�һ��DMA

        DMA_BYTEn : ÿ��DMA������ֽ�������������Ϊ1�ֽڣ�2�ֽڻ���4�ֽ� 
        u32 count : �ܹ���Ҫ������ֽ���������ͷ�Ǹ��е����ص��������������ɺ�DMA����ֹ�ˣ�����DMA��Ҫ����ִ�иú���
        DMA_REQUEST_MODEn��DMA����ģʽ�� DMA_REQ_M1Ϊ����������DMA_REQ_M2Ϊ�½�������DMA_REQ_M3Ϊ��������
        ע�ⲻҪ���������Ÿ���
        ��DMA �����Բ���׳�����������뼰ʱ����346656208@qq.com
*********************************************************/

#include "dma.h"
#include "uart.h"

/************************************************************************************************
������˵�����˺�����������DMAĿ�ĵ�ַ�ʹ��䳤�ȣ��ֽڣ�
��������
       DADDR           Ŀ�ĵ�ַ��ʹ��ʱ��ַ+1����
       TransferLength  ÿ�δ��䳤�ȣ���λ���ֽڣ�
************************************************************************************************/
void START_DMA(void * DADDR,u32 TransferLength)
{
  //SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;//��DMA��·������ʱ��

  //SIM_SCGC7|=SIM_SCGC7_DMA_MASK;//��DMAģ��ʱ��


    DMAMUX0_CHCFG0 = 0x00;              //��ʼ��ǰ�ȹر�DMA����
    /*if(((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) 
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))*/
    DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;    //ͨ��д "1" ��� �������λ 
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(TransferLength); // �����ܹ���������ֽ� 
    DMA_DCR0 |= DMA_DCR_D_REQ_MASK;                        //���д�����ɺ��Զ�����ж�����
    DMA_DCR0 |= DMA_DCR_ERQ_MASK;
    DMA_DAR0 =(uint32)DADDR;         // ����Ŀ�ĵ�ַ
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
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
  //�����ɱ�־��
SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;//��DMA��·������ʱ��

SIM_SCGC7|=SIM_SCGC7_DMA_MASK;//��DMAģ��ʱ��


    DMAMUX0_CHCFG0 = 0x00;              //��ʼ��ǰ�ȹر�DMA����
    if(((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK) 
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
   || ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
      DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;    //ͨ��д "1" ��� �������λ
   
    DMA_SAR0 =SADDR;

    //DMA_SAR0 =(uint32)&GPIOD_PDIR;// ����DMAԴ��ַΪI/O�� PORTD 0-7
    
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(TransferLength); // �����ܹ���������ֽ� 

    DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK| DMA_DCR_DSIZE_MASK );// ���Դ��ַ�����ֽ���λ��Ŀ�ĵ�ַд���ֽ���λ 
    DMA_DCR0 |= DMA_DCR_D_REQ_MASK;                        //���д�����ɺ��Զ�����ж�����
    switch(byten)
    {
      case DMA_BYTE1:   //����ͷʹ��Ĭ������DMA_BYTE1
        DMA_DCR0 |= (DMA_DCR_SSIZE(1)   //Դ��ַÿ�δ���1���ֽ�
             | DMA_DCR_DSIZE(1)             //Ŀ�ĵ�ַÿ��д��1���ֽ�
             | DMA_DCR_DINC_MASK            //Ŀ�ĵ�ַ����   DMA_DCR_SINC_MASK(Դ��ַ������������Ҫ�������)
             | DMA_DCR_ERQ_MASK             //ʹ���ⲿ����λ
             | DMA_DCR_EADREQ_MASK           //ʹ���첽DMA����
             | DMA_DCR_CS_MASK                  //ÿ���ⲿ�������һ��DMA
              );
      break;
      case DMA_BYTE2:
        DMA_DCR0 |= (DMA_DCR_SSIZE(2)   //Դ��ַÿ�δ���2���ֽ�
             | DMA_DCR_DSIZE(2)             //Ŀ�ĵ�ַÿ��д��2���ֽ�
             | DMA_DCR_DINC_MASK            //Ŀ�ĵ�ַ����   DMA_DCR_SINC_MASK(Դ��ַ������������Ҫ�������)
             | DMA_DCR_ERQ_MASK             //ʹ���ⲿ����λ
             | DMA_DCR_EADREQ_MASK           //ʹ���첽DMA����
             | DMA_DCR_CS_MASK               //ÿ���ⲿ�������һ��DMA
              );
      break;
      case DMA_BYTE4:
        DMA_DCR0 |= (DMA_DCR_SSIZE(4)   //Դ��ַÿ�δ���4���ֽ�
             | DMA_DCR_DSIZE(4)             //Ŀ�ĵ�ַÿ��д��4���ֽ�
             | DMA_DCR_DINC_MASK            //Ŀ�ĵ�ַ����   DMA_DCR_SINC_MASK(Դ��ַ������������Ҫ�������)
             | DMA_DCR_ERQ_MASK             //ʹ���ⲿ����λ
             | DMA_DCR_EADREQ_MASK           //ʹ���첽DMA����
             | DMA_DCR_CS_MASK               //ÿ���ⲿ�������һ��DMA
              );
      break;
      default :
        DMA_DCR0 |= (DMA_DCR_SSIZE(1)   //Դ��ַÿ�δ���1���ֽ�
             | DMA_DCR_DSIZE(1)             //Ŀ�ĵ�ַÿ��д��1���ֽ�
             | DMA_DCR_DINC_MASK            //Ŀ�ĵ�ַ����   DMA_DCR_SINC_MASK(Դ��ַ������������Ҫ�������)
             | DMA_DCR_ERQ_MASK             //ʹ���ⲿ����λ
             | DMA_DCR_EADREQ_MASK           //ʹ���첽DMA����
             | DMA_DCR_CS_MASK                  //ÿ���ⲿ�������һ��DMA
              );
      break;
    }
     
    DMA_DAR0 =(uint32)DADDR;         // ����Ŀ�ĵ�ַ
    
    switch(ptxn)
  {
  case PTA0 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR0 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case  PTA1 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case PTA2 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA
    break;
  case PTA3 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case  PTA4 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR4 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case PTA5 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR5 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
   case PTA6 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR6 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case  PTA7 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR7 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case PTC0 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR0 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;    
    case PTC1 :
      DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR1 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case  PTC2 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case PTC3 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR3 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
    case PTC7 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR7 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;    
    case PTC8 :
      DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR8 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case  PTC9 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR9 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
  case PTC10 :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(51); //DMAͨ��0��Ӧ51��DMA���󣬼�PORTC
    PORTC_PCR10 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA��
    break;
    
  default :
    DMAMUX0_CHCFG0 =DMAMUX_CHCFG_SOURCE(49); //DMAͨ��0��Ӧ49��DMA���󣬼�PORTA
    PORTA_PCR2 = PORT_PCR_MUX(1)|PORT_PCR_IRQC(mode);//GPIO���ܣ�������DMA
    break;
   }

}