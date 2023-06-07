#include "main.h"
#include "motor.h"
struct MOTO MOTO_PARA=
{
    .speed1_current=0,
    .speed2_current=0,
    .M1_distance=0,
    .M2_distance=0,
    .PWM_OUT1=0,
    .PWM_OUT2=0,
    .Intgral_M2_flag=1,
};
extern struct ROBOT_position ROBOT_pos;
char txt[20]={0};
/*测速函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {

    //LED1_TOG;
    if (htim->Instance == TIM7)
    {
			
				PS2_Receive();
        MOTO_PARA.speed1_current=Read_Encoder_M1();
        MOTO_PARA.speed2_current=Read_Encoder_M2();

       // Set_PWM_Wheel(MOTO_PARA.PWM_OUT1,0);
        MOTO_PARA.PWM_OUT1=Incremental_PI_1(MOTO_PARA.speed1_current,target_speed.speed_M1);
        MOTO_PARA.PWM_OUT2=Incremental_PI_2(MOTO_PARA.speed2_current,target_speed.speed_M2);
        Set_PWM_Wheel(MOTO_PARA.PWM_OUT1,MOTO_PARA.PWM_OUT2);
       // PID_Calc_ALL();
    }
}
/*
 *  读取左轮电机转速
 */
int16_t  Read_Encoder_M1(void)
{
    int16_t  ENCODE_CURRENT;
    ENCODE_CURRENT=__HAL_TIM_GetCounter(&htim2);
    /*积算距离*/
    if(MOTO_PARA.Intgral_M1_flag)
    {
        MOTO_PARA.M1_distance+=ENCODE_CURRENT;
    }
    else
    {
        MOTO_PARA.M1_distance=0;
    }
    __HAL_TIM_SetCounter(&htim2, 0);//清空计数值
    return ENCODE_CURRENT;
}

/*
 *  读取右轮电机转速
 */
int16_t  Read_Encoder_M2(void)
{
    int16_t  ENCODE_CURRENT;
    ENCODE_CURRENT=__HAL_TIM_GetCounter(&htim3);
    /*积算距离*/
    if(MOTO_PARA.Intgral_M2_flag)
    {
        MOTO_PARA.M2_distance+=ENCODE_CURRENT;
    }
    else
    {
        MOTO_PARA.M2_distance=0;
    }
    __HAL_TIM_SetCounter(&htim3, 0);//清空计数值
    return ENCODE_CURRENT;
}
/*设置电机PWM输出*/
void Set_PWM_Wheel(int M1,int M2)
{
    if(M1<=0)
    {
        TIM5->CCR1=-M1;
        MOTOR1_Frun();
    }
    else
    {
        TIM5->CCR1=M1;
        MOTOR1_Rrun();
    }
    if(M2<=0)
    {
        TIM5->CCR2=-M2;
        MOTOR2_Frun();
    }
    else
    {
        TIM5->CCR2=M2;
        MOTOR2_Rrun();
    }
}


void MOTOR1_Frun(void)
{
    HAL_GPIO_WritePin(MOTO1_H_GPIO_Port,MOTO1_H_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTO1_L_GPIO_Port,MOTO1_L_Pin,GPIO_PIN_RESET);
}
void MOTOR1_Rrun(void)
{
    HAL_GPIO_WritePin(MOTO1_H_GPIO_Port,MOTO1_H_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTO1_L_GPIO_Port,MOTO1_L_Pin,GPIO_PIN_SET);
}
void MOTOR2_Frun(void)
{
    HAL_GPIO_WritePin(MOTO2_H_GPIO_Port,MOTO2_H_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTO2_L_GPIO_Port,MOTO2_L_Pin,GPIO_PIN_RESET);
}
void MOTOR2_Rrun(void)
{
    HAL_GPIO_WritePin(MOTO2_H_GPIO_Port,MOTO2_H_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTO2_L_GPIO_Port,MOTO2_L_Pin,GPIO_PIN_SET);
}