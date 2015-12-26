/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[steer.h] 
* ��  �� ���������������
*�Ľ�����ֲ��Hyoga
*  Email ��498339494@qq.com
* ˵  �� ���������������
***********************************************************************
*/
#ifndef __STEER_H__
#define __STEER_H__

#include "common.h"
#include "PTM.h"


#define STEER_LEFT      2100     //����ڽ�����  �����ֵ�����ڲ��Եģ���Ҹ����Լ��Ķ������
#define STEER_MIDDLE    1400     //����ڽ���ֵ
#define STEER_RIGHT      700   //����ڽ��Ҽ���  


#define  STEER_PWMN     TPM1
#define  STEER_PWMCH    TPM_CH1     //��ӦPTA13
#define  STEER_FREQ     100    //���Ƶ��   һ��TPMģ��ֻ�����һ��Ƶ��                        
#define  STEER_INIT_VAL 1200   //�����ʼֵ������1/10000  ��1200/10000  = 12%

void steer_init();

void PWMSetSteer(int angle_pwm);

void steerCtrl();


#endif