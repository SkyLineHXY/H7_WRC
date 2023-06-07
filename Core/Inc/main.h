/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "../User/motor.h"
#include "usart.h"
#include  "tim.h"
#include "gpio.h"
#include "../User/PID.h"
#include "math.h"
#include "delay.h"
#include "mpuiic.h"
#include "PS2.h"
#include "i2c.h"
#include "SERVO.h"
#include "string.h"
#include "HWT101.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTO1_H_Pin GPIO_PIN_0
#define MOTO1_H_GPIO_Port GPIOC
#define MOTO1_L_Pin GPIO_PIN_1
#define MOTO1_L_GPIO_Port GPIOC
#define MOTO2_H_Pin GPIO_PIN_2
#define MOTO2_H_GPIO_Port GPIOC
#define MOTO2_L_Pin GPIO_PIN_3
#define MOTO2_L_GPIO_Port GPIOC
#define SERVO_U2_TX_Pin GPIO_PIN_2
#define SERVO_U2_TX_GPIO_Port GPIOA
#define SERVO_U2_RX_Pin GPIO_PIN_3
#define SERVO_U2_RX_GPIO_Port GPIOA
#define LEFT_ENC_1_Pin GPIO_PIN_5
#define LEFT_ENC_1_GPIO_Port GPIOA
#define RIGHT_ENC_1_Pin GPIO_PIN_6
#define RIGHT_ENC_1_GPIO_Port GPIOA
#define RIGHT_ENC_2_Pin GPIO_PIN_7
#define RIGHT_ENC_2_GPIO_Port GPIOA
#define actuator_1A_Pin GPIO_PIN_0
#define actuator_1A_GPIO_Port GPIOB
#define actuator_1B_Pin GPIO_PIN_1
#define actuator_1B_GPIO_Port GPIOB
#define actuator_2A_Pin GPIO_PIN_2
#define actuator_2A_GPIO_Port GPIOB
#define actuator_2B_Pin GPIO_PIN_7
#define actuator_2B_GPIO_Port GPIOE
#define RELAY_1_Pin GPIO_PIN_10
#define RELAY_1_GPIO_Port GPIOE
#define RELAY_2_Pin GPIO_PIN_11
#define RELAY_2_GPIO_Port GPIOE
#define PS2_CS_Pin GPIO_PIN_12
#define PS2_CS_GPIO_Port GPIOE
#define PS2_CLK_Pin GPIO_PIN_13
#define PS2_CLK_GPIO_Port GPIOE
#define PS2_DO_Pin GPIO_PIN_14
#define PS2_DO_GPIO_Port GPIOE
#define PS2_DI_Pin GPIO_PIN_15
#define PS2_DI_GPIO_Port GPIOE
#define U6_TLY_TX_Pin GPIO_PIN_6
#define U6_TLY_TX_GPIO_Port GPIOC
#define U6_TLY_RX_Pin GPIO_PIN_7
#define U6_TLY_RX_GPIO_Port GPIOC
#define LEFT_ENC_2_Pin GPIO_PIN_3
#define LEFT_ENC_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
u8 mpu_dmp_init(void);
void task_contorl(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
