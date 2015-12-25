/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[CCD.c] 
* ��  �� ��CCD��س���
* ԭ��   ��Ұ��Ƕ��ʽ����������
*��ƸĽ���Hyoga
*  Email ��498339494@qq.com
*�����£�2014-03-30
* ˵  �� ����ģ�������CCD����
***********************************************************************
*/
#include "CCD.h"
/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�CCD_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�StartIntegration_Front  // StartIntegration_Back 
*  ����˵����CCD��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�ImageCapture_Front // ImageCapture_Back
*  ����˵����CCD����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�CalculateIntegrationTime
*  ����˵���������ع�ʱ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
		if(cnt==0)continue;//�Ż�����
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
		if(count>=118)break;//�Ż����� 122-5+1
	}
	return tr;
}

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�PixelAverage
*  ����˵����������ľ�ֵ����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�SendHex
*  ����˵�����ɼ���������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ��ѿ����
*
*  �������ƣ�SendHexPID
*  ����˵�������͵�����������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�SendImageData
*  ����˵����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
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
*                           ������ӹ�����
*
*  �������ƣ�SamplingDelay
*  ����˵����CCD��ʱ���� 200ns
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void SamplingDelay(void)
{
    
}





