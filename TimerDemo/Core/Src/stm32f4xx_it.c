/**
 * @FileName: stm32f4xx_it.c
 * @Description: STM32F407 pulse width measurement IT callback Functions
 * @Author: Patrick John Palanas
 * @Date: 2019/10/19
 */

#include "main.h"
#include "stm32f4xx_it.h"
#include "lvgl.h"

//Personal Variables
extern int icValue;             //IC Value
extern uint8_t olCounter;				//Timer Overload Counter
bool icState = false;						//Polarity State (false=>rising, true=>falling)
uint32_t timerCounter = 0;			//Timer Value Counter
extern int pulsePeriod;					//Pulse Width

//External Handles
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim14;

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void){}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1){}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  while (1){}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  while (1){}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  while (1){}
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void){}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void){}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void){}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	//LVGL Required Timer ITs
	lv_tick_inc(10);
	lv_task_handler();
  HAL_TIM_IRQHandler(&htim14);
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
	olCounter ++;															//Timer Overload Counter Add By 1 After IT
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim7);
	timerCounter ++;
	if(timerCounter == pulsePeriod)   			  //If Counter Equals To Pulse Width
	{
		HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_1);		//Toggle GPIO State
		timerCounter = 0;		                    //Reset Counter
	}
}

/**
  * @brief This function handles IC interrupt.
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(!icState)
		{
			__HAL_TIM_SetCounter(&htim2, 0);																					//Reset IC counter
			HAL_TIM_Base_Start_IT(&htim6);																						//Start Timer6 (Overload Counter)
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);													
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);			//Reset Polarity
			icState = true;																														//Toggle State
		}
		else
		{
			HAL_TIM_Base_Stop_IT(&htim6);																							//Stop Timer6 (Overload Counter)
			__HAL_TIM_SetCounter(&htim6, 0);																					//Reset Timer6 Counter
			icValue = 0;																															//Reset icValue
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);			//Reset Polarity
			icValue += HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);							//Get IC Capture Value
			icValue += olCounter * 0xFFFF;																						//Add Overload Value
			icValue *= 2;   																													//Transfer into us
			olCounter = 0;																														//Reset Overload Counter
			icState = false;																		                      //Toggle State
		}
	}
}
