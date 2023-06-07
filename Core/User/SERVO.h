#ifndef SERVO_H
#define SERVO_H

#include "main.h"
#define GET_LOW_BYTE(A) ((uint8_t)(A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
#define Servo_RX_Tail 0x11
#define Servo_RX_Header 0x01
#define FRAME_HEADER 0x55             //帧头
#define CMD_SERVO_MOVE 0x03           //舵机移动指令
#define CMD_ACTION_GROUP_RUN 0x06     //运行动作组指令
#define CMD_ACTION_GROUP_STOP 0x07    //停止动作组指令
#define CMD_ACTION_GROUP_SPEED 0x0B   //设置动作组运行速度
#define CMD_GET_BATTERY_VOLTAGE 0x0F  //获取电池电压指令

typedef enum {
    false = 0, true = !false
}bool;
typedef struct _servo_
{  //舵机ID,舵机目标位置
    uint8_t ID;
    uint16_t Position;
} Servo_dd;

void receiveHandle(void);
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time);//移动舵机
void moveServosByArray(Servo_dd servos[], uint8_t Num, uint16_t Time);//同时控制多舵机执行同一动作
void moveServos(uint8_t Num, uint16_t Time, ...);//控制多舵机分别执行各自动作
void stopActionGroup(void);//停止动作组
void runActionGroup(uint8_t numOfAction, uint16_t Times);//运行舵机动作组
void setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed);//设定动作组运行时间

/**
 * 小船舵机控制
 * */
void servo_contorl_boat(uint16_t Position_1,uint16_t Position_2,uint16_t time);
//沉入
void servo_low(void);
//捞取
void servo_high(void);
#endif