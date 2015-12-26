#include "camera.h"

u8 PicBuffer[ROW][COLUMN] = {0};//图像缓冲区
u8 complete_flag = 0;
u8 temp_row = 0;
u8 temp_counter= 0;


void camera_init()
{
  //DMA init
  DMA_PORTx2BUFF_Init(DMA_CH0,(uint32)&GPIOD_PDIR,PicBuffer, TRIGER_PORT,DMA_BYTE1,COLUMN, DMA_REQ_M2);  
}

void new_dma(void * DADDR)
{
  START_DMA(DADDR,COLUMN);
}

void get_photo()
{
  complete_flag = 0;
  en_vsyn_interrupt();
  while(complete_flag!=1)
    ;
  //此处可以进行部分图像处理，通过temp_row变量获取传输进度
}

void en_href_interrupt()
{
   gpio_interrupt_init(HREF_PORT, HREF_NUM, IO_INT_FALLING_M);
}
void en_vsyn_interrupt()
{
  gpio_interrupt_init(VSYN_PORT, VSYN_NUM, IO_INT_FALLING_M);
}
void dis_href_interrupt()
{
  gpio_interrupt_dma_dis(HREF_PORT, HREF_NUM);
}
void dis_vsyn_interrupt()
{
  gpio_interrupt_dma_dis(VSYN_PORT, VSYN_NUM);
}

void show_photo()
{
  uartPrintf("here comes the photo:\n");
  for(int i=0;i<ROW;i++)
  {
    for(int j=0;j<COLUMN;j++)
      uartPrintf("%d,",PicBuffer[i][j]);
    uartPrintf("\n");
  }
}

void get_black_line()//自己的图像处理算法
{
  
}
