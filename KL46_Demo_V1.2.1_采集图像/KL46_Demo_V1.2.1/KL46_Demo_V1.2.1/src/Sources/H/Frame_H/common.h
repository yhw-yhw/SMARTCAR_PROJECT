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

#ifndef _COMMON_H_
#define _COMMON_H_

    //1 头文件
   #include "MKL46Z4.h"   //寄存器映像头文件
   
    //2 宏定义
    //2.1 用于中断的宏定义    
    #define ARM_INTERRUPT_LEVEL_BITS     4//中断优先级宏定义
    #define EnableInterrupts asm(" CPSIE i");//开总中断
    #define DisableInterrupts asm(" CPSID i");//关总中断
    
    
    //2.2 类型别名宏定义
    typedef unsigned char	uint8;  /*  8 bits */
    typedef unsigned short int	uint16; /* 16 bits */
    typedef unsigned long int	uint32; /* 32 bits */
    
    typedef char		int8;   /*  8 bits */
    typedef short int	       	int16;  /* 16 bits */
    typedef int		       	int32;  /* 32 bits */
    
    typedef volatile int8	vint8;  /*  8 bits */
    typedef volatile int16	vint16; /* 16 bits */
    typedef volatile int32	vint32; /* 32 bits */
    
    typedef volatile uint8	vuint8;  /*  8 bits */
    typedef volatile uint16	vuint16; /* 16 bits */
    typedef volatile uint32	vuint32; /* 32 bits */

 
 //-------------------------------------------------------------------------*
//                        数据类型定义                                     *
//-------------------------------------------------------------------------*
typedef 	unsigned 	char		u8;	  //无符号型
typedef 	unsigned 	short int	u16;
typedef 	unsigned 	long  int	u32;

typedef 	char					s8;	  //有符号型
typedef 	short int				s16;
typedef 	long  int				s32;
typedef    	__INT64_T_TYPE__     	s64;

 
    //3 函数声明
    //-------------------------------------------------------------------------*
    //函数名: stop                                                             *
    //功  能: 设置CPU为STOP模式                                                * 
    //参  数: 无						 	       *	
    //返  回: 无                                                               *
    //说  明: 无                                                               *
    //-------------------------------------------------------------------------*
    void stop (void);
    
    //-------------------------------------------------------------------------*
    //函数名: wait                                                             *
    //功  能: 设置CPU为WAIT模式                                                * 
    //参  数: 无					     		       *	
    //返  回: 无                                                               *
    //说  明: 无                                                               *
    //-------------------------------------------------------------------------*
    void wait (void);
    
    //-------------------------------------------------------------------------*
    //函数名: write_vtor                                                       *
    //功  能: 更改中断向量表偏移寄存器的值                                     * 
    //参  数: 要更改的值    						       *	
    //返  回: 无                                                               *
    //说  明: 无                                                               *
    //-------------------------------------------------------------------------*
    void write_vtor (int);
    
    //-------------------------------------------------------------------------*
    //函数名: enable_irq                                                       *
    //功  能: 使能irq中断                                                      * 
    //参  数: irq:irq号       						       *	
    //返  回: 无                                                               *
    //说  明: irq号不是中断向量号                                              *
    //-------------------------------------------------------------------------*
    void enable_irq (int);
    
    //-------------------------------------------------------------------------*
    //函数名: disable_irq                                                      *
    //功  能: 禁止irq中断                                                      * 
    //参  数: irq:irq号       						       *	
    //返  回: 无                                                               *
    //说  明: irq号不是中断向量号                                              *
    //-------------------------------------------------------------------------*
    void disable_irq (int);
    
    //-------------------------------------------------------------------------*
    //函数名: set_irq_priority                                                 *
    //功  能: 设置irq中断和优先级                                              * 
    //参  数: irq:irq号         					       *	
    //        prio:优先级						       *	
    //返  回: 无                                                               *
    //说  明: irq号不是中断向量号                                              *
    //-------------------------------------------------------------------------*
    void set_irq_priority (int, int);
    
    //-------------------------------------------------------------------------*
    //函数名: main                                                             *
    //功  能: 主函数声明                                                       * 
    //参  数: 无         						       *	
    //返  回: 无                                                               *
    //说  明: 无                                                               *
    //-------------------------------------------------------------------------*
    void main(void);
    void out_char (char ch);
    
    #define	TRUE	(1)
#define FALSE	(0)
#endif 
