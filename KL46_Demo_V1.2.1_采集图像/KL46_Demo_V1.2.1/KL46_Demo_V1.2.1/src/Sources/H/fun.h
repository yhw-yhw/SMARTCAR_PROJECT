/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��delay.h
 * ����         ��ģ����ʱ����ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	


#ifndef __FUN_H__
#define __FUN_H__

#include "common.h"
#include "sysinit.h"

void  delay(void);          //��ʱԼ500ms
void  delayms(uint32  ms);
void  delayus(uint32  us);
#endif