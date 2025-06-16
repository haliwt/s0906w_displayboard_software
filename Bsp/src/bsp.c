#include "bsp.h"


pro_run_t  gpro_t;

typedef enum {
    TEMP_SETTING_MODE = 0,
    TIMER_SETTING_MODE = 1
} SettingMode;


uint8_t hours_one,hours_two,minutes_one,minutes_two;

uint8_t  step_state;
uint8_t  first_set_temperature_value;


void bsp_init(void)
{

    run_t.gRunCommand_label =RUN_NULL;
    run_t.gPower_On = power_off;


}

void power_on_handler(void)
{

	run_t.gTimer_set_temp_times=0; //conflict with send temperatur value

	run_t.gPower_On = power_on;
	run_t.gRunCommand_label =RUN_POWER_ON;
	run_t.power_off_flag = 0;
	

	



 }

void power_off_handler(void)
{

    run_t.gPower_On = power_off;
	run_t.gRunCommand_label =RUN_NULL;

 }

/******************************************************************************
	*
	*Function Name:void RunPocess_Command_Handler(void)
	*Funcion: display pannel run of process 
	*Input Ref: NO
	*Return Ref:NO
	*
******************************************************************************/
void power_on_run_handler(void)
{

 //  static uint8_t  step_state;
   switch(run_t.gRunCommand_label){

      case RUN_POWER_ON:
          
	  
           run_t.gTimer_time_colon =0;
	       run_t.set_temperature_decade_value=40;
           
            run_t.gTimer_detect_mb_receive_flag =0;
			Power_On_Fun();
			run_t.gTimer_display_dht11 = 20; //at once display temperature and humidity value.
			gpro_t.set_timer_timing_doing_value = 0;
            gpro_t.g_manual_shutoff_dry_flag = 0; //allow open dry function .
            run_t.wifi_led_fast_blink=0;
			gpro_t.gTimer_temp_compare_counter=0;
			gpro_t.set_timer_timing_value_success=0;
			run_t.timer_dispTime_hours=0;
		    run_t.timer_dispTime_minutes=0;

			if(run_t.wifi_connect_state_flag == wifi_connect_success){

                   if(run_t.display_beijing_time_flag ==0){
						run_t.works_dispTime_hours=0;
						run_t.works_dispTime_minutes=0;
						run_t.gTimer_timing_seconds_counter =0;
					    

				    }

			}
			else{
			   
    		   run_t.works_dispTime_hours=0;
			   run_t.works_dispTime_minutes=0;
			   run_t.gTimer_timing_seconds_counter =0;

			}
			gpro_t.set_temp_value_success=0;
			
			run_t.gRunCommand_label= SPECIAL_DISP;


            
	  break;

      case SPECIAL_DISP:

              if(gpro_t.mode_key_shot_flag ==1){

                  if(gpro_t.gTimer_disp_moke_switch <  3){
				  	
			          mode_key_short_fun();

                  }
				  else{
				     gpro_t.mode_key_shot_flag++;


				  }

			  }
              else if(gpro_t.set_timer_timing_doing_value == 1 && run_t.ptc_warning ==0 && run_t.fan_warning ==0){

                   Set_TimerTiming_Number_Value();
                   
              }
              else if((gpro_t.set_timer_timing_doing_value == 0 ||gpro_t.set_timer_timing_doing_value == 3 )&&  run_t.set_temperature_special_flag   >0 &&  run_t.set_temperature_special_flag != 0xff ){

                   disp_smg_blink_set_tempeature_value();
	              
						
             }
             else{

              switch(step_state){

					case 0:
						Led_Panel_OnOff();
					    step_state=1;
					break;

					case 1:

						 
               			// disp_dht11_value();
                       
				        step_state=2;
	                    
				   break;
                    
                    case 2: //display 1:   timing times  2: timer times.

					    if(gpro_t.mode_key_shot_flag == 1){
                              if(gpro_t.gTimer_disp_moke_switch > 2){
							  	gpro_t.gTimer_disp_moke_switch=0;
								gpro_t.mode_key_shot_flag++;
                                mode_key_short_fun();

                              }
					    }
                        else if(gpro_t.set_timer_timing_doing_value==0 || gpro_t.set_timer_timing_doing_value==3){ //WT.EDIT 2025.05.07
                        if(run_t.ptc_warning ==0 && run_t.fan_warning ==0){ //read main board ptc_warning of ref.
                            
							   Display_SmgTiming_Value();

                            

                         }
                        else{

                            Warning_Error_Numbers_Fun();

                        }
                        
                        }

                     step_state=0;
                    break;

              }
            
             }    
      break;

	}
}


void detected_ptc_or_fan_warning_fun(void)
{

    Warning_Error_Numbers_Fun();

}

/******************************************************************************
	*
	*Function Name:void mode_key_long_fun(void)
	*Funcion: exit this mode set fun ,
	*Input Ref: NO
	*Return Ref:NO
	*
******************************************************************************/
void mode_key_long_fun(void)
{
         gpro_t.set_timer_timing_doing_value = 1;
		 gpro_t.key_add_dec_pressed_flag =0;
		 run_t.gTimer_key_timing = 0;
		 run_t.gTimer_smg_blink_times =0;
		 gpro_t.set_timer_first_smg_blink_flag=0;


}
void mode_key_short_fun(void)
{

  if(gpro_t.set_timer_timing_value_success==0){
             
	run_t.timer_dispTime_hours=0;
	run_t.timer_dispTime_minutes=0;

	Display_Timing(run_t.timer_dispTime_hours,run_t.timer_dispTime_minutes,0);

	}
   else{

        Display_Timing(run_t.works_dispTime_hours,run_t.works_dispTime_minutes,0);
			
			 

	}

}
/******************************************************************************
	*
	*Function Name:void RunPocess_Command_Handler(void)
	*Funcion: display pannel run of process 
	*Input Ref: NO
	*Return Ref:NO
	*
******************************************************************************/
void power_off_run_handler(void)
{
    static uint8_t power_on_off_flag;
    switch(run_t.power_off_flag){
     case 0://2
	  
		 run_t.ptc_warning =0;
		 run_t.fan_warning =0;
			
         run_t.gFan_RunContinue =1;
	     run_t.gTimer_fan_continue=0;
         run_t.gTimer_detect_mb_receive_flag=0;

         

         
       
		   
		 
         //  Power_Off();
           Power_Off_Led_Off();
		 gpro_t.smartphone_app_timer_power_on_flag =0;
		   gpro_t.set_timer_timing_value_success=0;
			run_t.timer_dispTime_hours=0;
		    run_t.timer_dispTime_minutes=0;
			
         run_t.power_off_flag = 1;
       break;

       case 1://4


            if(run_t.gTimer_fan_continue < 61 && run_t.gFan_RunContinue == 1 && power_on_off_flag !=0){
                   
					//LED_FAN_ON() ;
		      }
			  else if(run_t.gTimer_fan_continue > 59){
                    run_t.gTimer_fan_continue =0;
				 
				   run_t.gFan_RunContinue ++;
                 

			}


		  
            Breath_Led();
		 
		 break;
       }

}





/*******************************************************
*
*Function Name: void compare_temp_value()
*Function :
*
*
*******************************************************/


