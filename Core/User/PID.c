#include "PID.h"
extern struct MOTO MOTO_PARA;
extern PS2_TypeDef PS2_Data;
struct Tar_speed target_speed=
{
    .yaw=0,
    .X=0,
    .Y=0,
    .speed_M1=0,
    .speed_M2=0,
};
struct PID_Calc M1,M2,Distance_X,Distance_Y,angle,angle_speed;

struct ROBOT_position ROBOT_pos=
{
    .yaw=0,
    .X=0,
    .Y=0,
    .distance_ALL=0,
};
void PID_PARA_Init(void)
{
    M1.Kp=0.158;
    M1.Ki=0.01;
    M2.Kp=-0.59;
    M2.Ki=-0.004;

    angle.Kp=4;
    angle.Ki=0.1;
    angle.Kd=0;
}

/*处理陀螺仪对面的诡异位置*/
float Handle_Angle8191_PID_Over_Zero(float target, float cur)
{
    if(target - cur > 180)    //180 ：半圈机械角度
    {
        cur += 360;        //359,360无所谓了，四舍五入
    }
    else if(target - cur < -180)
    {
        cur = cur - 360;
    }
    return cur;

}

float angle_out(float Target_yaw,float yaw,float Gyro_Z)
{
    static float yaw_=0;
    yaw_=Handle_Angle8191_PID_Over_Zero(Target_yaw,yaw);
    angle.err=Target_yaw-yaw_;
    angle.integral+=angle.err;
    angle.integral=range(angle.integral,-30,30);//积分限幅
    if(fabs(angle.err)<1)
    {
        angle.Target_speed=0;
        angle.integral=0;
        angle.arrived=1;
    }
    else
    {
        angle.Target_speed=angle.err*angle.Kp+
                           angle.integral*angle.Ki+
                           Gyro_Z*angle.Kd;
        angle.arrived=0;
    }
    angle.Target_speed=range(angle.Target_speed,-30,30);

    return angle.Target_speed;
}

float angle_speed_in(float Target_yaw_speed,float Yaw_speed)
{
    angle_speed.err=Target_yaw_speed-Yaw_speed;
    angle_speed.integral+=angle_speed.err;
    angle_speed.integral=range(angle_speed.integral,-200,200);//积分限幅
    angle_speed.Target_pwm=angle_speed.err*angle_speed.Kp+
                           angle_speed.integral*angle_speed.Ki+
                           (angle_speed.err-angle_speed.err_last)*angle_speed.Kd;
    angle_speed.err_last=angle_speed.err;
    return angle_speed.Target_pwm;
}

int Incremental_PI_1(int Encoder,int Target)
{
    M1.err=Target-Encoder;
    if(fabs(M1.err)<2)
    {
        M1.integral=0;
    }
    else
    {
        M1.integral=M1.Ki*M1.err;
        M1.integral=range(M1.integral,-1500,1500);
    }
    M1.Target_pwm+=M1.Kp*(M1.err-M1.err_last)+M1.integral;
    M1.err_last=M1.err;
    M1.Target_pwm=range(M1.Target_pwm,-4000,4000);
    return (int)M1.Target_pwm;
}

int Incremental_PI_2(int Encoder,int Target)
{
    M2.err=Target-Encoder;
    if(fabs(M2.err)<2)
    {
        M2.integral=0;
    }
    else
    {
        M2.integral=M2.Ki*M2.err;
        M2.integral=range(M2.integral,-1500,1500);
    }
    M2.Target_pwm+=M2.Kp*(M2.err-M2.err_last)+M2.integral;//
    M2.err_last=M2.err;
    M2.Target_pwm=range(M2.Target_pwm,-4000,4000);
    return (int)M2.Target_pwm;
}
/*相关参数清零*/
void PID_PARA_intergal_clear(void)
{
    M1.err=0;
    M1.err_last=0;
    M1.integral=0;
    M2.err=0;
    M2.err_last=0;
    M2.integral=0;
    angle.err=0;
    angle.err_last=0;
    angle.integral=0;
    angle.Target_speed=0;

}

void PID_Calc_ALL(void)
{

    Distance_Calculation();
    //target_speed.yaw=angle_out(0,ROBOT_pos.yaw);
    /**
    * 遥控模式
    */
    target_speed.speed_M1=(int)(0.2*(PS2_Data.Rocker_LY+PS2_Data.Rocker_LX));
    target_speed.speed_M2=(int)(0.2*(PS2_Data.Rocker_LY-PS2_Data.Rocker_LX));
    MOTO_PARA.PWM_OUT1=Incremental_PI_1(MOTO_PARA.speed1_current,target_speed.speed_M1);
    MOTO_PARA.PWM_OUT2=Incremental_PI_2(MOTO_PARA.speed2_current,target_speed.speed_M2);
    Set_PWM_Wheel(MOTO_PARA.PWM_OUT1,MOTO_PARA.PWM_OUT2);
     /***
      * 自动偏航模式
    */
    /**
			target_speed.yaw=angle_out(0,ROBOT_pos.yaw,ROBOT_pos.gyro_Z);
			target_speed.Y=0;
			target_speed.speed_M1=(int)(0.2*(target_speed.yaw+target_speed.Y));
			target_speed.speed_M2=(int)(0.2*(-target_speed.yaw+target_speed.Y));
			Set_PWM_Wheel(MOTO_PARA.PWM_OUT1,MOTO_PARA.PWM_OUT2);
    */
}

void Distance_Calculation()
{
    ROBOT_pos.Y+=(int)((MOTO_PARA.speed1_current+MOTO_PARA.speed2_current)*0.5);
    ROBOT_pos.X+=(int)((MOTO_PARA.speed1_current-MOTO_PARA.speed2_current)*0.5);
    ROBOT_pos.distance_ALL=sqrt(ROBOT_pos.Y*ROBOT_pos.Y+ROBOT_pos.X*ROBOT_pos.X);

}