#ifndef BSP_PID_H
#define BSP_PID_H

#include "main.h"
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define range(x,a,b)  (min(max(x,a),b))
typedef struct PID_PARAMETER
{
    float speed_kp_m1;
    float speed_ki_m1;
    float speed_kd_m1;

    float speed_kp_m2;
    float speed_ki_m2;
    float speed_kd_m2;

    float angle_kp;
    float angle_ki;
    float angle_kd;

    float gyro_kp;
    float gyro_ki;
    float gyro_kd;
}PID_PARA;
struct PID_Calc
{
    float err;
    float err_last;            //定义上一个偏差值
    float integral;            //定义积分值
    float sum;
    float Target_speed;
    float arrived;//成功收敛标志位
    float Target_pwm;
    float Kp,Ki,Kd;
    float PID_out;
};
struct Tar_speed
{
    float yaw;
    float X;
    float Y;
    int speed_M1;
    int speed_M2;
};
struct tar_point
{
    float point_YAW;
    int point_X;
    int point_Y;
};

struct ROBOT_position
{
        float pitch;

        float roll;
        float yaw;
        float gyro_Z;
        int X;
        int Y;
        float distance_ALL;
};

extern struct PID_Calc M1,M2,Distance_X,Distance_Y,angle;
extern struct Tar_speed target_speed;
/*pid参数初始化*/
void PID_PARA_Init(void);
int Incremental_PI_1 (int Encoder,int Target);//右后
int Incremental_PI_2 (int Encoder,int Target);//左后

float angle_PID_Calc(float Target_yaw,float yaw,float glory_z);
float angle_out(float Target_yaw,float yaw,float Gyro_Z);//角度环外环 输出目标角速度
float angle_speed_in(float Target_yaw_speed,float Yaw_speed);//角速度内环 输出最终转向PWM

void PID_Calc_ALL(void);

/**
 * 船体位姿解算
 * */
void Distance_Calculation(void);

#endif