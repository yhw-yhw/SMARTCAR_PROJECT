/*
************************************************************************
*                北京邮电大学 KL46 学习例程                                        
* 文件名 :[CCD.c] 
* 描  述 ：CCD相关程序
* 原创   ：野火嵌入式开发工作室
*设计改进：Hyoga
*  Email ：498339494@qq.com
*最后更新：2014-03-30
* 说  明 ：本模块包含：CCD驱动
***********************************************************************
*/
#include "CCD.h"
/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：CCD_init
*  功能说明：CCD初始化
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void CCD_init(void)
{
  //front
  gpio_init (PORTE , 4, GPO,HIGH);
  gpio_init (PORTE , 5, GPO,HIGH);
  adc_init(AO_Front) ;
  //back
 // gpio_init (PORTB , 22, GPO,HIGH);
 // gpio_init (PORTB , 23, GPO,HIGH);
 // adc_init(ADC_8bit, AO_Back) ;
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：StartIntegration_Front  // StartIntegration_Back 
*  功能说明：CCD启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void StartIntegration_Front(void) {

    unsigned char i;

    SI_SetVal_Front();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal_Front();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal_Front();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal_Front();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal_Front();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal_Front();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal_Front();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal_Front();           /* CLK = 0 */
}

void StartIntegration_Back(void) {

    unsigned char i;

    SI_SetVal_Back();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal_Back();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal_Back();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal_Back();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal_Back();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal_Back();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal_Back();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal_Back();           /* CLK = 0 */
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：ImageCapture_Front // ImageCapture_Back
*  功能说明：CCD采样
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture_Front(u8 * ImageData) {
   
    unsigned char i;
   // extern u8 AtemP ;

    SI_SetVal_Front();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal_Front();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal_Front();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
  
    for(i = 0; i < 50; i++) {
      SamplingDelay() ;  //200ns
    }

    //Sampling Pixel 1
   
    *ImageData =  ad_once( AO_Front,ADC_8bit);
   
    ImageData ++ ;
    CLK_ClrVal_Front();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal_Front();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
       
       *ImageData = ad_once(AO_Front,ADC_8bit);
      // uartPrintf("%d  |",*ImageData);
   /*  *ImageData = (unsigned char)ad_once(ADC1, AD6a, ADC_8bit);
        */
        ImageData++ ;
        CLK_ClrVal_Front();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal_Front();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal_Front();           /* CLK = 0 */
}

void ImageCapture_Back(unsigned char * ImageData) {
   
    unsigned char i;
   // extern u8 AtemP ;

    SI_SetVal_Back();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal_Back();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal_Back();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 50; i++) {
      SamplingDelay() ;  //200ns
    }

    //Sampling Pixel 1
   
    *ImageData =  ad_once( AO_Back,ADC_8bit);
   
     /*  uartPrintf("%d",*ImageData);
    uartPrintf("%c",*ImageData);
     *ImageData = (unsigned char)ad_once(ADC1, AD6a, ADC_8bit);
        */
    ImageData ++ ;
    CLK_ClrVal_Back();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal_Back();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
       
       *ImageData = ad_once(AO_Back,ADC_8bit);
      // uartPrintf("%d  |",*ImageData);
   /*  *ImageData = (unsigned char)ad_once(ADC1, AD6a, ADC_8bit);
        */
        ImageData++ ;
        CLK_ClrVal_Back();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal_Back();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal_Back();           /* CLK = 0 */
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CalculateIntegrationTime
*  功能说明：计算曝光时间
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
u8 otsu(u8 *p)
{       
	u32 g,max=0;
	u16 total=0,total_low=0;
	u8 u0=0,u1=0,count=0,tr=0,cnt=0;
	u8 pc[256]={0};
	u8 j;
	for(j=5;j<=122;j++)
	{
		pc[*(p+j)]++;
		total+=*(p+j);
	}
	for(j=0;j<=254;j++)
	{
		cnt=pc[j];
		if(cnt==0)continue;//优化加速
		count+=pc[j];
		total_low+=cnt*j;
		u0=total_low/count;
		u1=(total-total_low)/(118-count);
		g=((u32)(u0-u1)*(u0-u1))*((count*(118-count)))/16384;
		if(g>max)
		{
			max=g;
			tr=j;
		}
		if(count>=118)break;//优化加速 122-5+1
	}
	return tr;
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：PixelAverage
*  功能说明：求数组的均值程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/

u8 PixelAverage(u8 len, u8 *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
    uart_putchar(UART0,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
   uart_putchar(UART0,temp - 10 + 'A');
  }
}
/*************************************************************************
*                           豆芽电子
*
*  函数名称：SendHexPID
*  功能说明：发送单个测速数据
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHexPID(s16 hex)
{
  char temp;
  temp=hex>>8;
  if(temp==0xFF||temp==0xFD)temp=temp-1;
  uart_putchar(UART0,temp);
  temp=hex & 0x00FF;
  if(temp==0xFF||temp==0xFD)temp=temp-1;
  uart_putchar(UART0,temp);
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(UART0,'*');
    uart_putchar(UART0,'L');
    uart_putchar(UART0,'D');
    SendHex(0);
    SendHex(132);
    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(UART0,'#');
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SamplingDelay
*  功能说明：CCD延时程序 200ns
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SamplingDelay(void)
{
    
}





