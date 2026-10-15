/*************************************************
Copyright (C), 2016-2023, TYUT JBD TRoMaC
File name: Ctrl.c
Author: Li_Jiang
Version: v2.0    
Date: 2023_09_16
Description: 
Others: NULL
Function List: 
History:
<author>    <time>          <version>       <desc>
Li_Jiang    2023_09_10      v1.0            对拨码开关进行简单的封装
Zhang_Jiayi 2023_09_14      v1.1            实现结构赛题底盘的控制
Li_Jiang    2023_09_16      v2.0            优化底盘控制的代码
**************************************************/
#include "Ctrl.h"

/* ============ 全局变量声明 ============= */
hCtrl_TypeDef hCtrl;
int data = 0;  
F_Offset F_Offset_Wheel = {3700, 3900, 3600, 3750};//轮胎动力补偿 RF - LF - RB - LB

/* ============ 局部变量声明 ============= */

/* ============ 内部函数声明 ============= */
void Motor_Init(Motor_TypeDef   *hMotor,
                uint32_t        *PWM_Channel,
				GPIO_TypeDef	*GPIO_Port,
				uint16_t		Pin,
                uint16_t        PWM_Channel_DutyMax);

void SetSpeed_LF(int16_t Speed);//左前
void SetSpeed_RF(int16_t Speed);//右前
void SetSpeed_LB(int16_t Speed);//左后
void SetSpeed_RB(int16_t Speed);//右后
//"SetSpeed"为设置车轮速度
/* ============ 函数定义 ================= */

/**
  * @name   Switch_GetCode
  * @brief  获取拨码开关的键值
  * @call   Internal or External
  * @param  NULL
  * @RetVal Return value
  */
uint8_t Switch_GetCode(void)
{
    // 记录历史值
    hCtrl.Switch.Code = (hCtrl.Switch.Code & 0x55U) << 1;
    
    // 获取本次的值
    // Switch_1
    hCtrl.Switch.Code |= ((Switch_1_GPIO_Port->IDR & Switch_1_Pin) == Switch_Polarity ? 0x01U : 0x00U) << 2 * 0;
    // Switch_2
    hCtrl.Switch.Code |= ((Switch_2_GPIO_Port->IDR & Switch_2_Pin) == Switch_Polarity ? 0x01U : 0x00U) << 2 * 1;
    // Switch_3
    hCtrl.Switch.Code |= ((Switch_3_GPIO_Port->IDR & Switch_3_Pin) == Switch_Polarity ? 0x01U : 0x00U) << 2 * 2;
    // Switch_4
    hCtrl.Switch.Code |= ((Switch_4_GPIO_Port->IDR & Switch_4_Pin) == Switch_Polarity ? 0x01U : 0x00U) << 2 * 3;
    
    return hCtrl.Switch.Code & 0x55U;
    
}/* Switch_GetCode() */

/**
  * @name   Motor_Init()
  * @brief  电机句柄初始化
  * @call   Internal
  * @param  hMotor              要初始化的电机句柄
  * @param  Channel_A           电机的通道A
  * @param  Channel_B           电机的通道B
  * @param  Channel_A_DutyMax   电机通道A的最大占空
  * @param  Channel_B_DutyMax   电机通道B的最大占空
  * @RetVal NULL
  */
void Motor_Init(Motor_TypeDef   *hMotor,
                uint32_t        *PWM_Channel,
				GPIO_TypeDef	*GPIO_Port,
				uint16_t		Pin,
                uint16_t        PWM_Channel_DutyMax)
{
    hMotor->PWM_Channel         = PWM_Channel;
	hMotor->GPIO_Port			= GPIO_Port;
	hMotor->Pin					= Pin;
	
    hMotor->PWM_Channel_DutyMax   = PWM_Channel_DutyMax;    
    hMotor->PWM_Channel_Duty      = 0;
	
	HAL_GPIO_WritePin(hMotor->GPIO_Port, hMotor->Pin, GPIO_PIN_RESET);
}/* Motor_Init() */
    
/**
  * @name   Chassis_Init()
  * @brief  底盘初始化
  * @call   External
  * @param  NULL
  * @RetVal NULL
  */
void Chassis_Init(void)
{   
    Motor_Init(&hCtrl.Chassis.LF, Motor_LF_PWM, Motor_LF_IO_GPIO_Port, Motor_LF_IO_Pin  , 10000);//左前
    Motor_Init(&hCtrl.Chassis.LB, Motor_LR_PWM, Motor_LR_IO_GPIO_Port, Motor_LR_IO_Pin  , 10000);//左后
	
    Motor_Init(&hCtrl.Chassis.RF, Motor_RF_PWM, Motor_RF_IO_GPIO_Port, Motor_RF_IO_Pin  , 10000);//右前
    Motor_Init(&hCtrl.Chassis.RB, Motor_RR_PWM, Motor_RR_IO_GPIO_Port, Motor_RR_IO_Pin  , 10000);//右后
}/* Chassis_Init() */


/**
  * @name   SetSpeed_LF
  * @brief  设置左前轮的速度
  * @call   Internal or External
  * @param  Speed   要设置的速度 -10000 _ 10000
  * @RetVal NULL
  */


//{3700, 3900, 3600, 3750}      轮胎动力补偿 RF - LF - RB - LB
void SetSpeed_LF(int16_t Speed)
{   
    if(SignOf(Speed) == 1)//判断符号（+-）
    {    
        hCtrl.Chassis.LF.PWM_Channel_Duty = 6500;//Speed + F_Offset_Wheel.LF;
		HAL_GPIO_WritePin(hCtrl.Chassis.LF.GPIO_Port, hCtrl.Chassis.LF  .Pin, GPIO_PIN_RESET);
    }
    else
    {
        hCtrl.Chassis.LF.PWM_Channel_Duty = 0;//ABS(10000 + Speed - F_Offset_Wheel.LF);
		HAL_GPIO_WritePin(hCtrl.Chassis.LF.GPIO_Port, hCtrl.Chassis.LF.Pin, GPIO_PIN_SET);
    }
    PWM_SetDuty(hCtrl.Chassis.LF.PWM_Channel, hCtrl.Chassis.LF.PWM_Channel_Duty);
}/* SetSpeed_LF() */

/**
  * @name   SetSpeed_RF
  * @brief  设置右前轮的速度
  * @call   Internal or External
  * @param  Speed   要设置的速度 -10000 _ 10000
  * @RetVal NULL
  */
void SetSpeed_RF(int16_t Speed)
{
    if(SignOf(Speed) == 1)//判断符号（+-）
    {    
        hCtrl.Chassis.RF.PWM_Channel_Duty = 10000;//Speed + F_Offset_Wheel.RF;
		HAL_GPIO_WritePin(hCtrl.Chassis.RF.GPIO_Port, hCtrl.Chassis.RF.Pin, GPIO_PIN_RESET);
    }
    else
    {
        hCtrl.Chassis.RF.PWM_Channel_Duty = 200;//ABS(10000 + Speed - F_Offset_Wheel.RF);
		HAL_GPIO_WritePin(hCtrl.Chassis.RF.GPIO_Port, hCtrl.Chassis.RF.Pin, GPIO_PIN_SET);
    }
    PWM_SetDuty(hCtrl.Chassis.RF.PWM_Channel, hCtrl.Chassis.RF.PWM_Channel_Duty);
}/* SetSpeed_RF() */

/**
  * @name   SetSpeed_LB
  * @brief  设置左后轮的速度
  * @call   Internal or External
  * @param  Speed   要设置的速度 -10000 _ 10000
  * @RetVal NULL
  */
void SetSpeed_LB(int16_t Speed)
{
    if(SignOf(Speed) == 1)//判断符号（+-）
    {    
        hCtrl.Chassis.LB.PWM_Channel_Duty = 7500;//Speed + F_Offset_Wheel.LB;
		HAL_GPIO_WritePin(hCtrl.Chassis.LB.GPIO_Port, hCtrl.Chassis.LB.Pin, GPIO_PIN_RESET);
    }
    else
    {
        hCtrl.Chassis.LB.PWM_Channel_Duty = 150;//ABS(10000 + Speed - F_Offset_Wheel.LB);
		HAL_GPIO_WritePin(hCtrl.Chassis.LB.GPIO_Port, hCtrl.Chassis.LB.Pin, GPIO_PIN_SET);
    }
    PWM_SetDuty(hCtrl.Chassis.LB.PWM_Channel, hCtrl.Chassis.LB.PWM_Channel_Duty);
}/* SetSpeed_LB() */

/**
  * @name   SetSpeed_RB
  * @brief  设置左前轮的速度
  * @call   Internal or External
  * @param  Speed   要设置的速度 -10000 _ 10000
  * @RetVal NULL
  */
void SetSpeed_RB(int16_t Speed)
{
    if(SignOf(Speed) == 1)//判断符号（+-）
    {    
        hCtrl.Chassis.RB.PWM_Channel_Duty = 10000;//Speed + F_Offset_Wheel.RB;
		HAL_GPIO_WritePin(hCtrl.Chassis.RB.GPIO_Port, hCtrl.Chassis.RB.Pin, GPIO_PIN_RESET);
    }
    else
    {
        hCtrl.Chassis.RB.PWM_Channel_Duty = 300;//ABS(10000 + Speed - F_Offset_Wheel.RB);
		HAL_GPIO_WritePin(hCtrl.Chassis.RB.GPIO_Port, hCtrl.Chassis.RB.Pin, GPIO_PIN_SET);
    }
    PWM_SetDuty(hCtrl.Chassis.RB.PWM_Channel, hCtrl.Chassis.RB.PWM_Channel_Duty);
}/* SetSpeed_RB() */

/**
  * @name   ChassisCtrl()
  * @brief  控制底盘的运动
  * @call   External
  * @param  Vx      底盘x轴速度
  * @param  Vy      底盘Y轴速度
  * @RetVal NULL
  */
void ChassisCtrl(int16_t Vy, int16_t Vx)
{
		int16_t Vlf = Vy + Vx;
		int16_t Vrf = Vy - Vx;
		int16_t Vlb = Vy + Vx;
		int16_t Vrb = Vy - Vx;

		int16_t max_val = ABS(Vlf);
		if(ABS(Vrf) > max_val) max_val = ABS(Vrf);
		if(ABS(Vlb) > max_val) max_val = ABS(Vlb);
		if(ABS(Vrb) > max_val) max_val = ABS(Vrb);

		if(max_val > 10000)
		{
				float k = 10000.0f / max_val;
				Vlf = (int16_t)(Vlf * k);
				Vrf = (int16_t)(Vrf * k);
				Vlb = (int16_t)(Vlb * k);
				Vrb = (int16_t)(Vrb * k);
		}
		
		SetSpeed_LF(Vlf);
    SetSpeed_RF(Vrf);
    SetSpeed_LB(Vlb);
    SetSpeed_RB(Vrb);
}/* ChassisCtrl() */



