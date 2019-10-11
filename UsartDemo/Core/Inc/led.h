#ifndef _LED_H_
#define _LED_H_

#include "gpio.h"

#define on GPIO_PIN_SET
#define off GPIO_PIN_RESET

#define ca

void ledOn(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin);

void ledOff(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin);

void ledToggle(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin);

#endif
