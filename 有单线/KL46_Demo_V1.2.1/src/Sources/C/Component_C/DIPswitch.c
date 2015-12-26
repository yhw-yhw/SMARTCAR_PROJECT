
/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[DIPswitch.c] 
* ��  �� �����뿪��
* ˵  �� �����뿪�� ��������
***********************************************************************
*/

#include  "DIPswitch.h"


/*************************************************************************
*  �������ƣ�DIPswitch_init
*  ����˵������ʼ�����뿪�ض˿ڣ�����IO��Ϊ���뷽��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-10-03   
*  ��    ע��
*************************************************************************/
void    DIPswitch_init(void)
{
    gpio_init(DIPswitch_PORT,DIP0,GPI,0);
    gpio_init(DIPswitch_PORT,DIP1,GPI,0);
    gpio_init(DIPswitch_PORT,DIP2,GPI,0);
    gpio_init(DIPswitch_PORT,DIP3,GPI,0);
}


/*************************************************************************
*  �������ƣ�DIPswitch_val
*  ����˵�����õ����뿪�ص�ֵ
*  ����˵������
*  �������أ����뿪�ص�ֵ
*  �޸�ʱ�䣺2014-10-03 
*  ��    ע��
*************************************************************************/
u8 DIPswitch_val()
{
    u8 val = 0;
    val |= gpio_get(DIPswitch_PORT,DIP3) << 3;
    val |= gpio_get(DIPswitch_PORT,DIP2) << 2;
    val |= gpio_get(DIPswitch_PORT,DIP1) << 1;
    val |= gpio_get(DIPswitch_PORT,DIP0) << 0;                     
#if DIPVAL == 0                     
    return val;
#else
    return ((~val)&0x0F);  //ȡ��
#endif
}
/*************************************************************************
*  �������ƣ�DIPswitch_valbit
*  ����˵�����õ����뿪�ص�ֵĳһ��λ��ֵ
*  ����˵������
*  �������أ����뿪�ص�ֵ
*  �޸�ʱ�䣺2014-10-03 
*  ��    ע��
*           �ò��뿪�ؿ������ò�ͬ����������������������ö����λ���ٶ�
*************************************************************************/
u8 DIPswitch_valbit(DIPn dipn)
{
#if DIPVAL == 0    
  return gpio_get(DIPswitch_PORT,dipn);
#else
  return (gpio_get(DIPswitch_PORT,dipn)^1);
#endif
}
                    
                    
/*************************************************************************
*  �������ƣ�DIPswitch_Ctrl
*  ����˵�������뿪�ؿ��Ƴ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-10-03 
*  ��    ע��������뿪�غ���ϣ����ֵ�Ƿ��࣬���԰Ѻ궨�� DIPVAL ȡ��
*************************************************************************/
u8 DIPswitch_ctrl(void)
{
   //�����������Ҫ����ѡ�����õı���
   switch(DIPswitch_val())
   {
   case 0x00:
     uartPrintf("yout choice is : 0\n");
     break;
   case 0x01:
     uartPrintf("yout choice is : 1\n");
     break;
   case 0x02:
     uartPrintf("yout choice is : 2\n");
     break;
   case 0x03:
     uartPrintf("yout choice is : 3\n");
     break;
     
   case 0x04:
     uartPrintf("yout choice is : 4\n");
     break;
   case 0x05:
     uartPrintf("yout choice is : 5\n");
     break;
   case 0x06:
     uartPrintf("yout choice is : 6\n");
     break;
   case 0x07:
     uartPrintf("yout choice is : 7\n");
     break;
     
   case 0x08:
     uartPrintf("yout choice is : 8\n");
     break;
   case 0x09:
     uartPrintf("yout choice is : 9\n");
     break;
   case 0x0A:
     uartPrintf("yout choice is : A\n");
     break;
   case 0x0B:
     uartPrintf("yout choice is : B\n");
     break;
     
   case 0x0C:
     uartPrintf("yout choice is : C\n");
     break;
   case 0x0D:
     uartPrintf("yout choice is : D\n");
     break;
   case 0x0E:
     uartPrintf("yout choice is : E\n");
     break;
   case 0x0F:
     uartPrintf("yout choice is : F\n");
     break;
   default:
     uartPrintf("yout choice is : Other\n");
     break;
   }
   
   uartPrintf("������뿪�غ���ϣ����ֵ�Ƿ��࣬���԰Ѻ궨�� DIPVAL ȡ��\n");
   return DIPswitch_val();
}