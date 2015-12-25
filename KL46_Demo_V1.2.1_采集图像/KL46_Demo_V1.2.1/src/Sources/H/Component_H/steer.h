/*
************************************************************************
*                北京邮电大学 KL46 学习例程                                        
* 文件名 :[steer.h] 
* 描  述 ：电机机驱动函数
*改进与移植：Hyoga
*  Email ：498339494@qq.com
* 说  明 ：电机机驱动函数
***********************************************************************
*/
#ifndef __STEER_H__
#define __STEER_H__

#include "camera.h"
#include "common.h"
#include "PTM.h"

#define PROTECT 

#define STEER_LEFT      800//790     //舵机摆角左极限  这里的值是用于测试的，大家根据自己的舵机更改 790
#define STEER_MIDDLE    1400//885     //舵机摆角中值 885
#define STEER_RIGHT     2000//980   //舵机摆角右极限  980  
//左小右大 95

#define  STEER_PWMN     TPM1
#define  STEER_PWMCH    TPM_CH1     //对应PTA13
#define  STEER_FREQ     100    //舵机频率   一个TPM模块只能输出一个频率                        
#define  STEER_INIT_VAL 1400//885   //舵机初始值，精度1/10000  即1200/10000  = 12%

extern s32 Line_Center[ROW];

void steer_init();

void PWMSetSteer(int angle_pwm);

void steerCtrl();


#endif