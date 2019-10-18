#include "main.h"
#include "stm32f4xx_it.h"
#include "led.h"
#include "stdbool.h"

int counter = 0;

extern TIM_HandleTypeDef htim7;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;

extern bool state;

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
  while (1)
  {

  }
}

void MemManage_Handler(void)
{
  while (1)
  {

  }
}

void BusFault_Handler(void)
{
  while (1)
  {
		
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
		
  }
}

void SVC_Handler(void)
{
	
}


void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{
  HAL_IncTick();
}


void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}

void TIM7_IRQHandler(void)
{
	#ifdef ITSolution
  HAL_TIM_IRQHandler(&htim7);
	//Counter add one after each IT callback
	counter ++;
	//If state = 1, LED toggles rapidly, if state = 0, LED works regularly
	if(state)
	{
		ledToggle(LED);
		if(counter == 8){
			//After toggle, change the Usart working state back to false
			state = false;
			counter = 0;
		}
	}
	else if(counter == 10)
	{
		ledToggle(LED);
		counter = 0;
	}
	#endif
}

void DMA2_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
}
