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

#include "steer.h"
#include "PID.h"
#include  "global.h"

#define TEST_LINE 90//(117-20)
int line=TEST_LINE;
int ec=RC; 
int uk=0;
 
/********************************************************************
** �������� : void steer_init() 
** �������� : ���ö��ת��
** ���     ��
** ����     ��
** ˵��     :  ��ʼ��PWM����ռ�ձ�
*********************************************************************/
void steer_init()         
{       
    KL46_PWM_Init(STEER_PWMN,STEER_PWMCH,STEER_FREQ,STEER_INIT_VAL); 
}

/********************************************************************
** ��������: void PWMSetSteer(int angle_pwm) 
** ��������: ���ö��ת��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //ռ�ձȲ��ܳ������ޣ���ֹ��ѹ��
    //ͬʱ��ֹ�������  
    //���������ʩ�Ǳ�Ҫ��
    if(angle_pwm > STEER_RIGHT)
         angle_pwm = STEER_RIGHT;
    if(angle_pwm < STEER_LEFT)
         angle_pwm = STEER_LEFT;
    TPM_PWM_Duty(STEER_PWMN,STEER_PWMCH,angle_pwm);
}


/********************************************************************
** ��������: steerCtrl
** ��������: ��������㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/

void steerCtrl()
{ //control  
  //static int angle_pwm=STEER_INIT_VAL;
  //��������λ��

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
  uk = ec-RC;//����λ��������ֵ��ƫ��
  //uartPrintf("uk%d\n ", uk);
  //angle_pwm = angle_pwm - pidSteer(uk);
  //uartPrintf("angle_pwm  %d", angle_pwm);
  PWMSetSteer(STEER_INIT_VAL+pidSteer(uk));
  
}


