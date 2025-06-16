#ifndef __BSP_TM1639_H
#define __BSP_TM1639_H
#include "main.h"

// TM1639 引脚定义
#define TM1639_STB_PIN                GPIO_PIN_4
#define TM1639_DIO_PIN                GPIO_PIN_5
#define TM1639_CLK_PIN                GPIO_PIN_6
#define TM1639_GPIO                   GPIOA

// TM1639 引脚操作宏定�??
#define TM1639_CLK_SetHigh()          do{TM1639_GPIO-> BSRR |=TM1639_CLK_PIN ; }while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_CLK_PIN, GPIO_PIN_SET)
#define TM1639_CLK_SetLow()           do{TM1639_GPIO-> BSRR |=(uint32_t)TM1639_CLK_PIN <<16 ;}while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_CLK_PIN, GPIO_PIN_RESET)

#define TM1639_DIO_SetHigh()          do{TM1639_GPIO-> BSRR |=TM1639_DIO_PIN;}while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_DIO_PIN, GPIO_PIN_SET)
#define TM1639_DIO_SetLow()           do{TM1639_GPIO-> BSRR |=(uint32_t)TM1639_DIO_PIN<<16;}while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_DIO_PIN, GPIO_PIN_RESET)

#define TM1639_STB_SetHigh()          do{TM1639_GPIO-> BSRR |=TM1639_STB_PIN;}while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_STB_PIN, GPIO_PIN_SET)
#define TM1639_STB_SetLow()           do{TM1639_GPIO-> BSRR |=(uint32_t)TM1639_STB_PIN<<16;}while(0)//HAL_GPIO_WritePin(TM1639_GPIO, TM1639_STB_PIN, GPIO_PIN_RESET)

// TM1639 命令定义
#define TM1639_CMD_DATA               0x40    // 数据命令
#define TM1639_CMD_DISPLAY            0x88    // 显示控制命令
#define TM1639_DONOT_DISPLAY          0x80    //  关闭显示

// TM1639 显示地址定义（每个数字需要高4位和�??4位两个地�??�??
// �??1位数码管（最左）
#define TM1639_ADDR_DIG1_H           0xC1    // �??4位地�??
#define TM1639_ADDR_DIG1_L           0xC0    // �??4位地�??
// �??2位数码管（中间）
#define TM1639_ADDR_DIG2_H           0xC3    // �??4位地�??
#define TM1639_ADDR_DIG2_L           0xC2    // �??4位地�??
// �??3位数码管（最右）
#define TM1639_ADDR_DIG3_H           0xC5    //  �??4位地�??
#define TM1639_ADDR_DIG3_L           0xC4    // �??4位地�??

#define 	TM1639_ADDR_GRID4_H      0xC7
#define		TM1639_ADDR_GRID4_L 	 0xC6

#define    	TM1639_ADDR_GRID5_H      0xC9
#define    	TM1639_ADDR_GRID5_L      0xC8

#define   	TM1639_ADDR_GRID6_H		0xCB
#define   	TM1639_ADDR_GRID6_L		0xCA

#define  	TM1639_ADDR_GRID7_H		0xCD
#define  	TM1639_ADDR_GRID7_L		0xCD

#define   	TM1639_ADDR_GRID8_H		0xCF
#define   	TM1639_ADDR_GRID8_L		0xCE



// TM1639 显示模式
#define TM1639_DISPLAY_ON            0x08    // 显示�??
#define TM1639_DISPLAY_OFF           0x00    // 显示�??

// TM1639 亮度级别 (0-7)
#define TM1639_BRIGHTNESS_MAX        0x07    // �??大亮�?? //WT.EDIT 2025.04.23
#define TM1639_BRIGHTNESS_MIN        0x00    // �??小亮�??

// 特殊字符段码定义
//#define TM1639_CHAR_H               0x76    // H: 0111 0110 (b,c,e,f,g)
//#define TM1639_CHAR_DEGREE          0x63    // 度数符号 (b,c,g)
//#define TM1639_CHAR_C               0x39    // 摄氏度C (a,d,e,f)
//#define TM1639_CHAR_RH              0x50    // 湿度符号RH的H部分 (e,g)
//#define TM1639_DOT                  0x80    // 小数�?? (dp)

#define SEG_A                       0x01
#define SEG_B                       0x02
#define SEG_C                       0x04
#define SEG_D                       0x08
#define SEG_E                       0x10
#define SEG_F                       0x20
#define SEG_G                       0x40
#define SEG_H                       0x80

// 函数声明
void TM1639_Init(void);                      // 初始化TM1639

void TM1639_Set_Brightness(uint8_t bright);  // 设置亮度
void TM1639_Display_ON_OFF(uint8_t status);  // 显示�??关控�??
void TM1639_Clear(void);                     // 清空显示

void TM1639_Write_Digit_Full(uint8_t addr_h, uint8_t addr_l, uint8_t data); // 写入完整的一位数码管
void TM1639_All_Off(void);

#if 0

void TM1639_Write_Half_Digit(uint8_t addr,uint8_t data);

void TM1639_Display_H(uint8_t position);     // 在指定位置显示字母H
void TM1639_Display_Temperature(int8_t temp); // 显示温度值（-9�??99℃）
void TM1639_Display_Humidity(uint8_t humi);  // 显示湿度值（0-99%RH�??
void TM1639_Display_Decimal(uint16_t num, uint8_t dot_pos); // 显示带小数点的数�??
             // 关闭�??有显示（包括数码管和LED�??


void disp_decimal_point(uint8_t idata);


void TM1639_Display_3_Digit(uint8_t num);   // 显示3位数�??

#endif

#endif 

