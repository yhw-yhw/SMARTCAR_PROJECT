#include "camera.h"

s32 Line_Center_L[ROW] = { 0 };
s32 Line_Center_R[ROW] = { 0 };
s32 Line_Center[ROW] = {0};
u8 PicBuffer[ROW][COLUMN] = {0};//ͼ�񻺳���
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
  //�˴����Խ��в���ͼ����ͨ��temp_row������ȡ�������
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

/*=== ��ȡ���ߺ������㷨������ ===*/
#define ROW_START       (ROW-3)
#define DELTA_THRESHOLD 30
//�ڰ׵�������ֵ 
#define THRESHOLD 115//125
#define CENTER 119//119 // ʵ��ͼ���м�ֵ
#define BOUND_RADIUS 5 // �߽������뾶
#define SINGLE_RADIUS 15      // �����б�뾶

#define LOSELL_THRESHOLD 7 // ���߶�ʧ����������ֵ
#define LOSERL_THRESHOLD 7 // ���߶�ʧ����������ֵ
#define CROSSROAD_THRESHOLD 7 // ʮ��·�ڲ���������ֵ
/*=== ��ȡ���ߺ������㷨������ ===*/
#define COLUMN_START 40//40
#define COLUMN_END 199
#define COMPLEMENT_DIST 140//140

void GetBlackLine()
{
 int row, // �к�
        column, // �к�
        leftline_leftbound = COLUMN_START + 1, // ����������߽磬�ʼΪȫͼ��߽�
        leftline_rightbound = CENTER, // ���������ұ߽磬�ʼΪȫͼ�м���
        leftline_lastvalid = -1, // ���һ����Ч���ߵ�ֵ
        rightline_leftbound = CENTER, // ����������߽磬�ʼΪȫͼ�м���
        rightline_rightbound = COLUMN_END - 1, // ���������ұ߽磬�ʼΪȫͼ�ұ߽�
        rightline_lastvalid = -1, // ���һ����Ч���ߵ�ֵ
        leftline_lost = 0, // ���߶�����
        rightline_lost = 0, // ���߶�����
        crossroad = 0, // ʮ��·�ڱ�־����
        singleline_mode = 0, // ����ģʽ��־����
        complement_dist = COMPLEMENT_DIST,  // ����ȱʧ���߾���
        //delta_max, delta_max2, delta_max_position, 
        tmp, tmp2; // ��ʱ����
    //int * tmptr; // ��ʱָ��
    float complement_k = 0.0; // ����б��
    //Line_Center[ROW_START + 1] = CENTER;
    for (row = ROW_START; row >= 20; row--)
    {
        Line_Center[row] = Line_Center_L[row] = Line_Center_R[row] = -1; // ��λ���н������

        if (singleline_mode == 1) {
            // ����Ϊ������
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
                // ���м俪ʼ����
                leftline_rightbound = Line_Center[row + 1] - 1;
                rightline_leftbound = Line_Center[row + 1] + 1;
                // �����һ���ҵ�������λ���������������ұ߽�
                rightline_rightbound = COLUMN_END - 1;
                singleline_mode = 0;
            }
        }
        else if (singleline_mode == 2) {
            // ����Ϊ������
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
                // ���м俪ʼ����
                leftline_rightbound = Line_Center[row + 1] - 1;
                rightline_leftbound = Line_Center[row + 1] + 1;
                // �����һ���ҵ�������λ���������������ұ߽�
                rightline_rightbound = COLUMN_END - 1;
                singleline_mode = 0;
            }
        }


        // ������һ�����������ұ߽�������߽��������Χ
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

        // ������߽�
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

        // ��������������߽������ұ߽��������Χ
        if (Line_Center_L[row] != -1 && rightline_leftbound < Line_Center_L[row])
        {
            rightline_leftbound = Line_Center_L[row] + 1;
            if (rightline_leftbound >= rightline_rightbound)
            {
                rightline_rightbound = rightline_leftbound + 2 * BOUND_RADIUS < COLUMN_END ?
                    rightline_leftbound + 2 * BOUND_RADIUS : COLUMN_END - 1;
            }
        }

        // �����ұ߽�
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

        // ���߶��ߣ�����Ϊ��ת��Ҳ�п��ܽ����ǳ���ͼ��߽�
        if (Line_Center_L[row] == -1 && Line_Center_R[row] > 0)
        {
            if (crossroad >= CROSSROAD_THRESHOLD) {
                crossroad++;
                // �����һ���ҵ�������λ����������������߽�
                leftline_leftbound = leftline_lastvalid != -1 && leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // ���м俪ʼ����
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
            // ������
            Line_Center_L[row] = row < ROW_START && Line_Center_L[row + 1] != -1 ?
                Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) :
                Line_Center_R[row] - complement_dist /*COLUMN_START*/;
            Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // �������� 
#ifdef G_PRINT
            printp("Line %d lost the left line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
        else if (Line_Center_L[row] > 0 && Line_Center_R[row] == -1)
        { // ���߶��ߣ�����Ϊ��ת��Ҳ�п��ܽ����ǳ���ͼ��߽�
            if (crossroad >= CROSSROAD_THRESHOLD)
            {
                crossroad++;
                rightline_leftbound = CENTER;
                // �����һ���ҵ�������λ���������������ұ߽�
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
            
            rightline_lost++; // �������߶�ʧ����

            // ���Ը���ǰһ��������������λ���Լ���������λ��ȷ����������λ��
            Line_Center_R[row] = row < ROW_START && Line_Center_R[row + 1] != -1 ?
                Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) :
                Line_Center_L[row] + complement_dist /*COLUMN_END*/;
              //COLUMN ;//COLUMN_END   �ս�����ǵ��ߣ����߸�Ϊ�߽�
            
            Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // ��������
#ifdef G_PRINT
            printp("Line %d lost the right line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
        else if (Line_Center_L[row] == -1 && Line_Center_R[row] == -1)
        { // ������ͬʱ���ߣ�����Ϊʮ��·��
            if (++crossroad >= CROSSROAD_THRESHOLD)
            {
                // �����һ���ҵ�������λ����������������߽�
                leftline_leftbound = leftline_lastvalid != -1 &&
                    leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // ���м俪ʼ����
                leftline_rightbound = CENTER;
                rightline_leftbound = CENTER;
                // �����һ���ҵ�������λ���������������ұ߽�
                rightline_rightbound = rightline_lastvalid != -1 && rightline_lastvalid + BOUND_RADIUS < COLUMN_END ? rightline_lastvalid + BOUND_RADIUS : COLUMN_END - 1;
            }
#ifdef G_PRINT
            printp("Line %d lost both lines\n", row);
#endif
        }
        else
        { // �����߾��ҵ����ڴ˴�����ֲ���
            if (crossroad >= CROSSROAD_THRESHOLD && crossroad > leftline_lost && crossroad >= rightline_lost)
            {
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // ��������
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
                crossroad = leftline_lost = rightline_lost = 0; // ���ʮ��·�ڱ�־
#ifdef G_PRINT
                printp("\n");
#endif
                crossroad = leftline_lost = rightline_lost = 0; // ���ʮ��·�ڱ�־
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
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // �������� 
            }
#ifdef G_PRINT
            printp("Line %d find out both lines: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
    }
}  //end GetBlackLine()


