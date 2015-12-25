/*
舵机PD

*/////////////

#ifndef _PID_H
#define _PID_H

#define EE 5 //EE 为误差的阀值，小于这个数值的时候，不做 PID 调整，避免误差较小
#define RC 130//130 //图像中心位置 (40+199)/2

int pidSteer(int ek);
//void pidSteerIni(void);

#endif