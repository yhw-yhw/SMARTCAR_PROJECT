/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@aliyun.com
������汾��V2.0
�������¡�2013��12��24��
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
------------------------------------
ʹ�ñ����������ܿƼ�cortex-M0����������
*********************************************************/
//-------------------------------------------------------------------------*
// �ļ���:start.c                                                          *
// ˵  ��: CPU���������ϵͳ����                                           *
//-------------------------------------------------------------------------*

//ͷ�ļ�
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

//�ڲ���������
//-------------------------------------------------------------------------*
//������: common_startup                                                   *
//��  ��: �����ж�������RAM��                                            * 
//��  ��: ��								   *	
//˵  ��: ��ROM�еĳ�ʼ�����ݿ�����RAM��                                   *
//-------------------------------------------------------------------------*
void common_startup(void);

//-------------------------------------------------------------------------*
//������: start                                                            *
//��  ��: ϵͳ����                                                         * 
//��  ��: ��								   *	
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void start(void)
{
    SIM_COPC = 0x00;
    common_startup();
    sysinit();
    KL46_LED_Init();  
    wdog_disable();//�رտ��Ź�
    
    uart_init(UART_PORT,115200);
    uartPrintf("\n\n********************************************************\n");
    uartPrintf("* \t\t�����ʵ��ѧ KL46 ѧϰ����             *\n");
    uartPrintf("* �ں�Ƶ�ʣ�%3dMHz \t����Ƶ�� ��%3dMHz              *\n",\
           core_clk_khz/1000,Bus_Fre/1000);
    uartPrintf("* Designed By��BuptSmartCar2011                        *\n");  
    uartPrintf("* Email:498339494@qq.com                               *\n");  
    uartPrintf("* �����£�");  
    uartPrintf("%s  %s                      *\n",__DATE__,__TIME__); 
    uartPrintf("*******************************************************\n");

    
    
    main();
    while(1);
}


//-------------------------------------------------------------------------*
//������: common_startup                                                   *
//��  ��: �����ж�������RAM��                                            * 
//��  ��: ��								   *	
//˵  ��: ��ROM�еĳ�ʼ�����ݿ�����RAM��                                   *
//-------------------------------------------------------------------------*
void common_startup(void)
{


	/* ����һ�������������ǽ�ʹ�������еĸ���ѭ�� */
	uint32 n;

       /* Ϊvector_table��vector_ram�����������ļ���ַ*/
	extern uint32 __VECTOR_TABLE[];
	extern uint32 __VECTOR_RAM[];
       /* ����������RAM */
	if (__VECTOR_RAM != __VECTOR_TABLE) {
		for (n = 0; n < 0x104; n++)
			__VECTOR_RAM[n] = __VECTOR_TABLE[n];
	}
	/* vtor����������µĸ��� */
	write_vtor((uint32) __VECTOR_RAM);

	/* Ϊ��õ�ַ�����ݶΣ���ʼ�����ݶΣ�*/

	uint8 *data_ram = __section_begin(".data");
	uint8 *data_rom = __section_begin(".data_init");
	uint8 *data_rom_end = __section_end(".data_init");
	/*���Ƴ�ʼ�����ݴ�ROM��RAM*/
        n = data_rom_end - data_rom;
        while (n--)
		*data_ram++ = *data_rom++;

        /*Ϊ��õ�ַ��BSS�Σ����ʼ�����ݣ�*/
	uint8*bss_start = __section_begin(".bss");
	uint8*bss_end = __section_end(".bss");
       /*������ʼ�����ݶ�*/
	n = bss_end - bss_start;
	while (n--)
		*bss_start++ = 0;


	/***************************************************************************************************************
        ����κεĴ���Σ���Ҫ��ROM���Ƶ�RAM�ĵ�ַ��IAR������һ��Ԥ����Ĺؼ��ʣ������������ִ�д�RAM���幦�ܡ���ӡ�__ramfunc�����������е��κγ���֮ǰ������Ҫ��RAM��ִ�ж����Ǻ���ԭ�ͣ�ROM������__ramfunc void foo����Ч����
	******************************************************************************************************************/

	uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
	uint8* code_relocate = __section_begin("CodeRelocate");
	uint8* code_relocate_end = __section_end("CodeRelocate");

	/*��ROM���ƹ��ܵ�RAM*/
	n = code_relocate_end - code_relocate;
	while (n--)
	*code_relocate_ram++ = *code_relocate++;

}