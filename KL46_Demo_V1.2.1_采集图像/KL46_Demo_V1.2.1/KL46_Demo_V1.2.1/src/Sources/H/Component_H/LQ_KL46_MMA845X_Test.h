/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@aliyun.com
������汾��V2.0
�������¡�2013��12��24��
�������Ϣ�ο����е�ַ�� 
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
------------------------------------
ʹ�ñ����������ܿƼ�cortex-M0����������
*********************************************************/

#ifndef _LQ_MMA845x_H
#define _LQ_MMA845x_H
#include "common.h"
#include "includes.h"
#include "KL46_IIC.h"




void accel_init(void);
void hal_dev_mma8451_init(void);
static void pause(void);
uint8 hal_dev_mma8451_read_reg(uint8 addr);
void hal_dev_mma8451_write_reg(uint8 addr, uint8 data);
void accel_init(void);
void accel_read(void);
void accel_test(void);
int iAcclReadX(void) ;
int iAcclReadY(void) ;
int iAcclReadZ(void) ;



#endif