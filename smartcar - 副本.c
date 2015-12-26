//�ڲ�ʹ�������⴫����
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#define ROW 120 //80 
#define COLUMN 210  //160

/*==== ʹ��python�����ļ��б� ====*/

#define FILE_NUM (sizeof(filepath) / (50 * sizeof(char)))
static char filepath[][50] = {
	"pic\\1.txt",
	"pic\\2.txt",
    "pic\\3.txt",
    "pic\\4.txt",
    "pic\\5.txt",
    "pic\\6.txt",
    "pic\\7.txt",
	"pic\\8.txt",
    "pic\\9.txt",
    "pic\\10.txt",
    "pic\\11.txt",
    "pic\\12.txt",   
	"pic\\13.txt",
	"pic\\14.txt",
    "pic\\15.txt",
    "pic\\16.txt",
    "pic\\17.txt",
    "pic\\18.txt",   
    "pic\\19.txt",
    "pic\\20.txt",   
    
};

/*==== ʹ��python�����ļ��б� ====*/
/* 
//�ڰ׵�������ֵ 
#define THRESHOLD 159  

//��Ч������ȣ���Ч����       
#define SEARCHWITHDEN 12 
//��Ч�������򣨺����� 
#define SEARCHWITHDDIS 6
//��չ������ 
#define SEARCHWITHDEXT 30

#define COLUMN_START 1
#define COLUMN_END 126
#define CENTER     62*/ 
/*=== ��ȡ���ߺ������㷨������ ===*/
#define ROW_START       (ROW-10)//3 
#define DELTA_THRESHOLD 30
//�ڰ׵�������ֵ 
#define THRESHOLD  115 //125
#define CENTER 119//119 // ʵ��ͼ���м�ֵ
#define BOUND_RADIUS 5 // �߽������뾶
#define SINGLE_RADIUS 15      // �����б�뾶

#define LOSELL_THRESHOLD 7 // ���߶�ʧ����������ֵ
#define LOSERL_THRESHOLD 7 // ���߶�ʧ����������ֵ
#define CROSSROAD_THRESHOLD 7 // ʮ��·�ڲ���������ֵ
//=== ��ȡ���ߺ������㷨������ ===
#define COLUMN_START 40 //40
#define COLUMN_END 199 //199
#define COMPLEMENT_DIST 120

static char *LogInfo = { 0 };

unsigned char Pic_Buffer[ROW][COLUMN];
signed int  Line_Center[ROW] = { 0 };
signed int  Line_Center_L[ROW] = { 0 };
signed int  Line_Center_R[ROW] = { 0 };

void printp(char* format, ...);
void WritePicValue();
void WritePicBlack();
void GetBlackLine();
void ReadFile(char * inpath);
void SendCenterLine3(int * templineL, int * templine, int * templineR);
void writelog(char *info, char *outpath);
void writereturn(unsigned char temp[][COLUMN], char *returnpath, int model);
void SaveCenter3(int *lineL, int *line, int *lineR, char *returnpath);
main()
{
    int i = 0, fi = 0;
    //���ڻ����ļ�·�� 
    char tempoutput[100] = { 0 }, logfilename[100];
    LogInfo = (char*)malloc(sizeof(char) * 10000000);
    LogInfo[0] = '\0';

    printp("=============BUPT SMARTCAR FOR CCD====================\n");
    printp("** Designed by snowwolf                             **\n");
    printp("** Email: snowwolf2012@qq.com                       **\n");
    printp("** Picture property :                               **\n");
    printp("**              ROW:%3d   COLUMN:%3d                **\n", ROW, COLUMN);
    printf("%d %d %d", sizeof(filepath), 50 * sizeof(char), FILE_NUM);
    for (fi = 0; fi < FILE_NUM; fi++)
    {
        for (i = 0; i < ROW; i++)
            Line_Center[i] = COLUMN / 2;

        for (i = 0; i < ROW; i++)
            Line_Center_L[i] = 0;

        for (i = 0; i < ROW; i++)
            Line_Center_R[i] = COLUMN - 1;

        //��ȡͼ��Դ����   
        ReadFile(filepath[fi]);
        //��Դ���ݱ��� �����洦��ǰͼ�� 
        strcpy(tempoutput, filepath[fi]);
        strcat(tempoutput, ".txt");
        writereturn(Pic_Buffer, tempoutput, (int)0);

        //��ֵ�� 
        WritePicBlack();
        //����ֵ 
        //WritePicValue();
        /***********************************************************************/
        //�Լ�����ȡ�����㷨
        GetBlackLine(ROW, COLUMN);


        /************************************************************************/
        //��������� 
        SendCenterLine3(Line_Center_L, Line_Center, Line_Center_R);

        //�Ѵ�����ͼ����б��� 
        writereturn(Pic_Buffer, tempoutput, (int)1);
        //���������� 
        SaveCenter3(Line_Center_L, Line_Center, Line_Center_R, tempoutput);

    }
    //д��־ 
    sprintf(logfilename, "init_%d.log", time(NULL));
    writelog(LogInfo, logfilename);
    //����־�ļ� 
    system(logfilename);

    return 0;
}

/***************************************************
** ��������: void printp(char* format, ...)
** ��������: ��дprintf���������ļ�
** ��ڣ���
** ���ڣ�
** ˵��:
****************************************************/
void printp(char* format, ...)
{
    char s[10000];
    va_list arg_ptr;
    va_start(arg_ptr, format);
    _vsnprintf(s, sizeof(s) - 1, format, arg_ptr);
    //printf("%s",s);
    strcat(LogInfo, s);
}
/***************************************************
** ��������: WritePicValue
** ��������: �Ҷ�ֵ��ʽ���ͼ��
** ��ڣ�
** ���ڣ�
** ˵��: �����ã���ȡ����ͼ��
****************************************************/
void WritePicValue()
{
    int rows = 0, cols = 0;
    for (rows = 0; rows < ROW; rows++)
    {
        for (cols = 0; cols < COLUMN; cols++)
        {
            printp("%4d", Pic_Buffer[rows][cols]);
        }
        printp("\n");
    }
    printp("\n\n\n");
}
/***************************************************
** ��������: WritePicBlack
** ��������: �� * ��ʾ��ɫ���ͼ��
** ��ڣ�
** ���ڣ�
** ˵��: �����ã���ȡ����ͼ��
****************************************************/
void WritePicBlack()
{
    unsigned char rows = 0, cols = 0;

    for (rows = 1; rows < ROW; rows++)
    {
        printp("%2d", rows);
        for (cols = 0; cols < COLUMN; cols++)
        {
            if (Pic_Buffer[rows][cols] < THRESHOLD)
                printp("*");
            else
                printp(" ");
        }
        printp("\n");
    }
    printp("\n");

}
signed int get_mid(signed int a, signed int b, signed int c)
{
    unsigned int x = 0;
    if (a > b) { x = b; b = a; a = x; }
    if (b > c) { x = c; c = b; b = x; }
    if (a > b) { x = b; b = a; a = x; }
    return b;
}
unsigned char get_mid8(unsigned char a, unsigned char b, unsigned char c)
{
    unsigned char x = 0;
    if (a > b) { x = b; b = a; a = x; }
    if (b > c) { x = c; c = b; b = x; }
    if (a > b) { x = b; b = a; a = x; }
    return b;
}

/*
**************************************************
* ��������: OptimizeCenterLine
* ��������: ·���˲�(�Ż�)
* ��ڣ�
* ���ڣ�
* ˵��: ǰ��ȡ��ֵ
***************************************************
*/
void  OptimizeCenterLine()
{

}

/*
********************************************************************
* ��������: void ImproveSingleRow
*           (unsigned char irows, unsigned char llimit, unsigned char rlimit, unsigned imp)
* ��������:
* ��ڣ�
* ���ڣ�
* ˵��: ���쳣��ȡ�����ң��ϵ�ƽ��
********************************************************************
*/
void ImproveSingleRow(unsigned char irows, unsigned char llimit, unsigned char rlimit)
{

}//end of void ImproveSingleRow(unsigned char irows, unsigned char llimit, unsigned char rlimit, unsigned imp)

/*
**************************************************
* ��������: void GetBlackLine()
* ��������: ȡ�ú���
* ��ڣ�
* ���ڣ�
* ˵��:
***************************************************
*/
/*=== ��ȡ���ߺ������㷨������ ===*/
//#define BOUND_RADIUS 5 // �߽������뾶
//#define CROSSROAD_THRESHOLD 7 // ʮ��·�ڲ���������ֵ
/*=== ��ȡ���ߺ������㷨������ ===*/
 
#define G_PRINT 1                                    //������ĳ�0�Ϳ��Բ���ӡGetBlackLine()�е������Ϣ 
/*void GetBlackLine()
{
    static int threshold = THRESHOLD, // Ԥ����̬��ֵ
               crossroad = 0; // ʮ��·�ڱ�־����
    int row, // �к�
        column, // �к�
        leftline_leftbound = 0, // ����������߽磬�ʼΪȫͼ����߽�
        leftline_rightbound = COLUMN / 2, // ���������ұ߽磬�ʼΪȫͼ�м���
        leftline_lost = 0, // ���������Ƿ���
        leftline_lastvalid = 0, // ���һ����Ч���ߵ�ֵ
        rightline_leftbound = COLUMN / 2, // ����������߽磬�ʼΪȫͼ�м���
        rightline_rightbound = COLUMN - 1, // ���������ұ߽磬�ʼΪȫͼ���ұ߽�
        rightline_lost = 0, // ���������Ƿ���
        rightline_lastvalid = 0; // ���һ����Ч���ߵ�ֵ
    float complement_k = 0.0; // ����б��
    for (row = ROW - 1; row >= 0; row--)
    {
        Line_Center[row] = Line_Center_L[row] = Line_Center_R[row] = -1; // ��λ���н������
        leftline_lost = rightline_lost = 0; // ��λ�����߶��߱��
        for (column = leftline_rightbound; column >= leftline_leftbound; column--)
        { // ������߽�
            if (Pic_Buffer[row][column - 1] < threshold && 
                Pic_Buffer[row][column]     < threshold && 
                Pic_Buffer[row][column + 1] > threshold   )
            {
                leftline_lastvalid = Line_Center_L[row] = column;
                leftline_leftbound = column - BOUND_RADIUS > 0 ? column - BOUND_RADIUS : 1;
                leftline_rightbound = column + BOUND_RADIUS < COLUMN ? column + BOUND_RADIUS : COLUMN - 2;
                break;
            }
        }
        
        for (column = rightline_leftbound; column <= rightline_rightbound; column++)
        { // �����ұ߽�
            if (Pic_Buffer[row][column - 1] > threshold && 
                Pic_Buffer[row][column]     < threshold && 
                Pic_Buffer[row][column + 1] < threshold   )
            {
                Line_Center_R[row] = column;
                rightline_leftbound = column - BOUND_RADIUS > 0 ? column - BOUND_RADIUS : 1;
                rightline_rightbound = column + BOUND_RADIUS < COLUMN ? column + BOUND_RADIUS : COLUMN - 1;
                break;
            }
        }
        
        if (Line_Center_L[row] == -1 && Line_Center_R[row] > 0)
        { // ���߶��ߣ�����Ϊ��ת
            Line_Center_L[row] = row < ROW - 1 ? Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) : 0;
        }
        else if (Line_Center_L[row] > 0 && Line_Center_R[row] == -1)
        { // ���߶��ߣ�����Ϊ��ת
            Line_Center_R[row] = row < ROW - 1 ? Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) : COLUMN - 1;
        }
        else if (Line_Center_L[row] == -1 && Line_Center_R[row] == -1)
        { // ������ͬʱ���ߣ�����Ϊʮ��·��
            crossroad++;
        }

        Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // �������� 
    }
}  //end GetBlackLine()*/ 
 
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

        /*if (singleline_mode == 1) {
            // ����Ϊ������
            for (column = leftline_rightbound; column >= leftline_leftbound; column--)
            {
                if (Pic_Buffer[row][column + 1] - Pic_Buffer[row][column] >= DELTA_THRESHOLD &&
                    Pic_Buffer[row][column] - Pic_Buffer[row][column - 1] <= DELTA_THRESHOLD &&
                    Pic_Buffer[row][column] <= THRESHOLD)
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
                if (Pic_Buffer[row][column - 1] - Pic_Buffer[row][column] >= DELTA_THRESHOLD &&
                    Pic_Buffer[row][column] - Pic_Buffer[row][column + 1] <= DELTA_THRESHOLD &&
                    Pic_Buffer[row][column] <= THRESHOLD)
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
        }*/ 


        // ������һ�����������ұ߽�������߽��������Χ
        if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid && Line_Center_R[row + 1] == rightline_lastvalid)
       //��һ�����߲����������Ч��ֵ����һ�����ߵ��������Ч��ֵ 
        //if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid)
        //��һ�����߲����������Ч��ֵ����ʾ�ϴ�δ�ҵ����� 
        { 
            leftline_rightbound = Line_Center_R[row + 1] - 1;  //�����ұ߽� Ϊ�ϴε����� 
            if (leftline_rightbound <= leftline_leftbound)
            {
                leftline_leftbound = leftline_rightbound - 2 * BOUND_RADIUS > COLUMN_START ?
                    leftline_rightbound - 2 * BOUND_RADIUS : COLUMN_START + 1;
            }
        }

        // ������߽�
        for (column = leftline_rightbound; column >= leftline_leftbound; column--)
        {
            if (Pic_Buffer[row][column + 1] - Pic_Buffer[row][column] >= DELTA_THRESHOLD &&
                Pic_Buffer[row][column] - Pic_Buffer[row][column - 1] <= DELTA_THRESHOLD &&
                Pic_Buffer[row][column] <= THRESHOLD)
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
            rightline_leftbound = Line_Center_L[row] + 1;    //������߽�Ϊ���� 
            if (rightline_leftbound >= rightline_rightbound)
            {
                rightline_rightbound = rightline_leftbound + 2 * BOUND_RADIUS < COLUMN_END ?
                    rightline_leftbound + 2 * BOUND_RADIUS : COLUMN_END - 1;
            }
        }

        // �����ұ߽�
        for (column = rightline_leftbound; column <= rightline_rightbound; column++)
        {
            if (Pic_Buffer[row][column - 1] - Pic_Buffer[row][column] >= DELTA_THRESHOLD &&
                Pic_Buffer[row][column] - Pic_Buffer[row][column + 1] <= DELTA_THRESHOLD &&
                Pic_Buffer[row][column] <= THRESHOLD)
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
            if (crossroad >= CROSSROAD_THRESHOLD) 
			{
                crossroad++;
                // �����һ���ҵ�������λ����������������߽�
                leftline_leftbound = leftline_lastvalid != -1 && leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // ���м俪ʼ����
                leftline_rightbound = CENTER;
            }
           /* else 
			{
                tmp = row < ROW_START && Line_Center[row + 1] != -1 ? Line_Center[row + 1] : CENTER;
                if (tmp - SINGLE_RADIUS <= Line_Center_R[row] && Line_Center_R[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_R[row];
                    singleline_mode = 2;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
            }*/ 
            leftline_lost++;
            // ������
            Line_Center_L[row] = row < ROW_START && Line_Center_L[row + 1] != -1 ?
                Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) :
                Line_Center_R[row] - complement_dist; //COLUMN_START
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
            /*else {
                tmp = row < ROW_START && Line_Center[row + 1] != -1 ? Line_Center[row + 1] : CENTER ;
                if (tmp - SINGLE_RADIUS <= Line_Center_L[row] && Line_Center_L[row] <= tmp + SINGLE_RADIUS) {
                    Line_Center[row] = Line_Center_L[row];
                    singleline_mode = 1;
#ifdef G_PRINT
                    printp("Line %d find single line: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
                    continue;
                }
            }*/ 
            
            rightline_lost++; // �������߶�ʧ����

            // ���Ը���ǰһ��������������λ���Լ���������λ��ȷ����������λ��
            Line_Center_R[row] = row < ROW_START && Line_Center_R[row + 1] != -1 ?
                Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) :     //�������Ʋ��䣬ȡ��һ��б�� 
                //Line_Center_L[row] + complement_dist ;//COLUMN_END    �ս�����ǵ��ߣ�����Ϊ����ƫ�̶����� 
                COLUMN ;//COLUMN_END   �ս�����ǵ��ߣ����߸�Ϊ�߽� 
            
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
                /*if (tmp - SINGLE_RADIUS <= Line_Center_L[row] && Line_Center_L[row] <= tmp + SINGLE_RADIUS) {
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
                }*/ 
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // �������� 
            }  
#ifdef G_PRINT
            printp("Line %d find out both lines: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
    }
}  //end GetBlackLine()

 

/***************************************************
** ��������: void ReadFile(char * inpath)
** ��������: ���ļ���ȡͼ������
** ��ڣ���
** ���ڣ�
** ˵��:
****************************************************/
void ReadFile(char * inpath)
{
    FILE *fp;
    int row = 0, col = 0, i = 0;
    char temp;

    if ((fp = fopen(inpath, "r")) == NULL)
    {
        printf("cannot open %s\n", inpath);
        printp("cannot open %s\n", inpath);
        system("pause");
        return;
    }
    else
    {
        printp("Open %s successfully.\n", inpath);
        printf("Open %s successfully.\n", inpath);
    }


    while (!feof(fp) && row < ROW)
    {
        fscanf(fp, "%d", &Pic_Buffer[row][col++]);
        fscanf(fp, "%c", &temp);

        if (temp == '\n')
        {
            col = 0;
            row++;
        }
    }
    fclose(fp);
}
/***************************************************
** ��������: void writelog(char *info,char *outpath)
** ��������: д��־�ļ�
** ��ڣ���
** ���ڣ�
** ˵��:
****************************************************/
void writelog(char *info, char *outpath)
{
    FILE *fp;

    printp("Write file %s\n", outpath);
    if ((fp = fopen(outpath, "w+")) == NULL)
    {
        printf("cannot open %s\n", outpath);
        printp("cannot open %s\n", outpath);
        system("pause");
        return;
    }
    else
    {
        printp("Open %s successfully.\n", outpath);
        printf("Open %s successfully.\n", outpath);
    }
    fprintf(fp, "%s", info);
    fclose(fp);
}
/*
***************************************************
** ��������: void SendCenterLine(unsigned int * templine)
** ��������: ���������
** ��ڣ�����������
** ���ڣ�
** ˵��: ���������������
***************************************************
*/
void SendCenterLine3(int * templineL, int * templine, int * templineR)
{
    int i, j, temp = 0;

    printp("Center Line :\n");

    printp("              ");
    for (i = 0; i < COLUMN; i++)
    {
        if (i % 10 != 0)
            printp("%d", i % 10);
        else
            printp("%d", (i % 100) / 10);
    }
    printp("\n");

    for (i = 0; i < ROW; i++)
    {
        printp("%2d", i);
        printp("-%3d-%3d-%3d", templineL[i], templine[i], templineR[i]);

        temp = templineL[i];
        for (j = 0; j<temp; j++)
        {
            printp(" ");
        }

        if (templine[i] > templineL[i])
        {
            printp("��");
            j++;
        }

        temp = templine[i];
        for (; j < temp; j++)
        {
            printp(" ");
        }
        printp("*");

        if (templineR[i] > templine[i])
        {
            j++;
            temp = templineR[i];
            for (; j < temp; j++)
            {
                printp(" ");
            }
            printp("��\n");
        }
        else
            printp("\n");
    }
    printp("              ");
    for (i = 0; i < COLUMN; i++)
    {
        if (i % 10 != 0)
            printp("%d", i % 10);
        else
            printp("%d", (i % 100) / 10);
    }
    printp("\n");

}
/***************************************************
** ��������: void writereturn(unsigned char **temp, char *returnpath, int model)
** ��������: ������д�ص��ļ�
** ��ڣ����ݣ��ļ�·����ģʽ��0�½���1��д
** ���ڣ�
** ˵��:
****************************************************/
void writereturn(unsigned char temp[][COLUMN], char *returnpath, int model)
{
    FILE *fp = NULL;
    unsigned char frow = 0, fcol = 0;
    printf("Write data to %s\n", returnpath);
    if (model == 0) //new  
    {
        if ((fp = fopen(returnpath, "w+")) == NULL)
        {
            printf("return cannot open %s\n", returnpath);
            system("pause");
            return;
        }
    }
    else if (model == 1)//apend
    {
        if ((fp = fopen(returnpath, "a+")) == NULL)
        {
            printf("return cannot open %s\n", returnpath);
            system("pause");
            return;
        }
    }
    for (frow = 0; frow < ROW; frow++)
    {
        for (fcol = 0; fcol < COLUMN; fcol++)
        {
            fprintf(fp, "%4d", temp[frow][fcol]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");

    fclose(fp);
}
/***************************************************
** ��������: void SaveCenter(int *line,char *returnpath)
** ��������: �������߱��浽�ļ�
** ��ڣ���
** ���ڣ�
** ˵��:
****************************************************/
void SaveCenter3(int *lineL, int *line, int *lineR, char *returnpath)
{
    unsigned char tempBuffer[ROW][COLUMN] = { 0 };
    int srow = 0, scol = 0, i = 0;

    for (srow = 1; srow < ROW; srow++)
        for (scol = 0; scol < COLUMN; scol++)
        {
        if (scol == lineL[srow] || scol == line[srow] || scol == lineR[srow])
            tempBuffer[srow][scol] = 5;
        else
            tempBuffer[srow][scol] = 250;
        }
    writereturn(tempBuffer, returnpath, 1);
}
