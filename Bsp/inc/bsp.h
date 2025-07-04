#ifndef __BSP_H
#define __BSP_H
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"


#include "usart.h"
#include "dma.h"


#include "bsp_smg.h"
#include "bsp_cmd_link.h"
#include "bsp_run.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_fan.h"
#include "bsp_tm1639.h"
#include "bsp_display_dynamic.h"
#include "bsp_display.h"
#include "interrupt_manager.h"
#include "bsp_delay.h"
#include "bsp_wifi.h"
#include "bsp_power.h"
#include "bsp_usart_dma.h"


#include "bsp_key_app.h"
#include "bsp_message.h"
#include "bsp_freertos.h"




#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"



#define  USE_FreeRTOS      1

#if USE_FreeRTOS == 1
	//#include "FreeRTOS.h"
	///#include "task.h"
	#define DISABLE_INT()    taskENTER_CRITICAL()
	#define ENABLE_INT()     taskEXIT_CRITICAL()
#else
	/* ����ȫ���жϵĺ� */
	#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
	#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */
#endif


typedef enum{

  WORKS_TIMING,
  TIMER_SUCCESS

}TIMER_STATE;


typedef enum power_onoff_state_t{

    power_off,
    power_on


}power_onoff_stae;


typedef enum{

  no_ai_mode,
  ai_mode

}ai_mode_typedef;

typedef struct _pro_t{

   
   uint8_t set_timer_timing_value_success;
   uint8_t set_timer_timing_doing_value;
   uint8_t set_temp_value_success;
   uint8_t set_up_temperature_value;
   uint8_t mode_Key_long_counter;
   uint8_t  mode_key_shot_flag ;
  
   uint8_t answer_signal_flag;
   uint8_t set_timer_first_smg_blink_flag;

   uint8_t send_ack_cmd;
   uint8_t receive_copy_cmd;
   uint8_t g_manual_shutoff_dry_flag;
  
   uint8_t input_numbers_flag;
   uint8_t DMA_txComplete;
   uint8_t mainBord_setTimer_flag;
   uint8_t main_settemp_value;
   
  



   uint8_t g_time_disp_colon_flag;
   uint8_t smartphone_app_timer_power_on_flag;
   uint8_t key_add_dec_pressed_flag;
   


   uint8_t gTimer_temp_compare_counter;
   uint8_t gTimer_set_temperature_value;
   uint8_t gTimer_again_send_power_on_off;

   uint8_t gTimer_wifi_led_blink ;
   uint8_t gTimer_disp_moke_switch;
   uint8_t gTimer_mode_long_key_counter;

   uint16_t gTimer_4bitsmg_blink_times;
  
   




}pro_run_t;

extern pro_run_t  gpro_t;


void bsp_init(void);

void power_on_handler(void);


void power_on_run_handler(void);


void power_off_run_handler(void);

void plasma_key_fun(uint8_t data);


void ai_key_fun(uint8_t data);



void bsp_dry_fun(uint8_t data);




void mode_key_long_fun(void);

void SetDataTemperatureValue(void);


void compare_temp_value(void);

void detected_ptc_or_fan_warning_fun(void);


void works_run_two_hours_handler(void);

void mode_key_short_fun(void);

#endif 


