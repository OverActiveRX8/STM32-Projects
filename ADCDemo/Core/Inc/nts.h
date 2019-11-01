/**
 * @FileName: nts.h
 * @Description: Use for transforming numbers into strings(supporting int float double & long)
 * @Author: Patrick John Palanas
 * @Date: 2019/11/1
 */

#ifndef _NTS_H_
#define _NTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief get the length of an integer
 */
int intSize(int value);

/**
 * @brief: Transfer float into string
 * @Param: value => transfer number (float)
					 length => transfer length after dot(int)
					 addon => the string following the number after convertion (char*)
 * @Rtvl: Converted String (Number+Addon) (char*)
 */
char* float2string(float value, int length, char* addon);
char* double2string(double value, int length, char* addon);

/**
 * @brief: Transfer float into string
 * @Param: value => transfer number (int)
					 length => transfer length (int)
					 addon => the string following the number after convertion (char*)
 * @Rtvl: Converted String (Number+Addon) (char*)
 */
char* int2String(int value, int length, char* addon);
char* long2String(long value, int length, char* addon);

#endif //_NTS_H_
