#include "led.h"

//Common Cathode
#ifdef cc

void ledOn(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin){
	HAL_GPIO_WritePin(GPIOPort,GPIOPin,on);
}

void ledOff(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin){
	HAL_GPIO_WritePin(GPIOPort,GPIOPin,off);
}

#endif

//Common Anode
#ifdef ca

void ledOn(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin){
	HAL_GPIO_WritePin(GPIOPort,GPIOPin,off);
}

void ledOff(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin){
	HAL_GPIO_WritePin(GPIOPort,GPIOPin,on);
}

#endif

void ledToggle(GPIO_TypeDef *GPIOPort, uint32_t GPIOPin){
	HAL_GPIO_TogglePin(GPIOPort,GPIOPin);
}
