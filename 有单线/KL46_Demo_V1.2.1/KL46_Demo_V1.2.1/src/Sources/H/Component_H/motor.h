/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[motor.h] 
* ��  �� ���������������
*�Ľ�����ֲ��Hyoga
*  Email ��498339494@qq.com
* ˵  �� ���������������
***********************************************************************
*/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 0   //Ϊ��·���Ƶ��Ԥ��

#include "common.h"
#include "PTM.h"


#define MOTOR_MAX    9600
#define MOTOR_MIN    -9600


#define  MOTOR_PWMN       TPM0           
#define  MOTOR_PWMCH0     TPM_CH0           //PTC1
#define  MOTOR_PWMCH1     TPM_CH1           //PTC2 
 

#define  MOTOR_FREQ 16000           //���Ƶ��   16k
#define  MOTOR_INIT_VAL 0           //�����ʼֵ������1/10000  ��0/10000 0%

void motor_init();
void PWMSetMotor(s32 speed_pwm);

#if MOTOR_DOUBLE
            
    #define  MOTOR_PWMCH2     TPM_CH2           //PTC3
    #define  MOTOR_PWMCH3     TPM_CH3           //PTC4 
    
    void PWMSetMotor2(s32 speed_pwm2);//˫���
#endif 

    
    void motorCtrl();
      
#endif
