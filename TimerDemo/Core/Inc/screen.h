#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "lvgl.h"
#include "main.h"
#include "stdlib.h"

//Event Callback Functions
static void btn1event(lv_obj_t * btn, lv_event_t event);
static void btn2event(lv_obj_t * btn, lv_event_t event);
static void btn3event(lv_obj_t * btn, lv_event_t event);
static void btn4event(lv_obj_t * btn, lv_event_t event);
static void btn5event(lv_obj_t * btn, lv_event_t event);
static void btn6event(lv_obj_t * btn, lv_event_t event);

//Display Function
void displayScr(void);
char* int2String(int value, int length, char* addOn);
int intSize(int value);

extern int pulsePeriod;
extern uint32_t timerCounter;

#endif
