#ifndef GLOBAL_H
#define GLOBAL_H 1
#include "common.h"

extern int16 trueSpeed;
extern int16 g_nSpeedControlCount;
extern int8 have_new_speed;
extern u8 Pixel[128],Pixel_back[128],IntegrationTime;

extern int g_countus;

//user added
extern float kp; //PID 调节的比例常数
#define SPEED_CONTROL_COUNT 3

#endif