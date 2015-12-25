/********************************************************   
【平    台】龙丘KL46最小系统版
【编    写】龙丘
【Designed】by Chiu Sir
【E-mail  】chiusir@aliyun.com
【软件版本】V2.0
【最后更新】2013年12月24日
【dev.env.】IAR6.50
【Target  】KL46
【Crystal 】50.000Mhz
------------------------------------
使用北京龙邱智能科技cortex-M0开发工具箱
*********************************************************/
//-------------------------------------------------------------------------*
// 文件名:start.c                                                          *
// 说  明: CPU启动后进行系统配置                                           *
//-------------------------------------------------------------------------*

//头文件
#include "common.h"
#include "wdog.h"
#include "sysinit.h"
#include "MKL46Z4.h"
#include "uart.h"
#include "KL46_light.h"

#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam" 

//内部函数声明
//-------------------------------------------------------------------------*
//函数名: common_startup                                                   *
//功  能: 复制中断向量表到RAM中                                            * 
//参  数: 无								   *	
//说  明: 将ROM中的初始化数据拷贝到RAM中                                   *
//-------------------------------------------------------------------------*
void common_startup(void);

//-------------------------------------------------------------------------*
//函数名: start                                                            *
//功  能: 系统启动                                                         * 
//参  数: 无								   *	
//说  明: 无                                                               *
//-------------------------------------------------------------------------*
void start(void)
{
    SIM_COPC = 0x00;
    common_startup();
    sysinit();
    KL46_LED_Init();  
    wdog_disable();//关闭看门够
    
    uart_init(UART_PORT,115200);
    uartPrintf("\n\n********************************************************\n");
    uartPrintf("* \t\t北京邮电大学 KL46 学习例程             *\n");
    uartPrintf("* 内核频率：%3dMHz \t总线频率 ：%3dMHz              *\n",\
           core_clk_khz/1000,Bus_Fre/1000);
    uartPrintf("* Designed By：BuptSmartCar2011                        *\n");  
    uartPrintf("* Email:498339494@qq.com                               *\n");  
    uartPrintf("* 最后更新：");  
    uartPrintf("%s  %s                      *\n",__DATE__,__TIME__); 
    uartPrintf("*******************************************************\n");

    
    
    main();
    while(1);
}


//-------------------------------------------------------------------------*
//函数名: common_startup                                                   *
//功  能: 复制中断向量表到RAM中                                            * 
//参  数: 无								   *	
//说  明: 将ROM中的初始化数据拷贝到RAM中                                   *
//-------------------------------------------------------------------------*
void common_startup(void)
{


	/* 声明一个计数器，我们将使用在所有的复制循环 */
	uint32 n;

       /* 为vector_table和vector_ram来自链接器文件地址*/
	extern uint32 __VECTOR_TABLE[];
	extern uint32 __VECTOR_RAM[];
       /* 复制向量表到RAM */
	if (__VECTOR_RAM != __VECTOR_TABLE) {
		for (n = 0; n < 0x104; n++)
			__VECTOR_RAM[n] = __VECTOR_TABLE[n];
	}
	/* vtor点的向量表新的副本 */
	write_vtor((uint32) __VECTOR_RAM);

	/* 为获得地址。数据段（初始化数据段）*/

	uint8 *data_ram = __section_begin(".data");
	uint8 *data_rom = __section_begin(".data_init");
	uint8 *data_rom_end = __section_end(".data_init");
	/*复制初始化数据从ROM，RAM*/
        n = data_rom_end - data_rom;
        while (n--)
		*data_ram++ = *data_rom++;

        /*为获得地址。BSS段（零初始化数据）*/
	uint8*bss_start = __section_begin(".bss");
	uint8*bss_end = __section_end(".bss");
       /*清除零初始化数据段*/
	n = bss_end - bss_start;
	while (n--)
		*bss_start++ = 0;


	/***************************************************************************************************************
        获得任何的代码段，需要从ROM复制到RAM的地址。IAR工具有一个预定义的关键词，可以用来标记执行从RAM个体功能。添加“__ramfunc“返回类型中的任何程序之前，您需要从RAM中执行而不是函数原型，ROM。例：__ramfunc void foo（无效）；
	******************************************************************************************************************/

	uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
	uint8* code_relocate = __section_begin("CodeRelocate");
	uint8* code_relocate_end = __section_end("CodeRelocate");

	/*从ROM复制功能的RAM*/
	n = code_relocate_end - code_relocate;
	while (n--)
	*code_relocate_ram++ = *code_relocate++;

}