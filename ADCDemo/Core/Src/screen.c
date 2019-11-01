/**
 * @FileName: screen.c
 * @Description: STM32F407 screen display program
 * @Author: Patrick John Palanas
 * @Date: 2019/10/19
 * @Others: Using open source GUI lib "LittleVGL" by Gabor "kisvegabor" Kiss-Vamosi
 *          Using TFTLCD lib by ALIENTEK
 */

#include "screen.h"

//Define Button Size
#define buttonWidth 60
#define buttonHeight 80

//Text areas
lv_obj_t *temp_ta;    
lv_obj_t *vdc_ta;    
lv_obj_t *vac_ta;      
lv_obj_t *avg_ta; 
lv_obj_t *rms_ta; 
lv_obj_t *vpp_ta; 

char *label_str = "Temp & Voltage Measurement";
char *ta1_str = "Temperature:";
char *ta2_str = "DC Voltage @PA0:";
char *ta3_str = "AC Volatge @PA4:";
char *ta4_str = "AC Volatge AVG:";
char *ta5_str = "AC Volatge RMS:";
char *ta6_str = "AC Voltage VPP:";

/**
 * @brief: Display Parameters (sLables & TextAreas)
 *         Using LVGL lib
 */
void displayScr(void)
{
	//Screen Parameters
	lv_obj_t *scr = lv_page_create(NULL, NULL);
	lv_disp_load_scr(scr);
	
	//Label Parameters
  lv_obj_t *label = lv_label_create(scr, NULL); 
  lv_label_set_text(label, label_str);  
	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);  
	
	//temp_ta
	temp_ta = lv_ta_create(lv_scr_act(), NULL);
	lv_ta_set_one_line(temp_ta, true);
	lv_obj_set_width(temp_ta, 100);
	lv_obj_align(temp_ta, label, LV_ALIGN_IN_TOP_MID, 0, 80);
	lv_ta_set_text(temp_ta, "0.00 deg");
	lv_ta_set_cursor_type(temp_ta, NULL);
	lv_obj_t *temp_label = lv_label_create(scr,NULL);
	lv_label_set_text(temp_label, ta1_str);
	lv_obj_align(temp_label, temp_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
	
	//vdc_ta
	vdc_ta = lv_ta_create(lv_scr_act(), temp_ta);
	lv_ta_set_text(vdc_ta, "0.00 V");
	lv_obj_align(vdc_ta, temp_ta, LV_ALIGN_IN_BOTTOM_MID, 0, 80);
	lv_obj_t *vdc_label = lv_label_create(scr,NULL);
	lv_label_set_text(vdc_label, ta2_str);
	lv_obj_align(vdc_label, vdc_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
	
	//vac_ta
	vac_ta = lv_ta_create(lv_scr_act(), temp_ta);
	lv_ta_set_text(vac_ta, "0.00 V");
	lv_obj_align(vac_ta, vdc_ta, LV_ALIGN_IN_BOTTOM_MID, 0, 80);
	lv_obj_t *vac_label = lv_label_create(scr,NULL);
	lv_label_set_text(vac_label, ta3_str);
	lv_obj_align(vac_label, vac_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
	
	//avg_ta
	avg_ta = lv_ta_create(lv_scr_act(), temp_ta);
	lv_ta_set_text(avg_ta, "0.00 V");
	lv_obj_align(avg_ta, vac_ta, LV_ALIGN_IN_BOTTOM_MID, 0, 80);
	lv_obj_t *avg_label = lv_label_create(scr,NULL);
	lv_label_set_text(avg_label, ta4_str);
	lv_obj_align(avg_label, avg_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
	
	//rms_ta
	rms_ta = lv_ta_create(lv_scr_act(), temp_ta);
	lv_ta_set_text(rms_ta, "0.00 V");
	lv_obj_align(rms_ta, avg_ta, LV_ALIGN_IN_BOTTOM_MID, 0, 80);
	lv_obj_t *rms_label = lv_label_create(scr,NULL);
	lv_label_set_text(rms_label, ta5_str);
	lv_obj_align(rms_label, rms_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
	
	//vpp_ta
	vpp_ta = lv_ta_create(lv_scr_act(), temp_ta);
	lv_ta_set_text(vpp_ta, "0.00 V");
	lv_obj_align(vpp_ta, rms_ta, LV_ALIGN_IN_BOTTOM_MID, 0, 80);
	lv_obj_t *vpp_label = lv_label_create(scr,NULL);
	lv_label_set_text(vpp_label, ta6_str);
	lv_obj_align(vpp_label, vpp_ta, LV_ALIGN_IN_TOP_LEFT, 0, -30);
}
