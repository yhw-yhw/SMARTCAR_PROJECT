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

#include "camera.h"
#include "common.h"
#include "PTM.h"

#define PROTECT 

#define STEER_LEFT      800//790     //����ڽ�����  �����ֵ�����ڲ��Եģ���Ҹ����Լ��Ķ������ 790
#define STEER_MIDDLE    1400//885     //����ڽ���ֵ 885
#define STEER_RIGHT     2000//980   //����ڽ��Ҽ���  980  
//��С�Ҵ� 95

#define  STEER_PWMN     TPM1
#define  STEER_PWMCH    TPM_CH1     //��ӦPTA13
#define  STEER_FREQ     100    //���Ƶ��   һ��TPMģ��ֻ�����һ��Ƶ��                        
#define  STEER_INIT_VAL 1400//885   //�����ʼֵ������1/10000  ��1200/10000  = 12%

extern s32 Line_Center[ROW];

void steer_init();

void PWMSetSteer(int angle_pwm);

void steerCtrl();


#endif