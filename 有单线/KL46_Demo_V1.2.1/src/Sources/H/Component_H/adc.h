/*
************************************************************************
*                北京邮电大学 KL46 学习例程                                        
* 文件名 :[adc.h] 
* 描  述 ：adc相关程序
*设计改进：Hyoga
*  Email ：498339494@qq.com
*最后更新：2014-12-19
* 说  明 ：本模块包含：adc驱动
***********************************************************************
*/

#ifndef __ADC_H__
#define __ADC_H__


//移位的bitfiled已经考虑bitfiled值总是被表示为相对于他们的位置。
  
/************************* #Defines ******************************************/



#define A                 0x0
#define B                 0x1

typedef enum ADC_Ch
{
            //SC1n[DIFF]= 0
            //  -----通道---------对应端口--       
  DAD0=0,   //	    ADC0_DP0	--PTE20 可用			                    
  DAD1=1,   //	    ADC0_DP1	--PTE16 可用			                    
  DAD2=2,   //	    ADC0_DP2	--PTE18 可用				            
  DAD3=3,   //	    ADC0_DP3	--PTE22 可用			                    

  //ADCx_CFG2[MUXSEL] 位决定 ADCx_SEn 通道为 a 或 b.
  AD4a=4,   //	    ADC0_SE4a   --PTE21 可用					       
  AD5a=5,   //	    ADC0_SE5a   --PTE17 可用					       
  AD6a=6,   //	    ADC0_SE6a   --PTE19 可用					       
  AD7a=7,   //	    ADC0_SE7a   --PTE23 可用					       

  //也是 4、5、6、7
//  AD4b=AD4a, //	    ADC0_SE4b	-- PTC2			                
//  AD5b=AD5a, //	    ADC0_SE5b	-- PTD1			                
 // AD6b=AD6a, //	    ADC0_SE6b	-- PTD5			                
//  AD7b=AD7a, //	    ADC0_SE7b	-- PTD6		

  AD8=8,    //	    ADC0_SE8  	-- PTB0	//可用	
  AD9=9,    //	    ADC0_SE9  	-- PTB1	 //可用		  
  AD10=10,  //	    ADC0_SE10 	-- PTA7	 //不可用		    
  AD11=11,  //	    ADC0_SE11 	-- PTC2	 //可用		          
  AD12=12,  //	    ADC0_SE12 	-- PTB2	 //可用		              
  AD13=13,  //	    ADC0_SE13 	-- PTB3	 //后面的没测试了，前面的基本上在智能车里完全够用了		              
  AD14=14,  //	    ADC0_SE14 	-- PTC0	 			                
  AD15=15,  //	    ADC0_SE15 	-- PTC1		                
  AD16=16,  //	    ADC0_SE16	36号引脚	 		        
  AD17=17,  //	    ADC0_SE17 	-- PTE24		                
  AD18=18,  //	    ADC0_SE18 	-- PTE25		                
  AD19=19,  //	    ADC0_DM0				                    
  AD20=20,  //	    ADC0_DM1				                    
  AD21=21,  //				        	                        
  AD22=22,  //				
  AD23=23,  //	    DAC0_OUT(12-bit) -- DAC0_OUT		       
  AD24=24,  //	    保留					
  AD25=25,  //	    保留					
  AD26=26,  //	    Temperature Sensor (S.E)		            
  AD27=27,  //	    Bandgap (S.E)				                
  AD28=28,  //	    保留					                    
  AD29=29,  //	    VREFH (S.E)				                    
  AD30=30,  //	    VREFL					                    
  AD31=31   //	    禁用ADC0				                    
}ADC_Ch;


//精度位数
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;


/////// 注意：下面的定义与ADC寄存器的定义和内容的参考手册，使用相同的符号。


//// ADCSC1 (寄存器)

//   转换完成(COCO) 标志位
#define COCO_COMPLETE     ADC_SC1_COCO_MASK
#define COCO_NOT          0x00

// ADC中断使能
#define AIEN_ON           ADC_SC1_AIEN_MASK
#define AIEN_OFF          0x00

// 差分或单端输入
#define DIFF_SINGLE       0x00
#define DIFF_DIFFERENTIAL ADC_SC1_DIFF_MASK

//// ADCCFG1

//  ADC电源设置
#define ADLPC_LOW         ADC_CFG1_ADLPC_MASK
#define ADLPC_NORMAL      0x00

// 时钟分频
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

// 长采样时间，短短时间采样
#define ADLSMP_LONG       ADC_CFG1_ADLSMP_MASK
#define ADLSMP_SHORT      0x00

// 转为位数
#define MODE_8            0x00
#define MODE_12           0x01
#define MODE_10           0x02
#define MODE_16           0x03

// ADC时钟选择总线时钟，总线时钟的一半, "altclk",ADC的异步时钟的低噪音
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

//// ADCCFG2

//选择ADC的AB通道
#define MUXSEL_ADCB       ADC_CFG2_MUXSEL_MASK
#define MUXSEL_ADCA       0x00

//同步时钟输出启用：启用或禁用，它的输出
#define ADACKEN_ENABLED   ADC_CFG2_ADACKEN_MASK
#define ADACKEN_DISABLED  0x00

// 高速或低速转换选择
#define ADHSC_HISPEED     ADC_CFG2_ADHSC_MASK
#define ADHSC_NORMAL      0x00

// 长的采样时间选择：20，12，6，或2个额外的时钟一个较长的采样时间
#define ADLSTS_20          0x00
#define ADLSTS_12          0x01
#define ADLSTS_6           0x02
#define ADLSTS_2           0x03

////ADCSC2

// 只读状态位指示转换状态
#define ADACT_ACTIVE       ADC_SC2_ADACT_MASK
#define ADACT_INACTIVE     0x00

// 开始转换触发：硬件或软件触发，触发。使用PDB，硬件触发选项。
#define ADTRG_HW           ADC_SC2_ADTRG_MASK
#define ADTRG_SW           0x00

// ADC比较功能选择使能或禁止
#define ACFE_DISABLED      0x00
#define ACFE_ENABLED       ADC_SC2_ACFE_MASK

//比较功能大于使：更大的，或不。
#define ACFGT_GREATER      ADC_SC2_ACFGT_MASK
#define ACFGT_LESS         0x00

// 比较功能范围启用：启用或禁用。
#define ACREN_ENABLED      ADC_SC2_ACREN_MASK
#define ACREN_DISABLED     0x00

// DMA使能选择
#define DMAEN_ENABLED      ADC_SC2_DMAEN_MASK
#define DMAEN_DISABLED     0x00

// 该ADC转换的参考电压的选择（* * *不* * PGA采用vrefo只）。电压和VREFL（0），或vrefo（1）。

#define REFSEL_EXT         0x00
#define REFSEL_ALT         0x01
#define REFSEL_RES         0x02     /* reserved */
#define REFSEL_RES_EXT     0x03     /* reserved but defaults to Vref */

////ADCSC3

// 校准开始或关闭
#define CAL_BEGIN          ADC_SC3_CAL_MASK
#define CAL_OFF            0x00

// 状态指示校验失败，或正常的成功
#define CALF_FAIL          ADC_SC3_CALF_MASK
#define CALF_NORMAL        0x00

// ADC的不断转换，或做一个单转换
#define ADCO_CONTINUOUS    ADC_SC3_ADCO_MASK
#define ADCO_SINGLE        0x00

// Averaging enabled in the ADC, or not.
#define AVGE_ENABLED       ADC_SC3_AVGE_MASK
#define AVGE_DISABLED      0x00

// 多少平均之前打断单片机？4，8，16，或32
#define AVGS_4             0x00
#define AVGS_8             0x01
#define AVGS_16            0x02
#define AVGS_32            0x03

////PGA

// PGA启用或不？
#define PGAEN_ENABLED      ADC_PGA_PGAEN_MASK
#define PGAEN_DISABLED     0x00 

// 该放大器斩波稳定，或不。
#define PGACHP_CHOP        ADC_PGA_PGACHP_MASK 
#define PGACHP_NOCHOP      0x00

// PGA低功耗模式，普通模式
#define PGALP_LOW          ADC_PGA_PGALP_MASK
#define PGALP_NORMAL       0x00

// PGA的增益选择范围1到64
#define PGAG_1             0x00
#define PGAG_2             0x01
#define PGAG_4             0x02
#define PGAG_8             0x03
#define PGAG_16            0x04
#define PGAG_32            0x05
#define PGAG_64            0x06

//上述数值拟合到下面的结构选择的ADC / PGA配置所需的：

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
