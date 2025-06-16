#include "bsp.h"



// 全局变量


G_MSG_T g_msg;

uint8_t dmaRxBuffer[RX_BUFFER_SIZE];


volatile uint8_t frameBuffer[MAX_FRAME_SIZE];
volatile uint16_t frameLength = 0;
volatile uint8_t frameReady = 0;




// 数据处理函数
void ProcessReceivedData(uint8_t *data, uint8_t length)
{
    static uint8_t state = 0;
    static uint8_t rx_end_flag = 0;
    
    for(uint8_t i = 0; i < length; i++)
    {
        switch(state)
        {
            case 0:  // 等待帧头
                if(data[i] == 0x5A)  // 0x5A -- 主板信号
                {
                    g_msg.rx_data_counter = 0;
                    g_msg.usData[g_msg.rx_data_counter] = data[i];
                    state = 1;
                }
			
                break;
                
            case 1:  // 接收数据
                if(g_msg.disp_rx_cmd_done_flag == 0)
                {
                    g_msg.rx_data_counter++;
                    g_msg.usData[g_msg.rx_data_counter] = data[i];
                    
                    if(rx_end_flag == 1)
                    {
                        state = 0;
                        g_msg.ulid = g_msg.rx_data_counter;
                        rx_end_flag = 0;
                        g_msg.rx_data_counter = 0;
                        g_msg.disp_rx_cmd_done_flag = 1;
                        g_msg.bcc_check_code = data[i];
                        
                        vTaskDecoder_USART1_handler();
                        //memset(g_msg.usData,0,MAX_FRAME_SIZE);
						
					
					}
                }
                
                if(g_msg.usData[g_msg.rx_data_counter] == 0xFE && rx_end_flag == 0 && 
                   g_msg.rx_data_counter > 4)
                {
                    rx_end_flag = 1;
                }
                break;
        }
    }
}


//// DMA1 Channel1中断处理
//void DMA1_Channel1_IRQHandler(void)
//{
//    HAL_DMA_IRQHandler(&hdma_usart1_rx);
//}
#if USART1_INTERRUPT


// 新增函数：处理从DMA缓冲区提取的一帧完整数据
void HandleReceivedFrame(uint8_t *buffer, uint8_t length)
{
    // 这里可以实现你的协议解析逻辑
    // 示例：检查帧头 0x5A 和帧尾 0xFE

    if (length >= 2 && buffer[0] == 0x5A && buffer[length - 2] == 0xFE)
    {
        // 成功接收到一帧数据
        g_msg.rx_data_counter = length;
        memcpy(g_msg.usData, buffer, length);  // 复制到全局消息结构体
        //g_msg.bcc_check_code = buffer[length - 1];
        g_msg.disp_rx_cmd_done_flag = 1;

//        // 通知解码任务
//        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//        xTaskNotifyFromISR(xHandleTaskDecoderPro,
//                           DECODER_BIT_9,
//                           eSetBits,
//                           &xHigherPriorityTaskWoken);
//        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

		vTaskDecoder_USART1_handler();
    }
   // else
    {
        // 数据格式不正确，可在此处做错误处理
    }
}

/**
 * @brief UART DMA 
 * UART callback function接收回调函数（接收完成或空闲线中断触发）
 */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &huart1) {
           g_msg.rx_data_counter = (uint8_t)Size;
           memcpy(g_msg.usData, dmaRxBuffer, g_msg.rx_data_counter);  // 复制到全局消息结构体
          vTaskDecoder_USART1_handler();

        // 重新启动 DMA 
        __HAL_UART_CLEAR_OREFLAG(&huart1);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, dmaRxBuffer, sizeof(dmaRxBuffer));
    }
}

#endif 

