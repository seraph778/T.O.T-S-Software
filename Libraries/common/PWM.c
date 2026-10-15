/*************************************************
Copyright (C), 2016-2023, TYUT JBD TRoMaC
File name: PWM.c
Author: Li_Jiang
Version: v1.0       
Date: 2023_09_16
Description: 
Others: NULL
Function List:  PWM_Init()
                PWM_SetDuty()
History:
<author>    <time>          <version>       <desc>
Li_Jiang    2023_09_16      v1.0            
**************************************************/
#include "PWM.h"




/**
  * @name   PWM_Init()
  * @brief  PWM初始化
  * @call   External
  * @param  NULL
  * @RetVal NULL
  */
void PWM_Init(void)
{
	// TIM2
	/*舵机PWM通道*/
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);     // TIM2_CH3---->B10
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);     // TIM2_CH4---->B11
	
	// TIM3
	/*舵机PWM通道*/
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);     // TIM3_CH1---->A6
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);     // TIM3_CH2---->A7
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);     // TIM3_CH3---->B0
	
	// TIM4
	/*舵机PWM通道*/
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);     // TIM4_CH1---->B6
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);     // TIM4_CH2---->B7
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);     // TIM4_CH3---->B8
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);     // TIM4_CH4---->B9
	
	// TIM5
	/*舵机PWM通道*/
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);     // TIM5_CH1---->A0
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);     // TIM5_CH2---->A1
	  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);     // TIM5_CH3---->A2
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);     // TIM5_CH4---->A3
    
}/* PWM_Init */

/**
  * @name   PWM_SetDuty()
  * @brief  设置PWM占空比
  * @call   External
  * @param  *Channel    PWM通道
  * @param  Duty        PWM占空比
  * @RetVal NULL
  */
void PWM_SetDuty(uint32_t *Channel, int32_t Duty)
{
    Duty = ABS(Duty);
		if(Duty > 10000) Duty = 10000;
    *Channel = Duty;
}/* PWM_SetDuty() */


int16_t PWM_BreathDuty(void)
{
    static uint16_t count_Add = 0;
    static uint16_t prescaler = 2;
    static int16_t duty_Min   = 100;
    static int16_t duty_Max   = 8000;
    static int16_t duty_Load  = (8000 + 100) / 2;
    static int8_t  dir        = 1;
    static int8_t  step       = 100;
    
    count_Add++;
    
    if(count_Add >= prescaler)
    {
        if(duty_Load <= duty_Min || duty_Load >= duty_Max)
        {
            dir = -dir;
        }
        
        duty_Load += dir * step;
        
        count_Add = 0;
    }
    
    return duty_Load;
}/* PWM_BreathDuty() */


