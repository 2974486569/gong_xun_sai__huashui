/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdbool.h"
#include "delay_us.h"


#include "stdio.h"
#include "fifo.h" 
#include "oled.h"
#include "Emm_V5.h"
#include "ZDT_X42_V2.h"
#include "delay.h"
#include "Motor.h"
#include "step.h"
#include "find.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "jixiebi.h"

#define v1  3
#define v2  1
#define e1  2
#define e2  1

#define speed_1  55
#define wait_1   613

#define kai 103
#define kai1 130//zhua hui
#define kai2 98//fang shang
#define bi  76
#define chu 16
#define zhong  132
#define mo  250


#define ling          0
#define jiang_di      11350
#define jiang_duo     6320
#define jiang_pan     2120
#define jiang_zhao    5200
#define jiang_maix    5500
#define jiang_liu     700
#define zhuan_zheng   1633
#define zhuan_hui     605


#define x_zb    263
#define y_zb    122
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void color(uint8_t color, int v, int err, int xzb, int yzb);
void Stop1(int acc);
void Stop(int acc);
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
#define dj_tx_Pin GPIO_PIN_2
#define dj_tx_GPIO_Port GPIOA
#define dj_rx_Pin GPIO_PIN_3
#define dj_rx_GPIO_Port GPIOA
#define maix_tx_Pin GPIO_PIN_8
#define maix_tx_GPIO_Port GPIOD
#define maix_rx_Pin GPIO_PIN_9
#define maix_rx_GPIO_Port GPIOD
#define k230_tx_Pin GPIO_PIN_9
#define k230_tx_GPIO_Port GPIOA
#define k230_rx_Pin GPIO_PIN_10
#define k230_rx_GPIO_Port GPIOA
#define scl_Pin GPIO_PIN_7
#define scl_GPIO_Port GPIOB
#define sda_Pin GPIO_PIN_8
#define sda_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
