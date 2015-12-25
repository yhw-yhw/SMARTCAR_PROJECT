/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[adc.h] 
* ��  �� ��adc��س���
*��ƸĽ���Hyoga
*  Email ��498339494@qq.com
*�����£�2014-12-19
* ˵  �� ����ģ�������adc����
***********************************************************************
*/

#ifndef __ADC_H__
#define __ADC_H__


//��λ��bitfiled�Ѿ�����bitfiledֵ���Ǳ���ʾΪ��������ǵ�λ�á�
  
/************************* #Defines ******************************************/



#define A                 0x0
#define B                 0x1

typedef enum ADC_Ch
{
            //SC1n[DIFF]= 0
            //  -----ͨ��---------��Ӧ�˿�--       
  DAD0=0,   //	    ADC0_DP0	--PTE20 ����			                    
  DAD1=1,   //	    ADC0_DP1	--PTE16 ����			                    
  DAD2=2,   //	    ADC0_DP2	--PTE18 ����				            
  DAD3=3,   //	    ADC0_DP3	--PTE22 ����			                    

  //ADCx_CFG2[MUXSEL] λ���� ADCx_SEn ͨ��Ϊ a �� b.
  AD4a=4,   //	    ADC0_SE4a   --PTE21 ����					       
  AD5a=5,   //	    ADC0_SE5a   --PTE17 ����					       
  AD6a=6,   //	    ADC0_SE6a   --PTE19 ����					       
  AD7a=7,   //	    ADC0_SE7a   --PTE23 ����					       

  //Ҳ�� 4��5��6��7
//  AD4b=AD4a, //	    ADC0_SE4b	-- PTC2			                
//  AD5b=AD5a, //	    ADC0_SE5b	-- PTD1			                
 // AD6b=AD6a, //	    ADC0_SE6b	-- PTD5			                
//  AD7b=AD7a, //	    ADC0_SE7b	-- PTD6		

  AD8=8,    //	    ADC0_SE8  	-- PTB0	//����	
  AD9=9,    //	    ADC0_SE9  	-- PTB1	 //����		  
  AD10=10,  //	    ADC0_SE10 	-- PTA7	 //������		    
  AD11=11,  //	    ADC0_SE11 	-- PTC2	 //����		          
  AD12=12,  //	    ADC0_SE12 	-- PTB2	 //����		              
  AD13=13,  //	    ADC0_SE13 	-- PTB3	 //�����û�����ˣ�ǰ��Ļ����������ܳ�����ȫ������		              
  AD14=14,  //	    ADC0_SE14 	-- PTC0	 			                
  AD15=15,  //	    ADC0_SE15 	-- PTC1		                
  AD16=16,  //	    ADC0_SE16	36������	 		        
  AD17=17,  //	    ADC0_SE17 	-- PTE24		                
  AD18=18,  //	    ADC0_SE18 	-- PTE25		                
  AD19=19,  //	    ADC0_DM0				                    
  AD20=20,  //	    ADC0_DM1				                    
  AD21=21,  //				        	                        
  AD22=22,  //				
  AD23=23,  //	    DAC0_OUT(12-bit) -- DAC0_OUT		       
  AD24=24,  //	    ����					
  AD25=25,  //	    ����					
  AD26=26,  //	    Temperature Sensor (S.E)		            
  AD27=27,  //	    Bandgap (S.E)				                
  AD28=28,  //	    ����					                    
  AD29=29,  //	    VREFH (S.E)				                    
  AD30=30,  //	    VREFL					                    
  AD31=31   //	    ����ADC0				                    
}ADC_Ch;


//����λ��
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;


/////// ע�⣺����Ķ�����ADC�Ĵ����Ķ�������ݵĲο��ֲᣬʹ����ͬ�ķ��š�


//// ADCSC1 (�Ĵ���)

//   ת�����(COCO) ��־λ
#define COCO_COMPLETE     ADC_SC1_COCO_MASK
#define COCO_NOT          0x00

// ADC�ж�ʹ��
#define AIEN_ON           ADC_SC1_AIEN_MASK
#define AIEN_OFF          0x00

// ��ֻ򵥶�����
#define DIFF_SINGLE       0x00
#define DIFF_DIFFERENTIAL ADC_SC1_DIFF_MASK

//// ADCCFG1

//  ADC��Դ����
#define ADLPC_LOW         ADC_CFG1_ADLPC_MASK
#define ADLPC_NORMAL      0x00

// ʱ�ӷ�Ƶ
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

// ������ʱ�䣬�̶�ʱ�����
#define ADLSMP_LONG       ADC_CFG1_ADLSMP_MASK
#define ADLSMP_SHORT      0x00

// תΪλ��
#define MODE_8            0x00
#define MODE_12           0x01
#define MODE_10           0x02
#define MODE_16           0x03

// ADCʱ��ѡ������ʱ�ӣ�����ʱ�ӵ�һ��, "altclk",ADC���첽ʱ�ӵĵ�����
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

//// ADCCFG2

//ѡ��ADC��ABͨ��
#define MUXSEL_ADCB       ADC_CFG2_MUXSEL_MASK
#define MUXSEL_ADCA       0x00

//ͬ��ʱ��������ã����û���ã��������
#define ADACKEN_ENABLED   ADC_CFG2_ADACKEN_MASK
#define ADACKEN_DISABLED  0x00

// ���ٻ����ת��ѡ��
#define ADHSC_HISPEED     ADC_CFG2_ADHSC_MASK
#define ADHSC_NORMAL      0x00

// ���Ĳ���ʱ��ѡ��20��12��6����2�������ʱ��һ���ϳ��Ĳ���ʱ��
#define ADLSTS_20          0x00
#define ADLSTS_12          0x01
#define ADLSTS_6           0x02
#define ADLSTS_2           0x03

////ADCSC2

// ֻ��״̬λָʾת��״̬
#define ADACT_ACTIVE       ADC_SC2_ADACT_MASK
#define ADACT_INACTIVE     0x00

// ��ʼת��������Ӳ�������������������ʹ��PDB��Ӳ������ѡ�
#define ADTRG_HW           ADC_SC2_ADTRG_MASK
#define ADTRG_SW           0x00

// ADC�ȽϹ���ѡ��ʹ�ܻ��ֹ
#define ACFE_DISABLED      0x00
#define ACFE_ENABLED       ADC_SC2_ACFE_MASK

//�ȽϹ��ܴ���ʹ������ģ��򲻡�
#define ACFGT_GREATER      ADC_SC2_ACFGT_MASK
#define ACFGT_LESS         0x00

// �ȽϹ��ܷ�Χ���ã����û���á�
#define ACREN_ENABLED      ADC_SC2_ACREN_MASK
#define ACREN_DISABLED     0x00

// DMAʹ��ѡ��
#define DMAEN_ENABLED      ADC_SC2_DMAEN_MASK
#define DMAEN_DISABLED     0x00

// ��ADCת���Ĳο���ѹ��ѡ��* * *��* * PGA����vrefoֻ������ѹ��VREFL��0������vrefo��1����

#define REFSEL_EXT         0x00
#define REFSEL_ALT         0x01
#define REFSEL_RES         0x02     /* reserved */
#define REFSEL_RES_EXT     0x03     /* reserved but defaults to Vref */

////ADCSC3

// У׼��ʼ��ر�
#define CAL_BEGIN          ADC_SC3_CAL_MASK
#define CAL_OFF            0x00

// ״ָ̬ʾУ��ʧ�ܣ��������ĳɹ�
#define CALF_FAIL          ADC_SC3_CALF_MASK
#define CALF_NORMAL        0x00

// ADC�Ĳ���ת��������һ����ת��
#define ADCO_CONTINUOUS    ADC_SC3_ADCO_MASK
#define ADCO_SINGLE        0x00

// Averaging enabled in the ADC, or not.
#define AVGE_ENABLED       ADC_SC3_AVGE_MASK
#define AVGE_DISABLED      0x00

// ����ƽ��֮ǰ��ϵ�Ƭ����4��8��16����32
#define AVGS_4             0x00
#define AVGS_8             0x01
#define AVGS_16            0x02
#define AVGS_32            0x03

////PGA

// PGA���û򲻣�
#define PGAEN_ENABLED      ADC_PGA_PGAEN_MASK
#define PGAEN_DISABLED     0x00 

// �÷Ŵ���ն���ȶ����򲻡�
#define PGACHP_CHOP        ADC_PGA_PGACHP_MASK 
#define PGACHP_NOCHOP      0x00

// PGA�͹���ģʽ����ͨģʽ
#define PGALP_LOW          ADC_PGA_PGALP_MASK
#define PGALP_NORMAL       0x00

// PGA������ѡ��Χ1��64
#define PGAG_1             0x00
#define PGAG_2             0x01
#define PGAG_4             0x02
#define PGAG_8             0x03
#define PGAG_16            0x04
#define PGAG_32            0x05
#define PGAG_64            0x06

//������ֵ��ϵ�����Ľṹѡ���ADC / PGA��������ģ�

typedef struct adc_cfg {
  uint8_t  CONFIG1; 
  uint8_t  CONFIG2; 
  uint16_t COMPARE1; 
  uint16_t COMPARE2; 
  uint8_t  STATUS2;
  uint8_t  STATUS3; 
  uint8_t  STATUS1A; 
  uint8_t  STATUS1B;
  uint32_t PGA;
  } *tADC_ConfigPtr, tADC_Config ;  
  

#define CAL_BLK_NUMREC 18 

typedef struct adc_cal {
 
uint16_t  OFS;
uint16_t  PG;
uint16_t  MG;
uint8_t   CLPD;
uint8_t   CLPS;
uint16_t  CLP4;
uint16_t  CLP3;
uint8_t   CLP2;
uint8_t   CLP1;
uint8_t   CLP0;
uint8_t   dummy;
uint8_t   CLMD;
uint8_t   CLMS;
uint16_t  CLM4;
uint16_t  CLM3;
uint8_t   CLM2;
uint8_t   CLM1;
uint8_t   CLM0;
} tADC_Cal_Blk ;  





uint8_t ADC_Cal(ADC_MemMapPtr);
void ADC_Config_Alt(ADC_MemMapPtr, tADC_ConfigPtr);
void ADC_Read_Cal(ADC_MemMapPtr, tADC_Cal_Blk *);
void ADC0_isrv(void);

void adc_init(ADC_Ch ch);
u16 ad_once(ADC_Ch adc_channel,ADC_nbit bit);

#endif /* __ADC_H__ */
