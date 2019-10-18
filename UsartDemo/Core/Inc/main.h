#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

//Define DMASolution to use polling, define ITSolution to use IT
//#define DMASolution
#define ITSolution

//LED @PF9
#define LED GPIOF,GPIO_PIN_9

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif
