/*
*˵����
*���ļ���������������ͷ��ص�����
*OV7620����ͷͼ��Ϊ640*480���������������жϾ�����4��Ƶ����������Ϊ640/4=160
*����ͷΪ����ɨ�裬ÿ��ֻ�ɵ����ͼ��240�У�Ϊ��ʡ�ڴ�ֻ���ӵ�һ����ж���Ϊ120
*��ȡ���ߵ��㷨��ŵ�get_black_line()��
*ע�⣺���ļ������ͼ���С����ʹ�ã��ٴ�ᳬ��KL46�Դ��ڴ棬����ͨ����
*ͼ����ຬ��������������ʱδ�ҵ�ԭ���п��Ϊ��210!��
*2015/1/11 by Sky
*���䣺sky10834@163.com
*/
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "dma.h"
#include "uart.h"

#define COLUMN          210   //������
#define ROW             120   //������
#define TRIGER_PORT     PTA2  //���������жϴ����ܽ�
#define HREF_PORT       PORTA //���жϹܽ�
#define HREF_NUM        15    //���жϹܽź�
#define VSYN_PORT       PORTA //���жϹܽ�
#define VSYN_NUM        14    //���жϹܽź�

extern u8 PicBuffer[ROW][COLUMN];//ͼ�񻺳���
extern u8 complete_flag;         //��ͼ��ɱ�־
extern u8 temp_row;              //��¼��ǰ������
extern u8 temp_counter;          //2�ּ�����

void camera_init();              //DMA��ʼ��
void new_dma(void * DADDR);     //��ʼDMA����
void en_href_interrupt();        //���жϴ�
void en_vsyn_interrupt();        //�򿪳��ж�
void dis_href_interrupt();       //�ر����ж�
void dis_vsyn_interrupt();       //�رճ��ж�
void get_photo();                //��ʼ�ɼ�ͼ��
void show_photo();               //���ڴ���ͼ��
void get_black_line();           //�Լ���ͼ�����㷨


#endif