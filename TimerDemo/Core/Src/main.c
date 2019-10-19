/**
 * @FileName: main.c
 * @Description: STM32F407 pulse width measurement main progarm 
 * @Author: Patrick John Palanas
 * @Date: 2019/10/19
 * @Others: Using open source GUI lib "LittleVGL" by Gabor "kisvegabor" Kiss-Vamosi
 *          Using TFTLCD lib by ALIENTEK
 */

#include "main.h"
#include "tim.h"
#include "gpio.h"

//Personal Variables
int icValue = 0;	    		//IC Value 
uint8_t olCounter = 0; 		//Timer Overload Counter
int pulsePeriod = 10;		  //Initial Output Pulse Width (*10us)

//LVGL Input TextArea Object
extern lv_obj_t *input_ta; 

//LVGL Driver Variables
static lv_disp_buf_t disp_buf; 
static lv_color_t buf[LV_HOR_RES_MAX * 10];    
lv_disp_drv_t disp_drv;  
lv_indev_drv_t indev_drv;

//HAL CLK Function Declaration
void SystemClock_Config(void);

//LVGL Driver Function Declarations
void my_disp_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * color_p);
bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);

/**
 * @brief: Main Function
 */
int main(void)
{
	//System Initializations
  HAL_Init();
  SystemClock_Config();		//CLK
  MX_GPIO_Init();    			//GPIO
  MX_TIM2_Init();		 			//Timers
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_TIM14_Init();
  
	//TFTLCD Initializations
	delay_init(168);        //Delay Functions
	uart_init(115200);      //UART    
	usmart_dev.init(84); 		//USMART    
 	LCD_Init();      				//LCD
	tp_dev.init();					//Touch Screen 
	LCD_Clear(WHITE);				//Clear LCD
	lv_init();							//Lvgl 
	
	//LVGL Driver Initializations
	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);  /*Initialize the display buffer*/
	lv_disp_drv_init(&disp_drv);         													/*Basic initialization*/
	disp_drv.flush_cb = my_disp_flush;    												/*Set your driver function*/
	disp_drv.buffer = &disp_buf;                                  /*Assign the buffer to the display*/
	lv_disp_drv_register(&disp_drv);                              /*Finally register the driver*/
	lv_indev_drv_init(&indev_drv);                                /*Descriptor of a input device driver*/
	indev_drv.type = LV_INDEV_TYPE_POINTER;                       /*Touch pad is a pointer-like device*/
	indev_drv.read_cb = my_touchpad_read;                         /*Set your driver function*/
	lv_indev_drv_register(&indev_drv);                            /*Finally register the driver*/
	     
	//Start Timer IT
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim14);
	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);
	
	//Display Screen
	displayScr();

	//Loop
  while (1)
  {
		lv_ta_set_text(input_ta, int2String(icValue, intSize(icValue), "us"));  //Print IC Value onto LCD (by LVGL)
		HAL_Delay(100);																													//Delay 100ms
  }
}

/**
 *@brief System CLK Configuration
 */
void SystemClock_Config(void){
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

/**
 * @brief: LVGL Display Driver Function
 */
void my_disp_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
						LCD_Fast_DrawPoint(x,y,color_p->full);
            color_p++;
        }
    }
		lv_disp_flush_ready((lv_disp_drv_t *)disp);       
}

/**
 * @brief: LVGL Input Driver Function
 */
bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
		tp_dev.scan(0); 
    data->state = tp_dev.sta&TP_PRES_DOWN ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
    if(data->state == LV_INDEV_STATE_PR) 
		{
			last_x = tp_dev.x[0];
			last_y = tp_dev.y[0];
		}
    data->point.x = last_x;
    data->point.y = last_y;
		return false; 
}

/**
 * @brief: HAL Error Handles
 */
void Error_Handler(void){}
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line){}
#endif /* USE_FULL_ASSERT */
