#ifndef __BSP_USART_DMA_H
#define __BSP_USART_DMA_H
#include "main.h"

#define RX_BUFFER_SIZE  12
#define MAX_FRAME_SIZE  12

extern uint8_t dmaRxBuffer[RX_BUFFER_SIZE];


// 原有的全局消息结构体
typedef struct _g_msg_t{
    uint8_t usData[MAX_FRAME_SIZE];
    uint8_t rx_data_counter;
    uint8_t disp_rx_cmd_done_flag;
    uint8_t ulid;
    uint8_t bcc_check_code;
	uint8_t receivedLength ;
	
} G_MSG_T;

extern G_MSG_T g_msg;


void ProcessReceivedData(uint8_t *data, uint8_t length);

void HandleReceivedFrame(uint8_t *buffer, uint8_t length);



#endif 

