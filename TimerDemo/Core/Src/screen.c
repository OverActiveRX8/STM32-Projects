#include "screen.h"

#define buttonWidth 60
#define buttonHeight 80

lv_obj_t *output_ta;
lv_obj_t *input_ta;

void displayScr()
{
	//Screen Parameters
	lv_obj_t *scr = lv_page_create(NULL, NULL);
	lv_disp_load_scr(scr);
	
	//Label Parameters
  lv_obj_t *label = lv_label_create(scr, NULL); 
  lv_label_set_text(label, "Pulse Width Measurement");
  lv_obj_set_x(label, 50);   
	lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);  
	
	lv_obj_t *btn_label = lv_label_create(scr, NULL);
	lv_label_set_text(btn_label, "Adjust Pulse Width (by 10 us)");
	lv_obj_align(btn_label, label, LV_ALIGN_IN_BOTTOM_MID, 0, 50);  
	
	//Buttons
	lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn1, btn1event);       
	lv_obj_set_size(btn1,buttonWidth,buttonHeight);	
  lv_obj_align(btn1, label, LV_ALIGN_IN_TOP_MID, -100, 100);  
  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "+\n1");	
	
	lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn2, btn2event);      
	lv_obj_set_size(btn2,buttonWidth,buttonHeight);
  lv_obj_align(btn2, btn1, LV_ALIGN_IN_RIGHT_MID, 100, 0);   
  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, " +\n10");		
		
	lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn3, btn3event);   
	lv_obj_set_size(btn3,buttonWidth,buttonHeight);		
  lv_obj_align(btn3, btn2, LV_ALIGN_IN_RIGHT_MID, 100, 0); 
  label = lv_label_create(btn3, NULL);
  lv_label_set_text(label, "  +\n100");		
		
	lv_obj_t *btn4 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn4, btn4event);    
	lv_obj_set_size(btn4,buttonWidth,buttonHeight);
  lv_obj_align(btn4, btn1, LV_ALIGN_IN_BOTTOM_MID, 0, 100); 
  label = lv_label_create(btn4, NULL);
  lv_label_set_text(label, "-\n1");		
		
	lv_obj_t *btn5 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn5, btn5event);
	lv_obj_set_size(btn5,buttonWidth,buttonHeight);	
  lv_obj_align(btn5, btn4, LV_ALIGN_IN_RIGHT_MID, 100, 0); 
  label = lv_label_create(btn5, NULL);
  lv_label_set_text(label, " -\n10");		
		
	lv_obj_t *btn6 = lv_btn_create(lv_scr_act(), NULL);       
  lv_obj_set_event_cb(btn6, btn6event);    
	lv_obj_set_size(btn6,buttonWidth,buttonHeight);	
  lv_obj_align(btn6, btn5, LV_ALIGN_IN_RIGHT_MID, 100, 0); 
  label = lv_label_create(btn6, NULL);
  lv_label_set_text(label, "  -\n100");			
	
	output_ta = lv_ta_create(lv_scr_act(), NULL);
	lv_ta_set_one_line(output_ta, true);
	lv_obj_set_width(output_ta, 100);
	lv_obj_set_pos(output_ta, 185, 370);
	lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
	lv_ta_set_cursor_type(output_ta, NULL);
	
	lv_obj_t *ota_label = lv_label_create(scr,NULL);
	lv_label_set_text(ota_label, "Output Pulse Width");
	lv_obj_align(ota_label, output_ta, LV_ALIGN_IN_TOP_MID, 0, -30);
	
	input_ta = lv_ta_create(lv_scr_act(), NULL);
	lv_ta_set_one_line(input_ta, true);
	lv_obj_set_width(input_ta, 100);
	lv_obj_set_pos(input_ta, 185, 450);
	lv_ta_set_text(input_ta, "");
	lv_ta_set_cursor_type(input_ta, NULL);
	
	lv_obj_t *ita_label = lv_label_create(scr,NULL);
	lv_label_set_text(ita_label, "Input Pulse Width");
	lv_obj_align(ita_label, input_ta, LV_ALIGN_IN_TOP_MID, 0, -30);
	lv_ta_set_text(input_ta, "0us");
}

static void btn1event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod ++;
			timerCounter = 0;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
		}
}

static void btn2event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod += 10;
			timerCounter = 0;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
		}
}

static void btn3event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod += 100;
			timerCounter = 0;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
		}
}

static void btn4event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod --;
			timerCounter = 0;
			if(pulsePeriod<0) pulsePeriod = 1;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
		}
}

static void btn5event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod -= 10;
			timerCounter = 0;
		  if(pulsePeriod<0) pulsePeriod = 1;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));			
		}
}

static void btn6event(lv_obj_t * btn, lv_event_t event)
{
		if(event == LV_EVENT_PRESSED)
		{
			pulsePeriod -= 100;
			timerCounter = 0;
			if(pulsePeriod<0) pulsePeriod = 1;
			lv_ta_set_text(output_ta, int2String(pulsePeriod*10, intSize(pulsePeriod*10), "us"));
		}
}

char* int2String(int value, int length, char* addOn)
{
    char *string = malloc(sizeof(char) * (length+sizeof(addOn)+1));
    snprintf(string, length+1, "%d", value);
    strcat(string, addOn);
    return string;
}

int intSize(int value)
{
    value++;
    int count = 0;
    while(value!=0)
    {
        value /= 10;
        count++;
    }
    return count;
}