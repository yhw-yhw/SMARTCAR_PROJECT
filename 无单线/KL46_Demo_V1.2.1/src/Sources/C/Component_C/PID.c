#include"PID.h"
#include"global.h"
//��������
//�������


float kd=0.0;  //0.9
//float ek; //ƫ�� e[k]
static float ek1=0; //ƫ�� e[k-1]
//float ek2; //ƫ�� e[k-2]
static float adjust=0; //��������ĵ�����

int pidSteer(int ek)
{
  if((ek<0?-ek:ek)<EE) //ee Ϊ���ķ�ֵ��С�������ֵ��ʱ�򣬲��� PID ��������������СʱƵ�����������𵴡� ee ��ֵ���Լ���
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
