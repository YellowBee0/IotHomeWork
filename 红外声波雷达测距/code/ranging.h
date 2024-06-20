#ifndef __SHARP2Y0A21_H
#define __SHARP2Y0A21_H 
 
#include "main.h"
 
 
#define Adc1IN1Distance_READ_TIMES 10  //定义红外传感器读取次数,以便取平均值
 
void DistanceSensor_Init(void);     //初始化红外传感器
float DistanceSensor_Get_Val(void);    //读取红外传感器的值
 
 
#endif 