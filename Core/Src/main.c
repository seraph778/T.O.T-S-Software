/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *....................................................................................................*
  *....................................................................................................*
  *....................................................................................................*
  *.............................................tttttttttttttttttttttt.................................*
  *............................................ttttttttttttttttttttttt.................................*
  *............................................tttttttttttttttttttttt..................................*
  *...........................................tttttttttttttttttttttt...................................*
  *..........................................ttttttttttttttttttttttt...................................*
  *..........................................tttttttttttttttttttttt....................................*
  *..........................................ttttttttttttttttttttt.....................................*
  *....................................................................................................*
  *....................ttttttttttttt.......tttttttttttttttttttttt...tttttttttt.........................*
  *...................tttttttttttt.....ttttttttttttttttttttttttt....tttttttttt.........................*
  *...................tttttttt......tttttttttttttttttttttttttttt...tttttttttt..........................*
  *..................ttttt......ttttttttttttttttttttttttttttttt...tttttttttt...........................*
  *.................ttt......ttttttttttttttttttttttttttttttttt....tttttttttt...........................*
  *................tt....ttttttttttttttttttttttttttttttttttttt...tttttttttt............................*
  *...................ttttttttttttttttttttttttttttttttttttttt....ttttttttt.............................*
  *................................ttttttttttttttttttttttttt...........................................*
  *...............................tttttttttttttttttttttttttt...........................................*
  *..............................tttttttttttttttttttttttttt............................................*
  *..............................ttttttttttttttttttttttttt.............................................*
  *.............................tttttttttttttttttttttttttt.............................................*
  *............................ttttttttttttttttttttttttttt........ttt..................................*
  *............................ttttttttttttttttttttttttttttttttttttt...................................*
  *...........................ttttttttttttttttttttttttttttttttttttt....................................*
  *...........................tttttttttttttttttttttttttttttttttttt.....................................*
  *...........................tttttttttttttttttttttttttttttttttttt.....................................*
  *...........................ttttttttttttttttttttttttttttttttttt......................................*
  *............................ttttttttttttttttttttttttttttttttt.......................................*
  *.............................ttttttttttttttttttttttttttttttt........................................*
  *..............................tttttttttttttttttttttttttttt..........................................*
  *.................................ttttttttttttttttttttt..............................................*
  *........................................tttttt......................................................*
  *....................................................................................................*
  *....................................................................................................*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                      
  */                                                                                                             
  
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "headfiles.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t last_print_time = 0; 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Prevent_sensitity(void);
void Prevent_Lost(void);
void Getswitch(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define Center_Right_UD 1475
#define Center_Right_LR 1520 
#define Center_Left_UD  1500
#define Center_Left_LR  1500
#define Dead_zone 50 
//Right_UD: 1934---1475---1084
//Right_LR: 1935---1520---1084

int Right_UD = 0;
int Right_LR = 0;
int Left_UD = 0;
int Left_LR = 0;

int RCSend_Lost = 0;
int vlf,vlb,vrf,vrb;//�ٶ�
int GiPwmLF,GiPwmRF,GiPwmLR,GiPwmRR;
int ADC_Test[8];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  PWM_Init();       // PWM初始化
  RC_Init();        // 遥控初始化
  Chassis_Init();   //底盘初始化

  ADC_Init();       // start ADC+DMA, sample 6 channels

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      RCReceive_Lost_judgement();         //判断是否接收
      RCSend_Lost_judgement();            //判断是否丢失
      Prevent_Lost();                     //防止丢失遥控信号失控
      Getswitch();                        //获得拨码开关的键值
      Prevent_sensitity();                //防止过于遥控信号敏感
	  /*================================================== User Code Space ==================================================*/
	  /* use IO引脚   B1	 B10  B11  B12	B13		B14		B15		C6   eg.HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)        读取B1引脚的电平
																											            IO(B1, GPIO_PIN_SET);                      设置B1引脚为高电平
																										             	IO(B1, GPIO_PIN_RESET);	                   设置B1引脚为低电平
		                                                              Motor_Drive(B1, SET, B10, RESET);          驱动摩擦轮电机 （这个电机不用PWM控制 只用两个IO口来控制）
		                                                                                                         这里把B1引脚设置高电平 B10设置为低电平 
		                                                                                                         如果把B1引脚设置低电平 B10设置为高电平的话会反转
		   use PWM引脚 A0  A2   A3   A6   A7	B0                   eg.驱动舵机   PWM(A0, 750);                   设置该处占空比为750（范围250~1250，超出会毁坏舵机！！！）*/
//		  hCtrl.Chassis.SpeedTarget_Y = (Right_UD - Center_Right_UD) * 15;
//      hCtrl.Chassis.SpeedTarget_X = (Right_LR - Center_Right_LR) * 15;
			int Game_mode = 0;
			if(Game_mode == 1)
			{
					hCtrl.Chassis.SpeedTarget_Y = 7500;
					hCtrl.Chassis.SpeedTarget_X = 0;
			}
			else
			{
					hCtrl.Chassis.SpeedTarget_Y = 0;
					hCtrl.Chassis.SpeedTarget_X = -7500;		
			}
	  /*================================================== User Code End ==================================================*/
	    // 底盘驱动
      ChassisCtrl(hCtrl.Chassis.SpeedTarget_Y, hCtrl.Chassis.SpeedTarget_X);
			
			
			
      // VOFA调试
      VOFA_JustFloat(&huart_DBG);
	    // 勿动！！！
      HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void Prevent_sensitity()
{
	if((Right_UD < Center_Right_UD + Dead_zone && Right_UD  >  Center_Right_UD - Dead_zone) || Right_UD == 0)
	{
			Right_UD = Center_Right_UD;
	}
	
	if((Right_LR < Center_Right_LR + Dead_zone && Right_LR  >  Center_Right_LR - Dead_zone) || Right_LR == 0)
	{
			Right_LR = Center_Right_LR;
	}
	 
	if((Left_UD < Center_Left_UD + Dead_zone && Left_UD > Center_Left_UD - Dead_zone) || Left_UD == 0) 
	{
			Left_UD = Center_Left_UD;
	}
	
	if((Left_LR < Center_Left_LR + Dead_zone && Left_LR > Center_Left_LR - Dead_zone) || Left_LR == 0)
	{
			Left_LR = Center_Left_LR;
	}
}
void Prevent_Lost()
{
	if( hRC.State == RC_state_Receive_Lost || RCSend_Lost)     //����
	{
			Right_UD = Center_Right_UD;	
			Right_LR = Center_Right_LR;	
			Left_UD  = Center_Left_UD;	
			Left_LR  = Center_Left_LR;	
	}
 else       
 {    
	Right_UD = hRC.ChannelData_Raw[0];	
	Right_LR = hRC.ChannelData_Raw[1];	
	Left_UD  = hRC.ChannelData_Raw[2];	
	Left_LR  = hRC.ChannelData_Raw[3];	
 }
}

void Getswitch()
{
	Switch_GetCode();//获取拨码开关的键值
	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, Switch_GetState_Index(Switch_Index_1));
	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, Switch_GetState_Index(Switch_Index_2));
	HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, Switch_GetState_Index(Switch_Index_3));
	HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, Switch_GetState_Index(Switch_Index_4));
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
