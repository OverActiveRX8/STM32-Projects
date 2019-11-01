/**
 * @FileName: nts.c
 * @Description: Use for transforming numbers into strings(supporting int float double & long)
 * @Author: Patrick John Palanas
 * @Date: 2019/11/1
 */

#include "nts.h"

char* int2String(int value, int length, char* addon)
{
    char *string = malloc(sizeof(char) * (length+sizeof(addon)+1));
    snprintf(string, length+1, "%d", value);
    strcat(string, addon);
    return string;
}

char* float2string(float value, int length, char* addon) {
    int temp = (int)value;
    value = value - (float)temp;
    char *string= malloc(sizeof(char)*(intSize(temp)+2+length+sizeof(addon)));
    snprintf(string,length+3,"%f",value);
    string = strchr(string, '.');
    string = strcat(int2String(temp,intSize(temp),""),string);
    return  strcat(string,addon);
}

int intSize(int value)
{
    value++;
    int count = 0;
    while(value!=0)
    {
        value /= 10;
        count++;
    }
    return count;
}

char* double2string(double value, int length, char* addon) {
    int temp = (int)value;
    value = value - (double)temp;
    char *string= malloc(sizeof(char)*(intSize(temp)+2+length+sizeof(addon)));
    snprintf(string,length+3,"%lf",value);
    string = strchr(string, '.');
    string = strcat(int2String(temp,intSize(temp),""),string);
    return  strcat(string,addon);
}

char* long2String(long value, int length, char* addon) {
    char *string = malloc(sizeof(char) * (length+sizeof(addon)+1));
    snprintf(string, length+1, "%ld", value);
    strcat(string, addon);
    return string;
}