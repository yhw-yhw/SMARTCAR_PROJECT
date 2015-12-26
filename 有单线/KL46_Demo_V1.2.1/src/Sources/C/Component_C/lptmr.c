/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#include "common.h"
#include "lptmr.h"
#include "includes.h"
#define LPTMR_ALT1 0x1
#define LPTMR_ALT2 0x2
#define LPTMR_ALT3 0x3

/*��Ҫʹ�øú�����Pulse Counterģʽ��ͻ*/
/*void time_delay_ms(unsigned int count_val)
{
  // ʹ��LPTMRʱ��
  SIM_SCGC5|=SIM_SCGC5_LPTMR_MASK;

  // ��λLPTMR��ʱ��
  LPTMR0_CSR=0;

  // ���ñȽ�ֵ��λΪms 
  LPTMR0_CMR = count_val;

  // ����LPTMR�Ĳο�ʱ��
  LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK;

  //������ʱ�� 
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;

  // �ȴ���������
  while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK));

  //�رն�ʱ����־λ 
  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;

  return;
}*/

/*PTC5Ϊ���벶׽��*/
void lptmr_counter_init(void)
{
   
    
    SIM_SCGC5   |= SIM_SCGC5_PORTC_MASK;//��PORTCʱ�� 
    PORTC_PCR5  =PORT_PCR_MUX(0x2); //��PTC5��ʹ��LPTMR0_ALT2
    //GPIO_Init    (PORTA, 19,GPI_UP, 0);
    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;//����ʱ��
    LPTMR0_CSR=0x00;//���״̬�Ĵ���
    //LPTMR0_CMR = LPTMR_CMR_COMPARE(count);  //Set compare value
    LPTMR0_PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK;//ʱ��ѡ��LP0
    

    //the CSR mmust be initially written before configuring others 
    LPTMR0_CSR =(  LPTMR_CSR_TCF_MASK   // Clear any pending interrupt
                 //| LPTMR_CSR_TIE_MASK   // LPT interrupt enabled
                 | LPTMR_CSR_TPS(2)     //TMR pin select
                 | LPTMR_CSR_TPP_MASK   //TMR Pin polarity
                 | LPTMR_CSR_TFC_MASK   // CNR is reset on overflow��65535 over��
                 | LPTMR_CSR_TMS_MASK   //LPTMR0 as PULSE Counter MODE
                );
    
    
    
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;   //Turn on LPT and start counting
    

}



uint16 lptmr_counter_value()
{
  LPTMR0_CNR=0x1;//write any value before reading
  return LPTMR0_CNR;
}


void lptmr_clear_registers()
{
  LPTMR0_CSR=0x00;
  LPTMR0_PSR=0x00;
  LPTMR0_CMR=0x00;
}

void lptmr_counter_clean(void)
{
  LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;   //Turn OFF LPT and Restart
  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;
}