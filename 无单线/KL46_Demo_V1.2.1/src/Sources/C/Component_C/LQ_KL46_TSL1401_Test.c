/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@aliyun.com
������汾��V2.0
�������¡�2013��12��24��
�������Ϣ�ο����е�ַ�� 
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
------------------------------------
ʹ�ñ����������ܿƼ�cortex-M0����������
*********************************************************/
#include "common.h"
#include "includeS.h"
#include "includes.h"
#include "LQ_KL46_TSL1401_Test.h"
long evv=0;                   //��������������м�ֵ
byte SD1[128]={0,0};          //�������飬���ڴ�Ŷ�ֵ��������Ϣ
float Threshold1=0;           //���������������ֵ
/*************************************************************************
*                            LQ_1401CD_Test
*
*  �������ƣ�void LQ_CCD_Init(void)
*  ����˵����CCD��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2013-11-19
*  ����    ������
*************************************************************************/
void LQ_CCD_Init(void)
{
 CCD1_TSL_SI_Int;    //��ʼ��CCD1 SI
 CCD1_TSL_SCK_Int;   //��ʼ��CCD1 SCK
 CCD1_TSL_AO_Int;    //��ʼ��CCD1 AO
 
}

/*************************************************************************
*                            LQ_1401CD_Test
*
*  �������ƣ�void Get_TSL1401(void)
*  ����˵������ȡCCD����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2013-11-19
*  ����    ������
*************************************************************************/
void Get_TSL1401(void)
{
 
  
  byte i=0,tslp=0;
  CCD1_TSL_SCK_HIG;//��ʼ��ƽ�� 
  CCD1_TSL_SI_LOW; //��ʼ��ƽ��
  Dly_us(); //�������ʱ
      
  CCD1_TSL_SI_HIG; //������
  CCD1_TSL_SCK_LOW;//�½���
  Dly_us(); //������ʱ
      
  CCD1_TSL_SCK_HIG;//������
  CCD1_TSL_SI_LOW;//������
  Dly_us(); //������ʱ      
  for(i=0;i<64;i++)
  { 
    CCD1_TSL_SCK_LOW;//�½���    
    Dly_us(); //������ʱ
    Pixel[tslp]=CCD1_Pixe_Get;  //AD�ɼ�
    ++tslp;
    CCD1_TSL_SCK_HIG;//������ 
    Dly_us(); //������ʱ    
  }
  for(i=0;i<64;i++)
  { 
    CCD1_TSL_SCK_LOW;//�½���    
    Dly_us(); //������ʱ
    Pixel[tslp]=CCD1_Pixe_Get;  //AD�ɼ�
    ++tslp;
    CCD1_TSL_SCK_HIG;//������ 
    Dly_us(); //������ʱ    
  }    


}
/*************************************************************************
*                            LQ_1401CD_Test
*
*  �������ƣ�void Image(void) 
*  ����˵����������ֵ���Լ�������ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2013-11-19
*  ����    ������
*************************************************************************/
void Image(void) 
{
 u8 i=0;
 int tslp=0;
 for(i=0;i<128;i++)
  { 
    Threshold1+=Pixel[i];
   
  }
 Threshold1=Threshold1/128;   //��128����ĵ�ѹƽ��ֵ
 Threshold1=Threshold1*0.8;   //��CCD1����ֵ
  for(i=0;i<128;i++)
  { 
    if(Pixel[i]<Threshold1) SD1[i]=0;
    else                        SD1[i]=1;
  }
   LCD_Set_Pos(0,7);    
  for(i=0;i<128;i++)
  {
    if(SD1[i]==0)  tslp=0xfe;        
    else tslp=0x80;      
    LCD_WrDat(tslp);           
  }
  
}


void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<200;ii++); //32M     
}
