#include "Fun.h"
//int tdata[8];                                                                                                                                   
int ztx=0;//״̬x�����ڿ���ֱ��״̬��0Ϊ���ɿ��ƣ�1Ϊ����ֱ��
//int zty=0;//״̬y�����ڿ���ֱ��״̬��0Ϊ���ɿ��ƣ�1Ϊ����ԭ��תȦ
int UP=0;//��̨״̬0&1&2
int GRAP=0;//ץȡ״̬0&1
int ZHUA=0;
/**
  * @brief  通用 H 桥电机驱动（纯 IO 口）
  *         直接设置两个方向脚的电平
  * @param  IO1_Port/IO1_Pin/State1  方向脚 1 及其电平
  * @param  IO2_Port/IO2_Pin/State2  方向脚 2 及其电平
  * @retval None
  */
void Motor_Drive(GPIO_TypeDef *IO1_Port, uint16_t IO1_Pin, GPIO_PinState State1, GPIO_TypeDef *IO2_Port, uint16_t IO2_Pin, GPIO_PinState State2)
{
	HAL_GPIO_WritePin(IO1_Port, IO1_Pin, State1);
	HAL_GPIO_WritePin(IO2_Port, IO2_Pin, State2);
}

void VOFA_JustFloat(UART_HandleTypeDef *huart)
{
    float data[VOFA_JustFloat_index] = {0.0};
    const uint8_t end[4] = {0x00, 0x00, 0x80, 0x7f};

    data[0] = hRC.ChannelData_Raw[0];
    data[1] = hRC.ChannelData_Raw[1];
    data[2] = hRC.ChannelData_Raw[2];
    data[3] = hRC.ChannelData_Raw[3];
    data[4] = hRC.ChannelData_Raw[4];
    data[5] = hRC.ChannelData_Raw[5];
    data[6] = hRC.ChannelData_Raw[6];
    data[7] = hRC.ChannelData_Raw[7];
	/*for(int i=0;i<=7;i++){
		tdata[i]=data[i];
	}*/
	
	
	
	
    
    Usart_SendArr(huart, (uint8_t*)data, sizeof(float) * VOFA_JustFloat_index);

    Usart_SendArr(huart, (uint8_t*)end, 4);
}


void MasterPC_send(UART_HandleTypeDef *huart)
{
    signed int SendData_Temp = 0;
    unsigned char SendData_Temp_High,SendData_Temp_Low;

    Usart_SendByte(huart,0xFF);
    Usart_SendByte(huart,0x00);

    //����1
//    SendData_Temp = (signed int)PID_body_Omega.pOut;
    SendData_Temp_High = SendData_Temp >> 8;
    SendData_Temp_Low = SendData_Temp & 0xff;
    Usart_SendByte(huart,SendData_Temp_Low);
    Usart_SendByte(huart,SendData_Temp_High);

    //����2
//    SendData_Temp = (signed int)PID_body_Omega.iOut;
    SendData_Temp_High = SendData_Temp >> 8;
    SendData_Temp_Low = SendData_Temp & 0xff;
    Usart_SendByte(huart,SendData_Temp_Low);
    Usart_SendByte(huart,SendData_Temp_High);

    //����3
//    SendData_Temp = (signed int)PID_body_Angle.pOut;
    SendData_Temp_High = SendData_Temp >> 8;
    SendData_Temp_Low = SendData_Temp & 0xff;
    Usart_SendByte(huart,SendData_Temp_Low);
    Usart_SendByte(huart,SendData_Temp_High);

    //����4
//    SendData_Temp = (signed int)PID_body_Angle.iOut;
    SendData_Temp_High = SendData_Temp >> 8;
    SendData_Temp_Low = SendData_Temp & 0xff;
    Usart_SendByte(huart,SendData_Temp_Low);
    Usart_SendByte(huart,SendData_Temp_High);

    //����5
//    SendData_Temp = (signed int)PID_body_Angle.dOut;
    SendData_Temp_High = SendData_Temp >> 8;
    SendData_Temp_Low = SendData_Temp & 0xff;
    Usart_SendByte(huart,SendData_Temp_Low);
    Usart_SendByte(huart,SendData_Temp_High);

//    //����6
//    SendData_Temp = (signed int)PID_body_Omega.out;
//    SendData_Temp_High = SendData_Temp >> 8;
//    SendData_Temp_Low = SendData_Temp & 0xff;
//    Usart_SendByte(&huart4,SendData_Temp_Low);
//    Usart_SendByte(&huart4,SendData_Temp_High);

//    //����7
//    SendData_Temp = (signed int)giGyro_Z;
//    SendData_Temp_High = SendData_Temp >> 8;
//    SendData_Temp_Low = SendData_Temp & 0xff;
//    Usart_SendByte(&huart4,SendData_Temp_Low);
//    Usart_SendByte(&huart4,SendData_Temp_High);

//    //����8
//    SendData_Temp = (signed int)0;
//    SendData_Temp_High = SendData_Temp >> 8;
//    SendData_Temp_Low = SendData_Temp & 0xff;
//    Usart_SendByte(&huart4,SendData_Temp_Low);
//    Usart_SendByte(&huart4,SendData_Temp_High);

    Usart_SendByte(huart,0xAA);
    Usart_SendByte(huart,0x55);
}






