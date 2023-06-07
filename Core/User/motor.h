#ifndef MOTO_H
#define MOTO_H
extern int PAUSE;
struct MOTO
{
    //两个轮子当前速度
    int speed1_current;
    int speed2_current;

    //编码器积分距离
    int M1_distance;
    int M2_distance;
    //积分开始标志位
    int Intgral_M1_flag;
    int Intgral_M2_flag;

    //两个轮子最终PWM输出
    int PWM_OUT1;
    int PWM_OUT2;
};
int16_t  Read_Encoder_M1(void);
int16_t  Read_Encoder_M2(void);
void Set_PWM_Wheel(int M1,int M2);

void MOTOR1_Frun(void);
void MOTOR1_Rrun(void);
void MOTOR2_Frun(void);
void MOTOR2_Rrun(void);
#endif