/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;

extern UART_HandleTypeDef huart5;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */
#define MAX_REC_CNT 30

struct USART_RX_Data
{
    uint8_t U1_RX_COUNT;
    uint8_t U1_RES;
    uint8_t U1_RX_BUF[MAX_REC_CNT];

    uint8_t U2_RX_COUNT;
    uint8_t U2_RES;
    uint8_t U2_RX_BUF_SERVO[MAX_REC_CNT];

    uint8_t U3_RX_COUNT;
    uint8_t U3_RES;
    uint8_t U3_RX_BUF[MAX_REC_CNT];

    uint8_t U6_RX_COUNT;
    uint8_t U6_RES;
    uint8_t U6_RX_BUF[MAX_REC_CNT];

    uint8_t U4_RX_COUNT;
    uint8_t U4_RES;
    uint8_t U4_RX_BUF[MAX_REC_CNT];

    uint8_t U5_RX_COUNT;
    uint8_t U5_RES;
    uint8_t U5_RX_BUF[MAX_REC_CNT];
};


/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
extern struct USART_RX_Data USART_RX_DATA;

void USART_send_str(UART_HandleTypeDef *huart,uint8_t *data);
void USART_send_char(UART_HandleTypeDef *huart,uint8_t data);


void USART2_send_str_SERVO(uint8_t data[],uint8_t len);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

