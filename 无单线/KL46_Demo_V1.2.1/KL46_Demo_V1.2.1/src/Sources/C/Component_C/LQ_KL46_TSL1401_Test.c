/********************************************************   
【平    台】龙丘KL46最小系统版
【编    写】龙丘
【Designed】by Chiu Sir
【E-mail  】chiusir@aliyun.com
【软件版本】V2.0
【最后更新】2013年12月24日
【相关信息参考下列地址】 
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
------------------------------------
使用北京龙邱智能科技cortex-M0开发工具箱
*********************************************************/
#include "common.h"
#include "includeS.h"
#include "includes.h"
#include "LQ_KL46_TSL1401_Test.h"
long evv=0;                   //申明变量，存放中间值
byte SD1[128]={0,0};          //声明数组，用于存放二值化赛道信息
float Threshold1=0;           //申明变量，存放阈值
/*************************************************************************
*                            LQ_1401CD_Test
*
*  函数名称：void LQ_CCD_Init(void)
*  功能说明：CCD初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2013-11-19
*  作者    ：龙丘
*************************************************************************/
void LQ_CCD_Init(void)
{
 CCD1_TSL_SI_Int;    //初始化CCD1 SI
 CCD1_TSL_SCK_Int;   //初始化CCD1 SCK
 CCD1_TSL_AO_Int;    //初始化CCD1 AO
 
}

/*************************************************************************
*                            LQ_1401CD_Test
*
*  函数名称：void Get_TSL1401(void)
*  功能说明：读取CCD数据
*  参数说明：无
*  函数返回：无
*  修改时间：2013-11-19
*  作者    ：龙丘
*************************************************************************/
void Get_TSL1401(void)
{
 
  
  byte i=0,tslp=0;
  CCD1_TSL_SCK_HIG;//起始电平高 
  CCD1_TSL_SI_LOW; //起始电平低
  Dly_us(); //合理的延时
      
  CCD1_TSL_SI_HIG; //上升沿
  CCD1_TSL_SCK_LOW;//下降沿
  Dly_us(); //合理延时
      
  CCD1_TSL_SCK_HIG;//上升沿
  CCD1_TSL_SI_LOW;//上升沿
  Dly_us(); //合理延时      
  for(i=0;i<64;i++)
  { 
    CCD1_TSL_SCK_LOW;//下降沿    
    Dly_us(); //合理延时
    Pixel[tslp]=CCD1_Pixe_Get;  //AD采集
    ++tslp;
    CCD1_TSL_SCK_HIG;//上升沿 
    Dly_us(); //合理延时    
  }
  for(i=0;i<64;i++)
  { 
    CCD1_TSL_SCK_LOW;//下降沿    
    Dly_us(); //合理延时
    Pixel[tslp]=CCD1_Pixe_Get;  //AD采集
    ++tslp;
    CCD1_TSL_SCK_HIG;//上升沿 
    Dly_us(); //合理延时    
  }    


}
/*************************************************************************
*                            LQ_1401CD_Test
*
*  函数名称：void Image(void) 
*  功能说明：赛道二值化以及赛道显示
*  参数说明：无
*  函数返回：无
*  修改时间：2013-11-19
*  作者    ：龙丘
*************************************************************************/
void Image(void) 
{
 u8 i=0;
 int tslp=0;
 for(i=0;i<128;i++)
  { 
    Threshold1+=Pixel[i];
   
  }
 Threshold1=Threshold1/128;   //求128个点的电压平均值
 Threshold1=Threshold1*0.8;   //求CCD1的阈值
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
