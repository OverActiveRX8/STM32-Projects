/**
 * @FileName: main.h
 * @Description: STM32F407 pulse width measurement main progarm 
 * @Author: Patrick John Palanas
 * @Date: 2019/10/19
 * @Others: Using open source GUI lib "LittleVGL" by Gabor "kisvegabor" Kiss-Vamosi
 *          Using TFTLCD lib by ALIENTEK
 */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "touch.h"
#include "usmart.h"
#include "usart.h"
#include "stdbool.h"
#include "lvgl.h"
#include "screen.h"

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
