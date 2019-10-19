#include "main.h"         
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"                  
#include "stdbool.h"
#include "string.h"

#ifdef DMASolution
//BufferSize = 500 while using DMA method
#define bufferSize 500
//This array constantly equals to zero(for comparing)
const uint8_t temp[bufferSize] = {0};
#endif

#ifdef ITSolution
//BufferSize = 1 while using IT method
#define bufferSize 1
//false => usart is not working. true => usart is in use
bool state = false;
#endif

//Buffer to save the data received
uint8_t rxBuffer[bufferSize] = {0};

void SystemClock_Config(void);
int arrayCompare(uint8_t* Array1, uint8_t* Array2, int size);

//DMA handle
extern DMA_HandleTypeDef hdma_usart1_rx;
//counter for LED toggles
extern int counter;

int main(void)
{
	//System Initializations
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM7_Init();

	#ifdef DMASolution
	//Using DMA to save the received data into memory
	HAL_UART_Receive_DMA(&huart1,rxBuffer,sizeof(rxBuffer));
	#endif
	
	#ifdef ITSolution
	//Save the received data into memory
	HAL_UART_Receive_IT(&huart1,rxBuffer,sizeof(rxBuffer));
	//Start timer7 IT
	HAL_TIM_Base_Start_IT(&htim7);
	#endif

	//Loop
  while (1)
  {
		#ifdef DMASolution
		//Get DMA Transport Status
		if(!arrayCompare((uint8_t *)temp,rxBuffer,bufferSize))
		{
			//Transmit the received data
			HAL_UART_Transmit(&huart1,rxBuffer,sizeof(rxBuffer),0xffff); 
			//Clear the buffer
			memcpy(rxBuffer,temp,bufferSize);
			//Led toggle 5 times
			for(int i=0;i<5;i++)
			{
				ledOn(LED);
				HAL_Delay(100);
				ledOff(LED);
				HAL_Delay(100);
			}
		}
		else
		{
			//Led works in regular state
			ledOn(LED);
			HAL_Delay(1000);
			ledOff(LED);
			HAL_Delay(1000);			
		}
		#endif
  }
}

/*
 * @brief Initialize system clock
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}


#ifdef DMASolution
/*
 * @brief Compare two arrays
 * @retval equal => 1
 */
int arrayCompare(uint8_t* array1, uint8_t* array2, int size){
	for(int i = 0; i < size; i++){
		if(array1[i] != array2[i])
			return 0;
	}	
	return 1;
}
#endif

#ifdef ITSolution
//Uart IT call back function
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1)
	{
		//Transmit the received data
		HAL_UART_Transmit(&huart1,rxBuffer,sizeof(rxBuffer),0);
		//Restart the usart IT
		HAL_UART_Receive_IT(&huart1,rxBuffer,sizeof(rxBuffer));
		//Change the USART working state into true
		state = true;
		//Clear the LED counter
		counter = 0;
	}
}
#endif

//Error handler function
void Error_Handler(void)
{
	ledOn(LED);
}
