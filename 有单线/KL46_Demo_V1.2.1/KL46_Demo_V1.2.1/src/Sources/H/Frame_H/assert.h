/*
************************************************************************
*                �����ʵ��ѧ KL46 ѧϰ����                                        
* �ļ��� :[assert.h] 
* ��  �� ��assert���Ժ���
*�Ľ�����ֲ��Hyoga
*  Email ��498339494@qq.com
* ˵  �� ��assert����
***********************************************************************
*/


#ifndef _ASSERT_H_
#define _ASSERT_H_

#define ASSERT(expr) if (!(expr)) assert_failed()
#define assert(expr,output) if (!(expr)) assert_failed1(output)

extern void assert_failed();
extern void assert_failed1(char*);

#endif



