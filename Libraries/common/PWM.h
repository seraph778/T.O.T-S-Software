/*************************************************
Copyright (C), 2016-2023, TYUT JBD TRoMaC
File name: PWM.c
Author: Li_Jiang
Version: v1.0       
Date: 2023_09_16
Description: 
Others: NULL
Function List:  PWM_SetDuty()
                PWM_Init()
History:
<author>    <time>          <version>       <desc>
Li_Jiang    2023_09_16      v1.0            
**************************************************/
#ifndef __PWM_h
#define __PWM_h

#include "headfiles.h"

    // TIM3_CH1---->A6 
	  // TIM3_CH2---->A7
    // TIM3_CH3---->B0
		#define PWM_TIM3_CH1_A6         ((uint32_t *)&TIM3->CCR1)	
		#define PWM_TIM3_CH2_A7         ((uint32_t *)&TIM3->CCR2)	
		#define PWM_TIM3_CH3_B0         ((uint32_t *)&TIM3->CCR3)

    // TIM4_CH1---->B6
    // TIM4_CH2---->B7
    // TIM4_CH3---->B8
    // TIM4_CH4---->B9
    #define PWM_TIM4_CH1_B6         ((uint32_t *)&TIM4->CCR1)	
    #define PWM_TIM4_CH2_B7         ((uint32_t *)&TIM4->CCR2)	
    #define PWM_TIM4_CH3_B8         ((uint32_t *)&TIM4->CCR3)	
    #define PWM_TIM4_CH4_B9         ((uint32_t *)&TIM4->CCR4)
    
		// TIM2_CH3---->B10
    // TIM2_CH4---->B11
	  #define PWM_TIM2_CH3_B10        ((uint32_t *)&TIM2->CCR3)
    #define PWM_TIM2_CH4_B11        ((uint32_t *)&TIM2->CCR4)
		
    // TIM5_CH1---->A0
    // TIM5_CH2---->A1
	  // TIM5_CH3---->A2
    // TIM5_CH4---->A3
		#define PWM_TIM5_CH1_A0         ((uint32_t *)&TIM5->CCR1)	
		#define PWM_TIM5_CH2_A1         ((uint32_t *)&TIM5->CCR2)	
		#define PWM_TIM5_CH3_A2         ((uint32_t *)&TIM5->CCR3)	
		#define PWM_TIM5_CH4_A3         ((uint32_t *)&TIM5->CCR4)
	

void PWM_Init(void);
void PWM_SetDuty(uint32_t *Channel, int32_t Duty);
int16_t PWM_BreathDuty(void);
#endif /* __PWM_h */

