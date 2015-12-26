//内部使用请务外传！！
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#define ROW 120 //80 
#define COLUMN 210  //160

/*==== 使用python生成文件列表 ====*/

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

/*==== 使用python生成文件列表 ====*/
/* 
//黑白的跳变域值 
#define THRESHOLD 159  

//有效搜索宽度（有效区）       
#define SEARCHWITHDEN 12 
//无效搜索区域（黑区） 
#define SEARCHWITHDDIS 6
//扩展搜索区 
#define SEARCHWITHDEXT 30

#define COLUMN_START 1
#define COLUMN_END 126
#define CENTER     62*/ 
/*=== 提取边线和中线算法配置项 ===*/
#define ROW_START       (ROW-10)//3 
#define DELTA_THRESHOLD 30
//黑白的跳变域值 
#define THRESHOLD  115 //125
#define CENTER 119//119 // 实际图像中间值
#define BOUND_RADIUS 5 // 边界搜索半径
#define SINGLE_RADIUS 15      // 单线判别半径

#define LOSELL_THRESHOLD 7 // 左线丢失补线启发阈值
#define LOSERL_THRESHOLD 7 // 右线丢失补线启发阈值
#define CROSSROAD_THRESHOLD 7 // 十字路口补线启发阈值
//=== 提取边线和中线算法配置项 ===
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
    //用于缓存文件路径 
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

        //读取图像源数据   
        ReadFile(filepath[fi]);
        //把源数据保存 即保存处理前图像 
        strcpy(tempoutput, filepath[fi]);
        strcat(tempoutput, ".txt");
        writereturn(Pic_Buffer, tempoutput, (int)0);

        //二值化 
        WritePicBlack();
        //数据值 
        //WritePicValue();
        /***********************************************************************/
        //自己的提取黑线算法
        GetBlackLine(ROW, COLUMN);


        /************************************************************************/
        //输出中心线 
        SendCenterLine3(Line_Center_L, Line_Center, Line_Center_R);

        //把处理后的图像进行保存 
        writereturn(Pic_Buffer, tempoutput, (int)1);
        //保存中心线 
        SaveCenter3(Line_Center_L, Line_Center, Line_Center_R, tempoutput);

    }
    //写日志 
    sprintf(logfilename, "init_%d.log", time(NULL));
    writelog(LogInfo, logfilename);
    //打开日志文件 
    system(logfilename);

    return 0;
}

/***************************************************
** 函数名称: void printp(char* format, ...)
** 功能描述: 重写printf，并保存文件
** 入口：无
** 出口：
** 说明:
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
** 函数名称: WritePicValue
** 功能描述: 灰度值形式输出图像
** 入口：
** 出口：
** 说明: 调试用，看取到的图像
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
** 函数名称: WritePicBlack
** 功能描述: 以 * 表示黑色输出图像
** 入口：
** 出口：
** 说明: 调试用，看取到的图像
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
* 函数名称: OptimizeCenterLine
* 功能描述: 路线滤波(优化)
* 入口：
* 出口：
* 说明: 前后取中值
***************************************************
*/
void  OptimizeCenterLine()
{

}

/*
********************************************************************
* 函数名称: void ImproveSingleRow
*           (unsigned char irows, unsigned char llimit, unsigned char rlimit, unsigned imp)
* 功能描述:
* 入口：
* 出口：
* 说明: 对异常点取其左，右，上的平均
********************************************************************
*/
void ImproveSingleRow(unsigned char irows, unsigned char llimit, unsigned char rlimit)
{

}//end of void ImproveSingleRow(unsigned char irows, unsigned char llimit, unsigned char rlimit, unsigned imp)

/*
**************************************************
* 函数名称: void GetBlackLine()
* 功能描述: 取得黑线
* 入口：
* 出口：
* 说明:
***************************************************
*/
/*=== 提取边线和中线算法配置项 ===*/
//#define BOUND_RADIUS 5 // 边界搜索半径
//#define CROSSROAD_THRESHOLD 7 // 十字路口补线启发阈值
/*=== 提取边线和中线算法配置项 ===*/
 
#define G_PRINT 1                                    //把这里改成0就可以不打印GetBlackLine()中的输出信息 
/*void GetBlackLine()
{
    static int threshold = THRESHOLD, // 预备动态阈值
               crossroad = 0; // 十字路口标志变量
    int row, // 行号
        column, // 列号
        leftline_leftbound = 0, // 左线搜索左边界，最开始为全图最左边界
        leftline_rightbound = COLUMN / 2, // 左线搜索右边界，最开始为全图中间线
        leftline_lost = 0, // 本行左线是否丢线
        leftline_lastvalid = 0, // 最后一条有效左线的值
        rightline_leftbound = COLUMN / 2, // 右线搜索左边界，最开始为全图中间线
        rightline_rightbound = COLUMN - 1, // 右线搜索右边界，最开始为全图最右边界
        rightline_lost = 0, // 本行右线是否丢线
        rightline_lastvalid = 0; // 最后一条有效右线的值
    float complement_k = 0.0; // 补线斜率
    for (row = ROW - 1; row >= 0; row--)
    {
        Line_Center[row] = Line_Center_L[row] = Line_Center_R[row] = -1; // 复位该行结果数组
        leftline_lost = rightline_lost = 0; // 复位左右线丢线标记
        for (column = leftline_rightbound; column >= leftline_leftbound; column--)
        { // 搜索左边界
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
        { // 搜索右边界
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
        { // 左线丢线，可能为左转
            Line_Center_L[row] = row < ROW - 1 ? Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) : 0;
        }
        else if (Line_Center_L[row] > 0 && Line_Center_R[row] == -1)
        { // 右线丢线，可能为右转
            Line_Center_R[row] = row < ROW - 1 ? Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) : COLUMN - 1;
        }
        else if (Line_Center_L[row] == -1 && Line_Center_R[row] == -1)
        { // 左右线同时丢线，可能为十字路口
            crossroad++;
        }

        Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线 
    }
}  //end GetBlackLine()*/ 
 
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

        /*if (singleline_mode == 1) {
            // 左线为中心线
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
                // 从中间开始搜索
                leftline_rightbound = Line_Center[row + 1] - 1;
                rightline_leftbound = Line_Center[row + 1] + 1;
                // 按最后一次找到的右线位置重设右线搜索右边界
                rightline_rightbound = COLUMN_END - 1;
                singleline_mode = 0;
            }
        }*/ 


        // 根据上一次搜索到的右边界限制左边界的搜索范围
        if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid && Line_Center_R[row + 1] == rightline_lastvalid)
       //上一条左线不等于最近有效的值，上一条右线等于最近有效的值 
        //if (row < ROW_START && Line_Center_L[row + 1] != leftline_lastvalid)
        //上一条左线不等于最近有效的值，表示上次未找到左线 
        { 
            leftline_rightbound = Line_Center_R[row + 1] - 1;  //左线右边界 为上次的右线 
            if (leftline_rightbound <= leftline_leftbound)
            {
                leftline_leftbound = leftline_rightbound - 2 * BOUND_RADIUS > COLUMN_START ?
                    leftline_rightbound - 2 * BOUND_RADIUS : COLUMN_START + 1;
            }
        }

        // 搜索左边界
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

        // 根据搜索到的左边界限制右边界的搜索范围
        if (Line_Center_L[row] != -1 && rightline_leftbound < Line_Center_L[row])
        {
            rightline_leftbound = Line_Center_L[row] + 1;    //右线左边界为中线 
            if (rightline_leftbound >= rightline_rightbound)
            {
                rightline_rightbound = rightline_leftbound + 2 * BOUND_RADIUS < COLUMN_END ?
                    rightline_leftbound + 2 * BOUND_RADIUS : COLUMN_END - 1;
            }
        }

        // 搜索右边界
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

        // 左线丢线，可能为左转，也有可能仅仅是超出图像边界
        if (Line_Center_L[row] == -1 && Line_Center_R[row] > 0)
        {
            if (crossroad >= CROSSROAD_THRESHOLD) 
			{
                crossroad++;
                // 按最后一次找到的左线位置重设左线搜索左边界
                leftline_leftbound = leftline_lastvalid != -1 && leftline_lastvalid - BOUND_RADIUS > COLUMN_START ?
                    leftline_lastvalid - BOUND_RADIUS : COLUMN_START + 1;
                // 从中间开始搜索
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
            // 补左线
            Line_Center_L[row] = row < ROW_START && Line_Center_L[row + 1] != -1 ?
                Line_Center_L[row + 1] + (Line_Center_R[row] - Line_Center_R[row + 1]) :
                Line_Center_R[row] - complement_dist; //COLUMN_START
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
            
            rightline_lost++; // 增加右线丢失计数

            // 尝试根据前一行搜索到的右线位置以及本行左线位置确定本行右线位置
            Line_Center_R[row] = row < ROW_START && Line_Center_R[row + 1] != -1 ?
                Line_Center_R[row + 1] + (Line_Center_L[row] - Line_Center_L[row + 1]) :     //中线趋势不变，取上一次斜率 
                //Line_Center_L[row] + complement_dist ;//COLUMN_END    刚进入就是单线，中线为向右偏固定距离 
                COLUMN ;//COLUMN_END   刚进入就是单线，右线赋为边界 
            
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
                Line_Center[row] = (Line_Center_L[row] + Line_Center_R[row]) / 2; // 计算中线 
            }  
#ifdef G_PRINT
            printp("Line %d find out both lines: %d %d %d\n", row, Line_Center_L[row], Line_Center[row], Line_Center_R[row]);
#endif
        }
    }
}  //end GetBlackLine()

 

/***************************************************
** 函数名称: void ReadFile(char * inpath)
** 功能描述: 从文件读取图像数据
** 入口：无
** 出口：
** 说明:
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
** 函数名称: void writelog(char *info,char *outpath)
** 功能描述: 写日志文件
** 入口：无
** 出口：
** 说明:
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
** 函数名称: void SendCenterLine(unsigned int * templine)
** 功能描述: 输出中心线
** 入口：中心线数组
** 出口：
** 说明: 以左中右三线输出
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
            printp("。");
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
            printp("。\n");
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
** 函数名称: void writereturn(unsigned char **temp, char *returnpath, int model)
** 功能描述: 将数据写回到文件
** 入口：数据，文件路径，模式：0新建，1续写
** 出口：
** 说明:
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
** 函数名称: void SaveCenter(int *line,char *returnpath)
** 功能描述: 将中心线保存到文件
** 入口：无
** 出口：
** 说明:
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
