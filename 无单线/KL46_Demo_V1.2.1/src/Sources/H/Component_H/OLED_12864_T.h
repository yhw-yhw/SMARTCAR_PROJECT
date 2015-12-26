#include "common.h"
#include "includes.h"

#ifndef _OLED_12864_T_H  //OLED_12864_T
#define __OLED_12864_T_H
#include "includes.h"
#include "common.h"
#include "gpio.h"


#define byte uint8
#define word uint16
#define GPIO_PIN_MASK      0x1Fu    //0x1f=31,限制位数为0--31有效
#define GPIO_PIN(x)        (((1)<<(x & GPIO_PIN_MASK)))  //把当前位置1

#define LCD_DC_HIGH  (GPIOE_PDOR |=  GPIO_PDOR_PDO(GPIO_PIN(6)))
#define LCD_DC_LOW   (GPIOE_PDOR &=~ GPIO_PDOR_PDO(GPIO_PIN(6)))

#define LCD_SCL_HIGH (GPIOE_PDOR |=  GPIO_PDOR_PDO(GPIO_PIN(0)))
#define LCD_SCL_LOW  (GPIOE_PDOR &=~ GPIO_PDOR_PDO(GPIO_PIN(0)))

#define LCD_SDA_HIGH (GPIOE_PDOR |=  GPIO_PDOR_PDO(GPIO_PIN(2)))
#define LCD_SDA_LOW  (GPIOE_PDOR &=~ GPIO_PDOR_PDO(GPIO_PIN(2)))

#define LCD_RST_HIGH (GPIOE_PDOR |=  GPIO_PDOR_PDO(GPIO_PIN(4)))
#define LCD_RST_LOW  (GPIOE_PDOR &=~ GPIO_PDOR_PDO(GPIO_PIN(4)))


 extern byte longqiu96x64[768];
 void LCD_Init(void);
 void LCD_CLS(void);
 void LCD_Set_Pos(byte x, byte y);
 void LCD_WrDat(byte data);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
#endif