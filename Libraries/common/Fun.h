#ifndef __FUN_H
#define __FUN_H
    
#include "headfiles.h"

/* =========== �궨�� ============= */
#define Amplitude_Limit(Value,Dowm,Up)  ((Value) < (Dowm) ? (Dowm) : ((Value) > (Up) ? (Up) : (Value)));
#define Step_Limit(New,Old,Range)       (New > (Old + Range) ? (Old + Range) : (New < (Old - Range) ? (Old - Range) : (New)))
#define ABS(x)                          (((x) >= (0.0f)) ? (x) : (-(x)))
#define Data_Limit(Value,Dowm,Up)       ((Value) < (Dowm) ? (Dowm) : ((Value) > (Up) ? (Up) : (Value)))
#define Limited_Add(Value,MAX)          ((++Value) > MAX ? MAX : Value)
#define SignOf(Value)                   ((Value < 0.0) ? (-1.0) : (1.0))
#define Deg2Rad(deg)                    ((double)deg * 0.0174532925)
#define Rad2Deg(rad)                    ((double)rad * 57.295779513)
#define Increase_Limit(var, limit)      (var = (++var) > limit ? (limit+1) : var)

#define PI                              (3.1415926535897932384626433832795f)


#define VOFA_JustFloat_index    8

/* ========= ȫ�ֱ������� ========== */
//extern int tdata[8];
extern int ztx;
//extern int zty;
extern int UP;
extern int GRAP;
extern int ZHUA;
/* =========== �������� ============ */
void MasterPC_send(UART_HandleTypeDef *huart);
void VOFA_JustFloat(UART_HandleTypeDef *huart);
void Motor_Drive(GPIO_TypeDef *IO1_Port, uint16_t IO1_Pin, GPIO_PinState State1, GPIO_TypeDef *IO2_Port, uint16_t IO2_Pin, GPIO_PinState State2);


//int fputc(int ch, FILE *f);

#endif /*__FUN_H*/

