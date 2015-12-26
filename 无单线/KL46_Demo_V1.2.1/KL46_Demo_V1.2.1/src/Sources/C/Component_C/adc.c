/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[adc.c] 
* ��  �� ��adc��س���
*��ƸĽ���Hyoga
*  Email ��498339494@qq.com
*�����£�2014-12-19
* ˵  �� ����ģ�������adc����
***********************************************************************
*/

#include "common.h"
#include "adc.h"


tADC_Config  Master_Adc_Config;  
uint16 adc_isrv_result;

/******************************************************************************
��������	CAL ROUTINE   

����		ADCģ��ָ��ָ��ADC0��ADC1�Ĵ���ӳ���ַ��
����ֵ		�������ʾ��ʼ���ɹ�.
��ע         	У׼adc16����Ҫ��λ��ﵽ�淶������֮ǰ��ת����
******************************************************************************/
uint8 ADC_Cal(ADC_MemMapPtr adcmap)
{

  unsigned short cal_var;
  
  ADC_SC2_REG(adcmap) &=  ~ADC_SC2_ADTRG_MASK ; // ʹ��У׼���̵����ת������    - ADC0_SC2 = ADC0_SC2 | ADC_SC2_ADTRGW(0);   
  ADC_SC3_REG(adcmap) &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); // ��ת���������ƽ����λ��д��
  ADC_SC3_REG(adcmap) |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32) );  // ��ƽ�������������ֵ��32��
  
  
  ADC_SC3_REG(adcmap) |= ADC_SC3_CAL_MASK ;      // ����У׼
  while ( (ADC_SC1_REG(adcmap,A) & ADC_SC1_COCO_MASK ) == COCO_NOT ); // �ȴ�У׼���
  	
  if ((ADC_SC3_REG(adcmap)& ADC_SC3_CALF_MASK) == CALF_FAIL )
  {  
   return(1);    // Check for Calibration fail error and return 
  }
  // Calculate plus-side calibration
  cal_var = 0x00;
  
  cal_var =  ADC_CLP0_REG(adcmap); 
  cal_var += ADC_CLP1_REG(adcmap);
  cal_var += ADC_CLP2_REG(adcmap);
  cal_var += ADC_CLP3_REG(adcmap);
  cal_var += ADC_CLP4_REG(adcmap);
  cal_var += ADC_CLPS_REG(adcmap);

  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB

  ADC_PG_REG(adcmap) = ADC_PG_PG(cal_var);
 

  // Calculate minus-side calibration
  cal_var = 0x00;

  cal_var =  ADC_CLM0_REG(adcmap); 
  cal_var += ADC_CLM1_REG(adcmap);
  cal_var += ADC_CLM2_REG(adcmap);
  cal_var += ADC_CLM3_REG(adcmap);
  cal_var += ADC_CLM4_REG(adcmap);
  cal_var += ADC_CLMS_REG(adcmap);

  cal_var = cal_var/2;

  cal_var |= 0x8000; // Set MSB

  ADC_MG_REG(adcmap) = ADC_MG_MG(cal_var); 
  
  ADC_SC3_REG(adcmap) &= ~ADC_SC3_CAL_MASK ; /* Clear CAL bit */

  return(0);
}
/******************************************************************************
��������          	ADC_Config_Alt 
����     		�Ĵ�����ֵ��������һ���ṹ�е�ADC
����ֵ    		��
��ע         		����ADC0��ADC1ȡ����adcmap��������������ṹԪ�������ADC����֮ǰ��
******************************************************************************/
void ADC_Config_Alt(ADC_MemMapPtr adcmap, tADC_ConfigPtr ADC_CfgPtr)
{
 ADC_CFG1_REG(adcmap) = ADC_CfgPtr->CONFIG1;
 ADC_CFG2_REG(adcmap) = ADC_CfgPtr->CONFIG2;
 ADC_CV1_REG(adcmap)  = ADC_CfgPtr->COMPARE1; 
 ADC_CV2_REG(adcmap)  = ADC_CfgPtr->COMPARE2;
 ADC_SC2_REG(adcmap)  = ADC_CfgPtr->STATUS2;
 ADC_SC3_REG(adcmap)  = ADC_CfgPtr->STATUS3;
 //ADC_PGA_REG(adcmap)  = ADC_CfgPtr->PGA;  pbd
 ADC_SC1_REG(adcmap,A)= ADC_CfgPtr->STATUS1A;       
 ADC_SC1_REG(adcmap,B)= ADC_CfgPtr->STATUS1B;
}


void ADC_Read_Cal(ADC_MemMapPtr adcmap, tADC_Cal_Blk *blk)
{
  blk->OFS  = ADC_OFS_REG(adcmap);
  blk->PG   = ADC_PG_REG(adcmap); 
  blk->MG   = ADC_MG_REG(adcmap); 
  blk->CLPD = ADC_CLPD_REG(adcmap); 
  blk->CLPS = ADC_CLPS_REG(adcmap); 
  blk->CLP4 = ADC_CLP4_REG(adcmap);
  blk->CLP3 = ADC_CLP3_REG(adcmap); 
  blk->CLP2 = ADC_CLP2_REG(adcmap); 
  blk->CLP1 = ADC_CLP1_REG(adcmap);
  blk->CLP0 = ADC_CLP0_REG(adcmap);
  blk->CLMD = ADC_CLMD_REG(adcmap); 
  blk->CLMS = ADC_CLMS_REG(adcmap); 
  blk->CLM4 = ADC_CLM4_REG(adcmap);
  blk->CLM3 = ADC_CLM3_REG(adcmap); 
  blk->CLM2 = ADC_CLM2_REG(adcmap); 
  blk->CLM1 = ADC_CLM1_REG(adcmap);
  blk->CLM0 = ADC_CLM0_REG(adcmap);
  
}


/*************************************************************************
*  �����ʵ��ѧKL46����
*  �������ƣ�adc_init
*  ����˵����AD��ʼ��
*  ����˵����ADC_nbit  AD�������ȣ�  ADC_Ch  ģ���
*  �������أ���
*  ��ע��
*************************************************************************/
void adc_init(ADC_Ch ch)
{
    // Turn on the ADC0 clock 
        SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );
        SIM_SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK  | SIM_SOPT7_ADC0PRETRGSEL_MASK);
        SIM_SOPT7 = SIM_SOPT7_ADC0TRGSEL(0);
        
        switch(ch)
        {
        case AD8:   //ADC0_SE8 -- PTB0
        case AD9:   //ADC0_SE9 -- PTB1
            SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
            PORT_PCR_REG(PORTB_BASE_PTR, ch-AD8+0) =  PORT_PCR_MUX(0);
            break;
        case AD10:  //ADC0_SE10 -- PTA7
        case AD11:  //ADC0_SE11 -- PTA8
            SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
            PORT_PCR_REG(PORTA_BASE_PTR, ch-AD10+7) =  PORT_PCR_MUX(0);
            break;
        case AD12:  //ADC0_SE12 -- PTB2
        case AD13:  //ADC0_SE13 -- PTB3
            SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
            PORT_PCR_REG(PORTB_BASE_PTR, ch-AD12+2) =  PORT_PCR_MUX(0);
            break;
        case AD14:  //ADC0_SE14 -- PTC0
        case AD15:  //ADC0_SE15 -- PTC1
            SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
            PORT_PCR_REG(PORTC_BASE_PTR, ch-AD14+0) =  PORT_PCR_MUX(0);
            break;
        case AD17:   //ADC0_SE17 -- PTE24
        case AD18:   //ADC0_SE17 -- PTE25
            SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
            PORT_PCR_REG(PORTE_BASE_PTR, ch-AD17+24) =  PORT_PCR_MUX(0);
            break;
        default:
            break;
        }
        
        
            Master_Adc_Config.CONFIG2  = MUXSEL_ADCA   //A for FREEDOM
              | ADACKEN_DISABLED
              | ADHSC_HISPEED
              | ADC_CFG2_ADLSTS(ADLSTS_6) ;
          
            
            
            
            
            Master_Adc_Config.COMPARE1 = 0x1234u ;                 // can be anything
            Master_Adc_Config.COMPARE2 = 0x5678u ;                 // can be anything
            // since not using
            // compare feature
            Master_Adc_Config.STATUS2  = ADTRG_SW
              | ACFE_DISABLED
              | ACFGT_GREATER
              | ACREN_DISABLED
              | DMAEN_DISABLED
              | ADC_SC2_REFSEL(REFSEL_EXT);
            
            Master_Adc_Config.STATUS3  = CAL_OFF
              | ADCO_SINGLE
              | !AVGE_ENABLED
              | ADC_SC3_AVGS(AVGS_4);
            
            Master_Adc_Config.STATUS1A = !AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(ch);
              
            // Configure ADC as it will be used, but becuase ADC_SC1_ADCH is 31,
            // the ADC will be inactive.  Channel 31 is just disable function.
            // There really is no channel 31.
            
            ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc_Config);  // config ADC
              
            
            // Calibrate the ADC in the configuration in which it will be used:
            ADC_Cal(ADC0_BASE_PTR);                    // do the calibration
            
            // The structure still has the desired configuration.  So restore it.
            // Why restore it?  The calibration makes some adjustments to the
            // configuration of the ADC.  They are now undone:
            
            // config the ADC again to desired conditions
            ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc_Config);
        return;
}


/* 
    adc simple read   read a single channel as a configured in 
    Sigle mode, no interruptions
    Note: before run this function make sure init_ADC16 has been executed
*/
/*************************************************************************
*  �����ʵ��ѧKL46����
*  �������ƣ�ad_once
*  ����˵�����ɼ�һ��һ·ģ������ADֵ
*  ����˵����ADC_Ch    ģ���       
*  �������أ��޷��Ž��ֵ
*  ���ߣ�
*************************************************************************/
u16 ad_once(ADC_Ch adc_channel,ADC_nbit bit)
{
    
    
    Master_Adc_Config.CONFIG1  = ADLPC_NORMAL
                                 | ADC_CFG1_ADIV(ADIV_4)
                                 | ADLSMP_LONG
                                 | ADC_CFG1_MODE(bit)
                                 | ADC_CFG1_ADICLK(ADICLK_BUS);
    Master_Adc_Config.CONFIG2  = MUXSEL_ADCA    //MUXSEL_ADCA
                                 | ADACKEN_DISABLED
                                 | ADHSC_HISPEED
                                 | ADC_CFG2_ADLSTS(ADLSTS_20) ;

    Master_Adc_Config.COMPARE1 = 0x1234u ;                 //����ֵ
    Master_Adc_Config.COMPARE2 = 0x5678u ;                 //����ֵ

    ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc_Config);       // ���� ADCn
    
    
    
    ADC0_SC1A = !AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(adc_channel);  // start conversion
    
   
    while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)){};                        // wait for conversion complete 
    return ADC0_RA;
}
                            

void ADC0_isrv(void)
{
  if (ADC0_SC1A & ADC_SC1_COCO_MASK)
  {
    adc_isrv_result = ADC0_RA;
  }

}


