/*
************************************************************************
*                北京邮电大学 KL46 学习例程                                        
* 文件名 :[assert.h] 
* 描  述 ：assert断言函数
*改进与移植：Hyoga
*  Email ：498339494@qq.com
* 说  明 ：assert断言
***********************************************************************
*/


#ifndef _ASSERT_H_
#define _ASSERT_H_

#define ASSERT(expr) if (!(expr)) assert_failed()
#define assert(expr,output) if (!(expr)) assert_failed1(output)

extern void assert_failed();
extern void assert_failed1(char*);

#endif



