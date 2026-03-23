/*
 * bsp_message.c
 *
 *  Created on: 2025�??2�??19�??
 *      Author: Administrator
 */
#include "bsp.h"

static void copy_cmd_data_from_mainboard(uint8_t *pdata);



/******************************************************************************
*
*Function Name:void send_cmd_ack_hanlder(void)
*Funcion: handle of tall process
*Input Ref:
*Return Ref:
*
******************************************************************************/

/******************************************************************************
*
*Function Name:void receive_data_from_mainboard(uint8_t *pdata,uint8_t len)
*Funcion: handle of tall process
*Input Ref:
*Return Ref:
*
******************************************************************************/
void receive_data_from_mainboard(uint8_t *pdata)
{
    
  // static uint8_t power_on_counter;
   uint8_t temp_value;
    switch(pdata[2]){

     case 0:


     break;

     case  power_cmd:
           

            if(pdata[3]== 0x01){
			run_t.gPower_On = power_on;
            run_t.gRunCommand_label =RUN_NULL;
            //gpro_t.receive_copy_cmd = 1;
            power_on_handler();
            SendData_Set_Command(0x01,0x01); //0x11 :send to main has the second display board exit.
			osDelay(50);
           }
           else{ //power off

            run_t.gPower_On = power_off;
            run_t.gRunCommand_label =RUN_NULL;
            SendData_Set_Command(0x01,0x01);
			osDelay(50);
           
           }
          

     break;

	 
	 case dry_cmd: //PTC打开关闭指令
		   
	
	 
		   if(pdata[3]== 0x01 && run_t.gPower_On == power_on){
	 
				run_t.gDry =1 ;//&& run_t.gPlasma ==1  && run_t.gUltransonic==1
				LED_DRY_ON();
			}
			else if(pdata[3] == 0x0){
	 
				run_t.gDry =0;
				LED_DRY_OFF();
			  
	 
			}
			
		 break;
	 
		 case plasma_cmd: //PLASMA 打开关闭指令
	 
			
			
				if(pdata[3]== 0x01){
				  
				run_t.gPlasma =1;
	 
	 
				}
				else if(pdata[3] == 0x0){
				  
				 run_t.gPlasma =0;
	 
				}
			
	 
		 break;
	 
	 
		  case mouse_cmd: //ultrasonic	打开关闭指令
	 
			
		  
			   
			   if(pdata[3]== 0x01){
				   
				   run_t.gMouse = 1;
	 
				}
				else { //close
				 run_t.gMouse = 0;
				}
	 
			
	 
	 
		 break;
	 
		 case wifi_cmd:
	 
	        if(pdata[3]== 0x01){
	 
			run_t.wifi_led_fast_blink=1;
			run_t.wifi_connect_state_flag = wifi_connect_null;
			run_t.gTimer_wifi_connect_counter =0; //120s counte start
			 
			
	 
			}
			else if(pdata[3] == 0x0){ //close
	 
			}
	 
	 
		
	 
	 
		 break;

	
	   case temp_warning: //temperature of high warning.
	 
			
				
				if(pdata[3]== 0x01){
	 
					run_t.ptc_warning = 1;
					run_t.gDry =0;
					LED_DRY_OFF();
				   
	 
				}
				else if(pdata[3] == 0x0){ //close
	 
				   run_t.ptc_warning = 0;
	 
	 
				}
	 
			
	 
		  break;
	 
		  case fan_warning: //fan of default of warning.
	 
	 
		   if(pdata[3]==1){
				run_t.fan_warning = 1;
	 
			   run_t.gDry =0;
			   LED_DRY_OFF();
			   //SendData_Set_Command(0x22,0x0); //0x22:PTC notice close .
			   } 
			   else if(pdata[3] == 0x0){ //close
	 
			   run_t.fan_warning = 0;
	 
	 
			   }
	 
	 
		  break;

//接收的是数据

      case temp_hum_data: //温度,湿度数据
      
        
          run_t.gReal_humtemp[0] = pdata[5] ;//humidity value 

             
          run_t.gReal_humtemp[1] = pdata[6];
       break;


      case beijing_times_data: //表示时间：小时，分，�??

        if(pdata[4] == 0x03){ //数据,has three data

            if(pdata[5] < 24){ //WT.EDIT 2024.11.23

            run_t.display_beijing_time_flag= 1;
          
          run_t.works_dispTime_hours= pdata[5];// run_t.dispTime_hours  =  pdata[5];
          run_t.works_dispTime_minutes =pdata[6];//run_t.dispTime_minutes = pdata[6];
          run_t.gTimer_timing_seconds_counter =  pdata[7];//run_t.gTimer_disp_time_seconds =  pdata[7];
           }


        }
      break;

	  case wifi_connect_data: //0x1f notice is command
	  	
         if(pdata[3]==1){
             run_t.wifi_led_fast_blink=0;
			 run_t.wifi_connect_state_flag = wifi_connect_success;
			 run_t.gTimer_wifi_connect_counter =0; //120s counte start
		
			  
	  
			}
			else{ //close
	  
		      run_t.wifi_led_fast_blink=0;
			 run_t.wifi_connect_state_flag = wifi_connect_null;
			 run_t.gTimer_wifi_connect_counter =0; //120s counte start
	  
			}
	    	
	    
  
	  break;

	  case 0x20: //手机定时�??机，发�?�的数据�??3个�??

	      if(pdata[3]==0x01){
		  	  run_t.wifi_connect_state_flag = wifi_connect_success;
			run_t.gPower_On = power_on;
		     run_t.gRunCommand_label =RUN_NULL;
						//gpro_t.receive_copy_cmd = 1;
			power_on_handler();

              
		   	}
		    else{
                 run_t.gPower_On = power_off;
                run_t.gRunCommand_label =RUN_NULL;

			}

	    
	 
      break;

	  case 0x21: //smart phone power on or off that App timer .
       

		   if(pdata[3]==0x01){

		   run_t.wifi_connect_state_flag = wifi_connect_success;
		   	
           gpro_t.smartphone_app_timer_power_on_flag =1;
		    run_t.gPower_On = power_on;
			 power_on_handler();
			 temp_value = 1;
			 SendData_CopyCmd_Data(0x01,&temp_value,0);
			 osDelay(50);
		   	}
		    else{

				run_t.gPower_On = power_off;
                run_t.gRunCommand_label =RUN_NULL;
			    temp_value = 0;
			    SendData_CopyCmd_Data(0x01,&temp_value,0);
				 osDelay(50);

			}
           
             
         
       
     break; 

   case 0x22: //Command ,set temperature compare dht11 result open or close


	   if(pdata[3]== 0x01 && run_t.gPower_On == power_on){

            run_t.gDry =1 ;//&& run_t.gPlasma ==1  && run_t.gUltransonic==1
           // gpro_t.g_manual_shutoff_dry_flag = 0;
        }
        else if(pdata[3] == 0x0 && run_t.gPower_On == power_on){

            //gpro_t.g_manual_shutoff_dry_flag = 0;
            run_t.gDry =0;
		    LED_DRY_OFF();
          

        }
    

	  break;

	  

        case 0x1D: //表示日期�?? 年，月，�??

        if(pdata[2] == 0x0F){ //数据



        }
      break;

	  

	  case 0x2A: //main board set temperature value 
	  
          
	
		  
			if(pdata[4]== 0x01){ // one only data 

		  
				
			gpro_t.set_up_temperature_value =pdata[5];//warning
	  
			 gpro_t.g_manual_shutoff_dry_flag = 0 ;//  allow open dry function
             gpro_t.set_temp_value_success=1;//
        
             run_t.gTimer_key_temp_timing=0;

			 run_t.set_temperature_decade_value = gpro_t.set_up_temperature_value / 10 ;
             run_t.set_temperature_unit_value  =gpro_t.set_up_temperature_value % 10; //

             TM1639_Write_2bit_SetUp_TempData(run_t.set_temperature_decade_value,run_t.set_temperature_unit_value,0);
				
	  
			 

			}
		  	
	break;

	case mainboard_set_timer_value://0x2B


		  
			if(pdata[5] >0){ // one only data 

			  run_t.timer_dispTime_hours=pdata[5]; //this is data don't command .
			 // if(run_t.timer_dispTime_hours> 0){
		      gpro_t.set_timer_timing_doing_value = 1;
			  gpro_t.key_add_dec_pressed_flag =0;
			  run_t.gTimer_key_timing = 0;
              run_t.gTimer_smg_blink_times =0;
			  gpro_t.set_timer_first_smg_blink_flag=0;
			  gpro_t.set_timer_timing_value_success=1;
			

			  gpro_t.mainBord_setTimer_flag = 1;
			  gpro_t.main_settemp_value=1;
	  
			 	 run_t.hours_two_decade_bit    = run_t.timer_dispTime_hours / 10;
    			run_t.hours_two_unit_bit      = run_t.timer_dispTime_hours % 10;
				run_t.timer_dispTime_minutes =0;
   				run_t.minutes_one_decade_bit  = run_t.timer_dispTime_minutes;
    			run_t.minutes_one_unit_bit    = run_t.timer_dispTime_minutes;
			   /// }
			}
			else if(pdata[5] ==0){
					 run_t.timer_dispTime_hours=0;

                   
		             gpro_t.set_timer_timing_doing_value = 1;
					 gpro_t.key_add_dec_pressed_flag =0;
					 run_t.gTimer_key_timing = 0;
					 run_t.gTimer_smg_blink_times =0;
					 gpro_t.set_timer_first_smg_blink_flag=0;
					 gpro_t.set_timer_timing_value_success=0;
					
		
					 gpro_t.mainBord_setTimer_flag = 0;
					 gpro_t.main_settemp_value=1;

					  run_t.hours_two_decade_bit    = 0;
		    			run_t.hours_two_unit_bit      =0;
						run_t.timer_dispTime_minutes =0;
		   				run_t.minutes_one_decade_bit  = run_t.timer_dispTime_minutes;
		    			run_t.minutes_one_unit_bit    = run_t.timer_dispTime_minutes;
             }
				 
		  	

	break;

     case copy_cmd: // copy send cmd acknowlege
          copy_cmd_data_from_mainboard(pdata);

     break;

     }

 }


static void copy_cmd_data_from_mainboard(uint8_t *pdata )
{
    
    switch(pdata[3]){

    case CMD_POWER : //power_on 
   

	 if(pdata[4]==0x01){
	 	run_t.gPower_On = power_on;
        power_on_handler();
        SendData_Set_Command(0x10,1); //again turn power on ,mainboard.WT.EDIT 2026.01.04
        vTaskDelay(pdMS_TO_TICKS(100)); //WT.EDIT 2026.01.04

     }
     else{ //power offf

        run_t.gPower_On = power_off;
        run_t.power_off_flag=0;
       

     }
    
    break;

    case ack_ptc:
    if(pdata[4]==0x00){
    if(pdata[5]==1){

         gpro_t.receive_copy_cmd = 1;
		 run_t.gDry =1 ;//&& run_t.gPlasma ==1  && run_t.gUltransonic==1
         gpro_t.g_manual_shutoff_dry_flag = 0;
		 LED_DRY_ON();
    }
    else{
      gpro_t.receive_copy_cmd = 2;
	  gpro_t.g_manual_shutoff_dry_flag = 0;
      run_t.gDry =0;
	  LED_DRY_OFF();

    }

    }

    break;

    case ack_plasma:

    if(pdata[5]==1){

        gpro_t.receive_copy_cmd = 1;
    }
    else{
      gpro_t.receive_copy_cmd = 2;

    }
    break;

    case ack_ai:

    if(pdata[5]==1){

        gpro_t.receive_copy_cmd = 1;
    }
    else{
      gpro_t.receive_copy_cmd = 2;

    }

    break;

    case ack_wifi: // link wifi command

    

	  if(pdata[4] == 0x01){  // link wifi

	     run_t.wifi_led_fast_blink=1;
		run_t.wifi_connect_state_flag = wifi_connect_null;
		run_t.gTimer_wifi_connect_counter =0; //120s counte start
			  
	  
	   }
	  else{ //close
	  
			   run_t.wifi_connect_state_flag = wifi_connect_null;
	            run_t.wifi_led_fast_blink=0;
			    run_t.display_beijing_time_flag =0;
	  
			}

      
     

   break;

   


    
    
    case ack_with_buzzer:
        if(pdata[5] == 1){  //buzzer answer command

           

        }
        else{
         


        }
     break;
    }


}


/******************************************************************************
*
*Function Name:uint8_t bcc_check(const unsigned char *data, int len)
*Funcion: BCC check code
*Input Ref: data:input data, len: data of length
*Return Ref:
*
******************************************************************************/
uint8_t bcc_check(const unsigned char *data, int len)
{
    unsigned char bcc = 0;
    for (int i = 0; i < len; i++) {
        bcc ^= data[i];
    }
    return bcc;
}



