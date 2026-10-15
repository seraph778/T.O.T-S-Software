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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define huart_DBG huart1
#define huart_USER huart3
#define htim_RC htim6
#define PPM_Pin GPIO_PIN_3
#define PPM_GPIO_Port GPIOC
#define PPM_EXTI_IRQn EXTI3_IRQn
#define Steer_A0_Pin GPIO_PIN_0
#define Steer_A0_GPIO_Port GPIOA
#define Steer_A1_Pin GPIO_PIN_1
#define Steer_A1_GPIO_Port GPIOA
#define Steer_A2_Pin GPIO_PIN_2
#define Steer_A2_GPIO_Port GPIOA
#define Steer_A3_Pin GPIO_PIN_3
#define Steer_A3_GPIO_Port GPIOA
#define Steer_B0_Pin GPIO_PIN_0
#define Steer_B0_GPIO_Port GPIOB
#define Switch_2_Pin GPIO_PIN_7
#define Switch_2_GPIO_Port GPIOC
#define Switch_4_Pin GPIO_PIN_8
#define Switch_4_GPIO_Port GPIOC
#define Switch_1_Pin GPIO_PIN_9
#define Switch_1_GPIO_Port GPIOC
#define Switch_3_Pin GPIO_PIN_8
#define Switch_3_GPIO_Port GPIOA
#define LED_4_Pin GPIO_PIN_11
#define LED_4_GPIO_Port GPIOA
#define Switch_EN_Pin GPIO_PIN_12
#define Switch_EN_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_15
#define LED_3_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_12
#define LED_2_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_3
#define LED_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/*控制电机的IO口和PWM口
  IO引脚 B4   D2   C13  B5
  PWM引脚 B6	 B7   B8   B9*/
// LF左前轮
#define Motor_LF_IO_GPIO_Port	  GPIOB
#define Motor_LF_IO_Pin			    GPIO_PIN_4
#define Motor_LF_PWM		        PWM_TIM4_CH4_B9

// LB左后轮
#define Motor_LR_IO_GPIO_Port	   GPIOD
#define Motor_LR_IO_Pin			     GPIO_PIN_2
#define Motor_LR_PWM			       PWM_TIM4_CH2_B7

// RF右前轮
#define Motor_RF_IO_GPIO_Port	   GPIOC
#define Motor_RF_IO_Pin			     GPIO_PIN_13
#define Motor_RF_PWM			       PWM_TIM4_CH3_B8

// RB右后轮
#define Motor_RR_IO_GPIO_Port	   GPIOB
#define Motor_RR_IO_Pin			     GPIO_PIN_5
#define Motor_RR_PWM			       PWM_TIM4_CH1_B6

//即控制轮胎的IO口和PWM口分别为：左前（B4,B9），左后（D2，B7），右前（C13，B8），右后（B5，B6）

/*控制舵机的PWM口*/
#define A0            PWM_TIM5_CH1_A0  //����
#define A2            PWM_TIM5_CH3_A2  //�϶��
#define A3            PWM_TIM5_CH4_A3  //ǰ���
#define A6            PWM_TIM3_CH1_A6  //����
#define A7            PWM_TIM3_CH2_A7  //����
#define B0            PWM_TIM3_CH3_B0  //����


/* ============ GPIO 快捷操作宏 ============ */

/* 函数名缩短：GPIO_WritePin -> HAL_GPIO_WritePin */
#define IO(PIN, STATE)     HAL_GPIO_WritePin(PIN, STATE)
#define PWM(Channel, Duty)  PWM_SetDuty(Channel, Duty)
//#define PWM_SetDuty(PIN);
/* 电平状态别名 */
#define SET     GPIO_PIN_SET
#define RESET   GPIO_PIN_RESET

/* IO 引脚别名：一个宏展开为 "GPIOx, GPIO_PIN_n" 两个参数 */
#define B1   GPIOB, GPIO_PIN_1
#define B10  GPIOB, GPIO_PIN_10
#define B11  GPIOB, GPIO_PIN_11
#define B12  GPIOB, GPIO_PIN_12
#define B13  GPIOB, GPIO_PIN_13
#define B14  GPIOB, GPIO_PIN_14
#define B15  GPIOB, GPIO_PIN_15
#define C6   GPIOC, GPIO_PIN_6



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
