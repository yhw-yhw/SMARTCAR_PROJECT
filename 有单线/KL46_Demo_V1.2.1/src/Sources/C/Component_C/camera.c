#include "camera.h"

s32 Line_Center_L[ROW] = { 0 };
s32 Line_Center_R[ROW] = { 0 };
s32 Line_Center[ROW] = {0};
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
  //en_href_interrupt();
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
  //uartPrintf("1,254");
  for(int i=0;i<ROW;i++)
  {
    for(int j=0;j<COLUMN;j++)
      uartPrintf("%d ",PicBuffer[i][j]);
    uartPrintf("\n");
  }
}

/*=== 提取边线和中线算法配置项 ===*/
#define ROW_START       (ROW-3)
#define DELTA_THRESHOLD 30
//黑白的跳变域值 
#define THRESHOLD 115//125
#define CENTER 119//119 // 实际图像中间值
#define BOUND_RADIUS 5 // 边界搜索半径
#define SINGLE_RADIUS 15      // 单线判别半径

#define LOSELL_THRESHOLD 7 // 左线丢失补线启发阈值
#define LOSERL_THRESHOLD 7 // 右线丢失补线启发阈值
#define CROSSROAD_THRESHOLD 7 // 十字路口补线启发阈值
/*=== 提取边线和中线算法配置项 ===*/
#define COLUMN_START 40//40
#define COLUMN_END 199
#define COMPLEMENT_DIST 140//140

void GetBlackLine()
{
 int row, // 行号
        column, // 列号
        leftline_leftbound = COLUMN_START + 1, // 左线搜索左边界，最开始为全图左边界
        leftline_rightbound = CENTER, // 左线搜索右边界，最开始为全图中间线
        leftline_lastvalid = -1, // 最后一条有效左线的值
        rightline_leftbound = CENTER, // 右线搜索左边界，最开始为全图中间线
        rightline_rightbound = COLUMN_END - 1, // 右线搜索右边界，最开始为全图右边界
        rightline_lastvalid = -1, // 最后一条有效右线的值
        leftline_lost = 0, // 左线丢线数
        rightline_lost = 0, // 右线丢线数
        crossroad = 0, // 十字路口标志变量
        singleline_mode = 0, // 单线模式标志变量
        complement_dist = COMPLEMENT_DIST,  // 边线缺失补线距离
        //delta_max, delta_max2, delta_max_position, 
        tmp, tmp2; // 临时变量
    //int * tmptr; // 临时指针
    float complement_k = 0.0; // 补线斜率
    //Line_Center[ROW_START + 1] = CENTER;
    for (row = ROW_START; row >= 20; row--)
    {
        Line_Center[row] = Line_Center_L[row] = Line_Center_R[row] = -1; // 复位该行结果数组

        if (singleline_mode == 1) {
            // 左线为中心线
            for (column = leftline_rightbound; column >= leftline_leftbound; column--)
            {
                if (PicBuffer[row][column + 1] - PicBuffer[row][column] >= DELTA_THRESHOLD &&
                    PicBuffer[row][column] - PicBuffer[row][column - 1] <= DELTA_THRESHOLD &&
                    PicBuffer[row][column] <= THRESHOLD)
                {
                    leftline_lastvalid = Line_Center[row] = column;
                    leftline_leftbound = column - BOUND_RADIUS > COLUMN_START ? column - BOUND_RADIUS : COLUMN_START + 1;
                    leftline_rightbound = column + BOUND_RADIUS < COLUMN_END ? column + BOUND_RADIUS : COLUMN_END - 1;
                    break;
                }
            }

            if (Line_Center[row] != -1) {
#ifdef G_PRINT
                printp("Single line %d\n", Line_Center[row]);
#endif
                continue;
            }
            else {
                leftline_leftbound = COLUMN_START + 1;
                // 从中间开始搜索
                leftline_rightbound = Line_Center[row + 1] - 1;
                rightline_leftbound = Line_Center[row + 1] + 1;
                // 按最后一次找到的右线位置重设右线搜索右边界
                rightline_rightbound = COLUMN_END - 1;
                singleline_mode = 0;
            }
        }
        else if (singleline_mode == 2) {
            // 右线为中心线
            for (column = rightline_leftbound; column <= rightline_rightbound; column++)
            {
                if (PicBuffer[row][column - 1] - PicBuffer[row][column] >= DELTA_THRESHOLD &&
                    PicBuffer[row][column] - PicBuffer[row][column + 1] <= DELTA_THRESHOLD &&
                    PicBuffer[row][column] <= THRESHOLD)
                {
                    rightline_lastvalid = Line_Center[row] = column;
                    rightline_leftbound = column - BOUND_RADIUS > COLUMN_START ? column - BOUND_RADIUS : COLUMN_START + 1;
                    rightline_rightbound = column + BOUND_RADIUS < COLUMN_END ? column + BOUND_RADIUS : COLUMN_END - 1;
                    break;
                }
            }

            if (Line_Center[row] != -1) {
#ifdef G_PRINT
                printp("Single line %d\n", Line_Center[row]);
#endif
                continue;
            }
            else {
                leftline_leftbound = COLUMN_START + 1;
                // 从中间开始搜索
                leftline_rightbound = Line_Center[row + 1] - 1;
                rightline_leftbound = Line_Center[row + 1] + 1;
                // 按最后一次找到的右线位置重设右线搜索右边界
                rightline_rightbound = COLUMN_END - 1;
                singleline_mode = 0;
            }
        }


        // 根据上一次搜索到的右边界限制左边界的搜索范围
        //if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid && Line_Center_R[row + 1] == rightline_lastvalid)
        if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid)
        {
            leftline_rightbound = Line_Center_R[row + 1] - 1;
            if (leftline_rightbound <= leftline_leftbound)
            {
                leftline_leftbound = leftline_rightbound - 2 * BOUND_RADIUS > COLUMN_START ?
                    leftline_rightbound - 2 * BOUND_RADIUS : COLUMN_START + 1;
            }
        }

        // 搜索左边界
        for (column = leftline_rightbound; column >= leftline_leftbound; column--)
        {
            if (PicBuffer[row][column + 1] - PicBuffer[row][column] >= DELTA_THRESHOLD &&
                PicBuffer[row][column] - PicBuffer[row][column - 1] <= DELTA_THRESHOLD &&
                PicBuffer[row][column] <= THRESHOLD)
            {
                leftline_lastvalid = Line_Center_L[row] = column;
                leftline_leftbound = column - BOUND_RADIUS > COLUMN_START ? column - BOUND_RADIUS : COLUMN_START + 1;
                leftline_rightbound = column + BOUND_RADIUS < COLUMN_END ? column + BOUND_RADIUS : COLUMN_END - 1;
                break;
            }
        }

        // 根据搜索到的左边界限制右边界的搜索范围
        if (Line_Center_L[row] != -1 && rightline_leftbound < Line_Center_L[row])
        {
            rightline_leftbound = Line_Center_L[row] + 1;
            if (rightline_leftbound >= rightline_rightbound)
            {
                rightline_rightbound = rightline_leftbound + 2 * BOUND_RADIUS < COLUMN_END ?
                    rightline_leftbound + 2 * BOUND_RADIUS : COLUMN_END - 1;
            }
        }

        // 搜索右边界
        for (column = rightline_leftbound; column <= rightline_rightbound; column++)
        {
            if (PicBuffer[row][column - 1] - PicBuffer[row][column] >= DELTA_THRESHOLD &&
                PicBuffer[row][column] - PicBuffer[row][column + 1] <= DELTA_THRESHOLD &&
                PicBuffer[row][column] <= THRESHOLD)
            {
                rightline_lastvalid = Line_Center_R[row] = column;
                rightline_leftbound = column - BOUND_RADIUS > COLUMN_START ? column - BOUND_RADIUS : COLUMN_START + 1;
                rightline_rightbound = column + BOUND_RADIUS < COLUMN_END ? column + BOUND_RADIUS : COLUMN_END - 1;
                break;
            }
        }

        // 左线丢线，可能为左转，也有可能仅仅是超出图像边界
        if (Line_Center_L[row] == -1 && Line_Center_R[row] > 0)
        {
            if (crossroad >= CROSSROAD_THRESHOLD) {
                crossroad++;
                // 按最后一次找到的左线位置重设左线搜索左边界
                leftline_leftbound = leftline_lastvalid != -1 && leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // 从中间开始搜索
                leftline_rightbound = CENTER;
            }
            else {
                tmp = row < ROW_START && Line_Center[row + 1] != -1 ? Line_Center[row + 1] : CENTER;
                if (tmp - SINGLE_RADIUS <= Line_Center_R[row] && Line_Center_R[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_R[row];
                    singleline_mode = 2;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
            }
            leftline_lost++;
            // 补左线
            Line_Center_L[row] = row < ROW_START && Line_Center_L[row + 1] != -1 ?
                Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) :
                Line_Center_R[row] - complement_dist /*COLUMN_START*/;
            Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线 
#ifdef G_PRINT
            printp("Line %d lost the left line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
        else if (Line_Center_L[row] > 0 && Line_Center_R[row] == -1)
        { // 右线丢线，可能为右转，也有可能仅仅是超出图像边界
            if (crossroad >= CROSSROAD_THRESHOLD)
            {
                crossroad++;
                rightline_leftbound = CENTER;
                // 按最后一次找到的右线位置重设右线搜索右边界
                rightline_rightbound = rightline_lastvalid != -1 && rightline_lastvalid + BOUND_RADIUS < COLUMN_END ?
                    rightline_lastvalid + BOUND_RADIUS : COLUMN_END - 1;
            }
            else {
                tmp = row < ROW_START && Line_Center[row + 1] != -1 ? Line_Center[row + 1] : CENTER ;
                if (tmp - SINGLE_RADIUS <= Line_Center_L[row] && Line_Center_L[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_L[row];
                    singleline_mode = 1;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
            }
            
            rightline_lost++; // 增加右线丢失计数

            // 尝试根据前一行搜索到的右线位置以及本行左线位置确定本行右线位置
            Line_Center_R[row] = row < ROW_START && Line_Center_R[row + 1] != -1 ?
                Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) :
                Line_Center_L[row] + complement_dist /*COLUMN_END*/;
              //COLUMN ;//COLUMN_END   刚进入就是单线，右线赋为边界
            
            Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线
#ifdef G_PRINT
            printp("Line %d lost the right line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
        else if (Line_Center_L[row] == -1 && Line_Center_R[row] == -1)
        { // 左右线同时丢线，可能为十字路口
            if (++crossroad >= CROSSROAD_THRESHOLD)
            {
                // 按最后一次找到的左线位置重设左线搜索左边界
                leftline_leftbound = leftline_lastvalid != -1 &&
                    leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // 从中间开始搜索
                leftline_rightbound = CENTER;
                rightline_leftbound = CENTER;
                // 按最后一次找到的右线位置重设右线搜索右边界
                rightline_rightbound = rightline_lastvalid != -1 && rightline_lastvalid + BOUND_RADIUS < COLUMN_END ? rightline_lastvalid + BOUND_RADIUS : COLUMN_END - 1;
            }
#ifdef G_PRINT
            printp("Line %d lost both lines\n", row);
#endif
        }
        else
        { // 左右线均找到，在此处理各种补线
            if (crossroad >= CROSSROAD_THRESHOLD && crossroad > leftline_lost && crossroad >= rightline_lost)
            {
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线
                tmp2 = tmp = leftline_lost > rightline_lost ? leftline_lost : rightline_lost;
                tmp = tmp + row + crossroad < ROW_START ? tmp + row + crossroad : ROW_START;
                complement_k = Line_Center[tmp] != -1 ? (Line_Center[tmp] - Line_Center[row]) / (float)crossroad : 0.0;
#ifdef G_PRINT
                printp(" k = %f", complement_k);
#endif
                for (tmp2 += crossroad; tmp2 >= 0; tmp2--, tmp--)
                {
                    Line_Center[tmp] = Line_Center[row] + tmp2 * complement_k;
                }
                crossroad = leftline_lost = rightline_lost = 0; // 清除十字路口标志
#ifdef G_PRINT
                printp("\n");
#endif
                crossroad = leftline_lost = rightline_lost = 0; // 清除十字路口标志
            }
            else {
                leftline_lost = rightline_lost = 0;
                tmp = row < ROW_START && Line_Center[row + 1] != -1 ? Line_Center[row + 1] : CENTER;
                if (tmp - SINGLE_RADIUS <= Line_Center_L[row] && Line_Center_L[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_L[row];
                    singleline_mode = 1;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
                else if (tmp - SINGLE_RADIUS <= Line_Center_R[row] && Line_Center_R[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_R[row];
                    singleline_mode = 2;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线 
            }
#ifdef G_PRINT
            printp("Line %d find out both lines: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
    }
}  //end GetBlackLine()


