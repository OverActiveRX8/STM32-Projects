#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

//ADC buffer
dmaArray adc1, adc2;
float temp = 0;
float vdc = 0;
float vref = 0;
float vac = 0;
float vacAvg = 0;
float vacRms = 0; 
float vacVpp = 0;

//AC Parameters Calculator
ACBuff rmsBuffer, avgBuffer;

//Text Areas
extern lv_obj_t *temp_ta;    
extern lv_obj_t *vdc_ta;    
extern lv_obj_t *vac_ta;      
extern lv_obj_t *avg_ta; 
extern lv_obj_t *rms_ta; 
extern lv_obj_t *vpp_ta; 

//Lvgl
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];    
lv_disp_drv_t disp_drv;  
lv_indev_drv_t indev_drv;
void my_disp_flush(lv_disp_t * disp, const lv_area_t * area, lv_color_t * color_p);
bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data);

//System CLK
void SystemClock_Config(void);

int debugWatch = 0;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
	delay_init(168);       
	uart_init(115200);   
	usmart_dev.init(84); 		    
	
	LCD_Init();      			
	tp_dev.init();				
	LCD_Clear(WHITE);
	POINT_COLOR = BLUE;			
	lv_init();						
	
	adcarrayInit(&adc1, 200, 100);
	adcarrayInit(&adc2, 200, 100);
	
	rmsBuffer = InitBuff(20);
	avgBuffer = InitBuff(20);

	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim6);
	
	adcarrayInit(&adc1, 200, 100);
	adcarrayInit(&adc2, 200, 100);
	
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&(*adc1.array), 200);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)&(*adc2.array), 200);
	
	//lvgl setup
	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10); 
	lv_disp_drv_init(&disp_drv);         
	disp_drv.flush_cb = my_disp_flush;  
	disp_drv.buffer = &disp_buf;         
	lv_disp_drv_register(&disp_drv);     
	lv_indev_drv_init(&indev_drv);            
	indev_drv.type = LV_INDEV_TYPE_POINTER;    
	indev_drv.read_cb = my_touchpad_read;     
	lv_indev_drv_register(&indev_drv);       

	displayScr();
	
  while (1)
  {
		vacVpp = getMax(avgBuffer->Buff->Array, avgBuffer->Buff->Capacity) 
				- getMin(avgBuffer->Buff->Array, avgBuffer->Buff->Capacity);
		lv_ta_set_text(temp_ta, float2string(temp, 2," deg"));
		lv_ta_set_text(vdc_ta, float2string(vdc, 2," V"));
		lv_ta_set_text(vac_ta, float2string(vac, 2," V"));
		lv_ta_set_text(rms_ta, float2string(vacRms, 2," V"));
		lv_ta_set_text(avg_ta, float2string(vacAvg, 2," V"));
		lv_ta_set_text(vpp_ta, float2string(vacVpp, 2," V"));
		HAL_Delay(1000);
  }
}

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

void Error_Handler() 
{
		debugWatch ++;
}

	