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

#include "motor.h"
#include "PTM.h"
#include "global.h"

/********************************************************************
** ��������: void steer_init() 
** ��������: ���ö��ת��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:  
*********************************************************************/
void motor_init()         
{  
    KL46_PWM_Init(MOTOR_PWMN,MOTOR_PWMCH0,MOTOR_FREQ,MOTOR_INIT_VAL); 
    KL46_PWM_Init(MOTOR_PWMN,MOTOR_PWMCH1,MOTOR_FREQ,MOTOR_INIT_VAL); 
#if MOTOR_DOUBLE
    KL46_PWM_Init(MOTOR_PWMN,MOTOR_PWMCH2,MOTOR_FREQ,MOTOR_INIT_VAL); 
    KL46_PWM_Init(MOTOR_PWMN,MOTOR_PWMCH3,MOTOR_FREQ,MOTOR_INIT_VAL); 
#endif
}

/********************************************************************
** ��������: PWMSetMotor
** ��������: �����ٶ�
** ��ڣ��ٶ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void PWMSetMotor(s32 speed_pwm)         
{
    if(speed_pwm < MOTOR_MIN)
    {
      speed_pwm = MOTOR_MIN;
    }
    if(speed_pwm > MOTOR_MAX)
    {
      speed_pwm = MOTOR_MAX;
    }
    
   
    if(speed_pwm > 0) 
    {
        TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH0,(u32)speed_pwm);
        TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH1,0);
    } 
    else 
    {
       speed_pwm = -speed_pwm;
       TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH1,(u32)speed_pwm);
       TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH0,0);
    }
}
/********************************************************************
** ��������: PWMSetMotor2
** ��������: �����ٶȣ��ڶ��������
** ��ڣ��ٶ�
** ���ڣ�
** ˵��:  
*********************************************************************/
#if MOTOR_DOUBLE
void PWMSetMotor2(s32 speed_pwm2)         
{
    if(speed_pwm2 < MOTOR_MIN)
    {
      speed_pwm2 = MOTOR_MIN;
    }
    if(speed_pwm2 > MOTOR_MAX)
    {
      speed_pwm2 = MOTOR_MAX;
    }
    
   
    if(speed_pwm2 > 0) 
    {
        TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH2,(u32)speed_pwm2);
        TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH3,0);
    } 
    else 
    {
       speed_pwm2 = -speed_pwm2;
       TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH3,(u32)speed_pwm2);
       TPM_PWM_Duty(MOTOR_PWMN,MOTOR_PWMCH2,0);
    }
}
#endif
/********************************************************************
** ��������: motorCtrl
** ��������: �ٶȿ����㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void motorCtrl()
{  
  s16 speedPWM=0;
  /*д���Լ��Ŀ����㷨*/
  
  PWMSetMotor(speedPWM);
  #if MOTOR_DOUBLE  
     s16 speedPWM2=0;
     PWMSetMotor2(speedPWM2);
  #endif
}







