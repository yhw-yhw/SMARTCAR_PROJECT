/********************************************************   
��ƽ    ̨������KL46��Сϵͳ��
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@aliyun.com
������汾��V2.0
�������¡�2013��12��24��
�������Ϣ�ο����е�ַ�� 
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��IAR6.50
��Target  ��KL46
��Crystal ��50.000Mhz
------------------------------------
ʹ�ñ����������ܿƼ�cortex-M0����������
*********************************************************/
#ifndef __KL46_LIGHT_H__
#define __KL46_LIGHT_H__

    //1 ͷ�ļ�
    #include "common.h"
    #include "gpio.h"
    
    //2.2 ��״̬�궨��
    #define Light_ON       0         //����(��Ӧ�͵�ƽ)
    #define Light_OFF      1         //�ư�(��Ӧ�ߵ�ƽ)
    
    void KL46_LED_Init();   
    void KL46_LED_Set(int state);
    void KL46_LED_Turn(void);
    
#endif 
