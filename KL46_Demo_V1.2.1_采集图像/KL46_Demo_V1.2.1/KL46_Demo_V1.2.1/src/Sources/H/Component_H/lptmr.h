/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
��ԭ�桿����
�������Ľ���BUPTSmartCar 2011��
�������¡�2014��10��2��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
*********************************************************/
#ifndef __LPTMR_H__
#define __LPTMR_H__


//void time_delay_ms(unsigned int count_val);/*��Ҫʹ�øú�����Pulse Counterģʽ��ͻ*/
void lptmr_clear_registers();

uint16 lptmr_counter_value();//PTC5
void lptmr_counter_init(void);
void lptmr_counter_clean(void);

#endif 
