#include"PID.h"
#include"global.h"
//声明变量
//定义变量


float kd=0.0;  //0.9
//float ek; //偏差 e[k]
static float ek1=0; //偏差 e[k-1]
//float ek2; //偏差 e[k-2]
static float adjust=0; //最终输出的调整量

int pidSteer(int ek)
{
  if((ek<0?-ek:ek)<EE) //ee 为误差的阀值，小于这个数值的时候，不做 PID 调整，避免误差较小时频繁调节引起震荡。 ee 的值可自己设
 {
    adjust=0;
 }
 else
 {
    adjust = kp * ek + kd*(ek - ek1);
    ek1=ek;
 }
   //uartPrintf("***** %f \n",adjust);
   return (int)adjust;
}
