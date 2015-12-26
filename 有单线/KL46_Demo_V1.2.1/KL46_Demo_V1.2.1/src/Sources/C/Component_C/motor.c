/*
************************************************************************
*                北京邮电大学 KL46 学习例程                                        
* 文件名 :[motor.h] 
* 描  述 ：电机机驱动函数
*改进与移植：Hyoga
*  Email ：498339494@qq.com
* 说  明 ：电机机驱动函数
***********************************************************************
*/

#include "motor.h"
#include "PTM.h"
#include "global.h"

/********************************************************************
** 函数名称: void steer_init() 
** 功能描述: 设置舵机转向
** 入口：角度值
** 出口：
** 说明:  
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
** 函数名称: PWMSetMotor
** 功能描述: 设置速度
** 入口：速度
** 出口：
** 说明:  
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
** 函数名称: PWMSetMotor2
** 功能描述: 设置速度（第二个电机）
** 入口：速度
** 出口：
** 说明:  
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
** 函数名称: motorCtrl
** 功能描述: 速度控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/
void motorCtrl()
{  
  s16 speedPWM=0;
  /*写下自己的控制算法*/
  
  PWMSetMotor(speedPWM);
  #if MOTOR_DOUBLE  
     s16 speedPWM2=0;
     PWMSetMotor2(speedPWM2);
  #endif
}







