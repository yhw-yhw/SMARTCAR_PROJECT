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
#ifndef __KL46_LIGHT_H__
#define __KL46_LIGHT_H__

    //1 头文件
    #include "common.h"
    #include "gpio.h"
    
    //2.2 灯状态宏定义
    #define Light_ON       0         //灯亮(对应低电平)
    #define Light_OFF      1         //灯暗(对应高电平)
    
    void KL46_LED_Init();   
    void KL46_LED_Set(int state);
    void KL46_LED_Turn(void);
    
#endif 
