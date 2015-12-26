/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：delay.h
 * 描述         ：模拟延时函数头文件
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	


#ifndef __FUN_H__
#define __FUN_H__

#include "common.h"
#include "sysinit.h"

void  delay(void);          //延时约500ms
void  delayms(uint32  ms);
void  delayus(uint32  us);
#endif