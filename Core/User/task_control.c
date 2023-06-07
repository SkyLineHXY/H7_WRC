#include "main.h"
void pump_contorl(uint8_t t);
void actuator_control(uint8_t t);
void mask_contorl(uint8_t t);
void task_contorl(void);
extern PS2_TypeDef PS2_Data;

void task_contorl(void)
{
    /***
     * 控制电缸
     */
	if(PS2_Data.Key_R1==1&&PS2_Data.Key_R2==0)
	{
        actuator_control(1);
	}
    else if(PS2_Data.Key_R1==0&&PS2_Data.Key_R2==1)
    {
        actuator_control(0);
    }
    else
    {
        actuator_control(2);
    }

    /**
     * 控制捞网
     * */
    if(PS2_Data.Key_L1==1&&PS2_Data.Key_L2==0)
    {
        mask_contorl(1);
    }
    else if(PS2_Data.Key_L1==0&&PS2_Data.Key_L2==1)
    {
        mask_contorl(0);
    }

    /***
     * 控制水泵
     */
     if(PS2_Data.Key_L_Right==1)
     {
         pump_contorl(1);
     }
     else
     {
         pump_contorl(0);
     }
}

void actuator_control(uint8_t t)
{
	switch(t)
	{
		/***
		 * 电缸控制
		 */
		case 0:
		{
			HAL_GPIO_WritePin(actuator_1A_GPIO_Port,actuator_1A_Pin,SET);
            HAL_GPIO_WritePin(actuator_1B_GPIO_Port,actuator_1B_Pin,RESET);


            HAL_GPIO_WritePin(actuator_2A_GPIO_Port,actuator_2A_Pin,RESET);
            HAL_GPIO_WritePin(actuator_2B_GPIO_Port,actuator_2B_Pin,SET);
			break;
		}

        case 1:
        {
            HAL_GPIO_WritePin(actuator_1A_GPIO_Port,actuator_1A_Pin,RESET);
            HAL_GPIO_WritePin(actuator_1B_GPIO_Port,actuator_1B_Pin,SET);

            HAL_GPIO_WritePin(actuator_2A_GPIO_Port,actuator_2A_Pin,SET);
            HAL_GPIO_WritePin(actuator_2B_GPIO_Port,actuator_2B_Pin,RESET);
            break;
        }

        case 2:
        {
            HAL_GPIO_WritePin(actuator_1A_GPIO_Port,actuator_1A_Pin,RESET);
            HAL_GPIO_WritePin(actuator_1B_GPIO_Port,actuator_1B_Pin,RESET);

            HAL_GPIO_WritePin(actuator_2A_GPIO_Port,actuator_2A_Pin,RESET);
            HAL_GPIO_WritePin(actuator_2B_GPIO_Port,actuator_2B_Pin,RESET);
            break;
        }
	}
}
/***
 * 捞网控制
 * @param t 输入变量
 */
void mask_contorl(uint8_t t)
{
    switch (t) {
        case 0:
        {
            servo_low();
            break;
        }
        case 1:
        {
            servo_high();
            break;
        }
    }
}
/***
 * 水泵控制
 * @param t 控制变量
 */
void pump_contorl(uint8_t t)
{
    switch (t) {
        case 0:
        {
            HAL_GPIO_WritePin(RELAY_1_GPIO_Port,RELAY_1_Pin,SET);
            HAL_GPIO_WritePin(RELAY_2_GPIO_Port,RELAY_2_Pin,SET);
            break;
        }
        case 1:
        {
            HAL_GPIO_WritePin(RELAY_1_GPIO_Port,RELAY_1_Pin,RESET);
            HAL_GPIO_WritePin(RELAY_2_GPIO_Port,RELAY_2_Pin,RESET);
            break;
        }
    }
}