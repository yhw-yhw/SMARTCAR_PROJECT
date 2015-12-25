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

#include "steer.h"
#include "PID.h"
#include  "global.h"

#define TEST_LINE 90//(117-20)
int line=TEST_LINE;
int ec=RC; 
int uk=0;
 
/********************************************************************
** 函数名称 : void steer_init() 
** 功能描述 : 设置舵机转向
** 入口     ：
** 出口     ：
** 说明     :  初始化PWM波及占空比
*********************************************************************/
void steer_init()         
{       
    KL46_PWM_Init(STEER_PWMN,STEER_PWMCH,STEER_FREQ,STEER_INIT_VAL); 
}

/********************************************************************
** 函数名称: void PWMSetSteer(int angle_pwm) 
** 功能描述: 设置舵机转向
** 入口：角度值
** 出口：
** 说明:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //占空比不能超过上限（防止过压）
    //同时防止方向打死  
    //这个保护措施是必要的
    if(angle_pwm > STEER_RIGHT)
         angle_pwm = STEER_RIGHT;
    if(angle_pwm < STEER_LEFT)
         angle_pwm = STEER_LEFT;
    TPM_PWM_Duty(STEER_PWMN,STEER_PWMCH,angle_pwm);
}


/********************************************************************
** 函数名称: steerCtrl
** 功能描述: 舵机控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/

void steerCtrl()
{ //control  
  //static int angle_pwm=STEER_INIT_VAL;
  //计算中心位置

  // forty = 0, eighty = 0, i, j, k, count;
  /*
  
  for (count = 117; (Line_Center[count] - Line_Center[count - 1])<8 && (Line_Center[count] - Line_Center[count - 1])>-8; count--);
  
  for (i = 118,j=0; i >= (118 + count) / 2; i--,j++)
  {
            forty = forty + Line_Center[i];
  }
  //uartPrintf("j %d\n",j);
  for (i = (118 + count) / 2, k=0 ; i >= count; i--, k++)
  {
    //      uartPrintf(" %d ", Line_Center[i]);
          eighty = eighty + Line_Center[i];
  }
  //uartPrintf("k %d \n",k);
  ec = 0.7 * forty / j + 0.3 * eighty / k;
  //uartPrintf("ec %d \n", ec);
  */
  ec=Line_Center[line];
  uk = ec-RC;//中心位置与中心值的偏差
  //uartPrintf("uk%d\n ", uk);
  //angle_pwm = angle_pwm - pidSteer(uk);
  //uartPrintf("angle_pwm  %d", angle_pwm);
  PWMSetSteer(STEER_INIT_VAL+pidSteer(uk));
  
}


