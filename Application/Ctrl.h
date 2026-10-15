/*************************************************
Copyright (C), 2016-2023, TYUT JBD TRoMaC
File name: 
Author: 
Version:               
Date: 
Description:  
Others:      
Function List:
History:
<author>    <time>          <version>       <desc>
**************************************************/
#ifndef __Ctrl_h
#define __Ctrl_h

#include "headfiles.h"

/* =========== 宏定义 ================ */

#define Switch_Polarity                     GPIO_PIN_RESET                                  // Switch有效电平
#define Switch_GetState_Index(Index)        ((hCtrl.Switch.Code >> (2 * (Index - 1))) & 0x01U)      // 根据Index获取单个键位的状态

#define Switch_EN_ON                        ((Switch_EN_GPIO_Port->IDR & Switch_EN_Pin) != 0x00U)
#define Switch_EN_OFF                       (!Switch_EN_ON)


typedef enum
{
    Switch_Index_1              = 1,
    Switch_Index_2              = 2,
    Switch_Index_3              = 3,
    Switch_Index_4              = 4,
}Switch_Index_enum;

typedef struct
{
	uint32_t        *PWM_Channel;
	GPIO_TypeDef	*GPIO_Port;
	uint16_t		Pin;
    
    uint16_t        PWM_Channel_DutyMax;
    uint16_t        PWM_Channel_Duty;
}Motor_TypeDef;

typedef struct
{
	int RF;
	int LF;
	int RB;
	int LB;
}F_Offset; //轮胎摩擦力补偿
	

typedef struct
{
    struct 
    {
        uint8_t     Code;
    }Switch;
    
    struct
    {
        uint8_t     Code;
    }LED;
    
    struct
    {
        Motor_TypeDef   LF;
        Motor_TypeDef   RF;
        Motor_TypeDef   LB;
        Motor_TypeDef   RB;
        
        int16_t         SpeedTarget_Y;    // 底盘前后方向
        int16_t         SpeedTarget_X;    // 底盘左右方向
    }Chassis;
    
    
}hCtrl_TypeDef;

/* =========== 全局变量声明 ========== */
extern hCtrl_TypeDef hCtrl;
extern int data;

/* =========== 函数声明 ============== */
uint8_t Switch_GetCode(void);
void Chassis_Init(void);
void ChassisCtrl(int16_t Vy, int16_t Vx);
void SetSpeed_LF(int16_t Speed);

#endif /* __Ctrl_h */



