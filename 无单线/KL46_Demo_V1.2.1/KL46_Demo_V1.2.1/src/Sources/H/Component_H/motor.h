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
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 0   //为两路控制电机预留

#include "common.h"
#include "PTM.h"


#define MOTOR_MAX    9600
#define MOTOR_MIN    -9600


#define  MOTOR_PWMN       TPM0           
#define  MOTOR_PWMCH0     TPM_CH0           //PTC1
#define  MOTOR_PWMCH1     TPM_CH1           //PTC2 
 

#define  MOTOR_FREQ 16000           //电机频率   16k
#define  MOTOR_INIT_VAL 0           //电机初始值，精度1/10000  即0/10000 0%

void motor_init();
void PWMSetMotor(s32 speed_pwm);

#if MOTOR_DOUBLE
            
    #define  MOTOR_PWMCH2     TPM_CH2           //PTC3
    #define  MOTOR_PWMCH3     TPM_CH3           //PTC4 
    
    void PWMSetMotor2(s32 speed_pwm2);//双电机
#endif 

    
    void motorCtrl();
      
#endif
