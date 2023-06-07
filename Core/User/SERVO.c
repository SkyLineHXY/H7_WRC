#include "SERVO.h"

uint8_t LobotTxBuf[50]={0};
extern struct USART_RX_Data USART_RX_DATA;
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Time)//移动舵机
{
    if (servoID > 31 || !(Time > 0))
    {  //舵机ID不能打于31,可根据对应控制板修改
        return;
    }
    LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;    //填充帧头
    LobotTxBuf[2] = 8;						  //数据长度=要控制舵机数*3+5，此处=1*3+5
    LobotTxBuf[3] = CMD_SERVO_MOVE;           //填充舵机移动指令
    LobotTxBuf[4] = 1;                        //要控制的舵机个数
    LobotTxBuf[5] = GET_LOW_BYTE(Time);       //取得时间的低八位
    LobotTxBuf[6] = GET_HIGH_BYTE(Time);      //取得时间的高八位
    LobotTxBuf[7] = servoID;                  //舵机ID
    LobotTxBuf[8] = GET_LOW_BYTE(Position);   //取得目标位置的低八位
    LobotTxBuf[9] = GET_HIGH_BYTE(Position);  //取得目标位置的高八位
    USART2_send_str_SERVO(LobotTxBuf,LobotTxBuf[2]+2);
}

/*********************************************************************************
 * Function:  moveServosByArray
 * Description： 控制多个舵机转动
 * Parameters:   servos[]:舵机结体数组，Num:舵机个数,Time:转动时间
                    0 < Num <= 32,Time > 0
 * Return:       无返回
 * Others:
 **********************************************************************************/
void moveServosByArray(Servo_dd servos[], uint8_t Num, uint16_t Time)
{
    uint8_t index = 7;
    uint8_t i = 0;

    if (Num < 1 || Num > 32 || !(Time > 0)) {
        return;                                          //舵机数不能为零和大与32，时间不能为零
    }
    LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;      //填充帧头
    LobotTxBuf[2] = Num * 3 + 5;                       //数据长度 = 要控制舵机数*3+5
    LobotTxBuf[3] = CMD_SERVO_MOVE;                    //填充舵机移动指令
    LobotTxBuf[4] = Num;                               //要控制的舵机个数
    LobotTxBuf[5] = GET_LOW_BYTE(Time);                //取得时间的低八位
    LobotTxBuf[6] = GET_HIGH_BYTE(Time);               //取得时间的高八位

    for (i = 0; i < Num; i++) {                        //循环填充舵机ID和对应目标位置
        LobotTxBuf[index++] = servos[i].ID;              //填充舵机ID
        LobotTxBuf[index++] = GET_LOW_BYTE(servos[i].Position); //填充目标位置低八位
        LobotTxBuf[index++] = GET_HIGH_BYTE(servos[i].Position);//填充目标位置高八位
    }
    USART2_send_str_SERVO(LobotTxBuf,LobotTxBuf[2]+2);
}


/*********************************************************************************
 * Function:  runActionGroup
 * Description： 运行指定动作组
 * Parameters:   NumOfAction:动作组序号, Times:执行次数
 * Return:       无返回
 * Others:       Times = 0 时无限循环
 **********************************************************************************/
void runActionGroup(uint8_t numOfAction, uint16_t Times)
{
    LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;  //填充帧头
    LobotTxBuf[2] = 5;                      //数据长度，数据帧除帧头部分数据字节数，此命令固定为5
    LobotTxBuf[3] = CMD_ACTION_GROUP_RUN;   //填充运行动作组命令
    LobotTxBuf[4] = numOfAction;            //填充要运行的动作组号
    LobotTxBuf[5] = GET_LOW_BYTE(Times);    //取得要运行次数的低八位
    LobotTxBuf[6] = GET_HIGH_BYTE(Times);   //取得要运行次数的高八位

    USART2_send_str_SERVO(LobotTxBuf,7);
}

/*********************************************************************************
 * Function:  stopActiongGroup
 * Description： 停止动作组运行
 * Parameters:   Speed: 目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void stopActionGroup(void)
{
    LobotTxBuf[0] = FRAME_HEADER;     //填充帧头
    LobotTxBuf[1] = FRAME_HEADER;
    LobotTxBuf[2] = 2;                //数据长度，数据帧除帧头部分数据字节数，此命令固定为2
    LobotTxBuf[3] = CMD_ACTION_GROUP_STOP;   //填充停止运行动作组命令

    USART2_send_str_SERVO(LobotTxBuf,4);
}

/*********************************************************************************
 * Function:  setActionGroupSpeed
 * Description： 设定指定动作组的运行速度
 * Parameters:   NumOfAction: 动作组序号 , Speed:目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed)
{
    LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;   //填充帧头
    LobotTxBuf[2] = 5;                       //数据长度，数据帧除帧头部分数据字节数，此命令固定为5
    LobotTxBuf[3] = CMD_ACTION_GROUP_SPEED;  //填充设置动作组速度命令
    LobotTxBuf[4] = numOfAction;             //填充要设置的动作组号
    LobotTxBuf[5] = GET_LOW_BYTE(Speed);     //获得目标速度的低八位
    LobotTxBuf[6] = GET_HIGH_BYTE(Speed);    //获得目标熟读的高八位
    USART2_send_str_SERVO(LobotTxBuf,7);
}

/*********************************************************************************
 * Function:  setAllActionGroupSpeed
 * Description： 设置所有动作组的运行速度
 * Parameters:   Speed: 目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void setAllActionGroupSpeed(uint16_t Speed)
{
    setActionGroupSpeed(0xFF, Speed);  //调用动作组速度设定，组号为0xFF时设置所有组的速度
}

//获取电池电压指令
void getBatteryVoltage(void)
{
//	uint16_t Voltage = 0;
    LobotTxBuf[0] = FRAME_HEADER;  //填充帧头
    LobotTxBuf[1] = FRAME_HEADER;
    LobotTxBuf[2] = 2;             //数据长度，数据帧除帧头部分数据字节数，此命令固定为2
    LobotTxBuf[3] = CMD_GET_BATTERY_VOLTAGE;  //填充获取电池电压命令

    USART_send_str(&huart2,LobotTxBuf);
}

void servo_contorl_boat(uint16_t Position_1,uint16_t Position_2,uint16_t time)
{
    LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;      //填充帧头
    LobotTxBuf[2] =2*3+5;                //数据长度 = 要控制舵机数 * 3 + 5
    LobotTxBuf[3] = CMD_SERVO_MOVE;             //舵机移动指令
    LobotTxBuf[4] =6;                        //要控制舵机数
    LobotTxBuf[5] = GET_LOW_BYTE(time);         //取得时间的低八位
    LobotTxBuf[6] = GET_HIGH_BYTE(time);        //取得时间的高八位
    LobotTxBuf[7] = 1;
    LobotTxBuf[8] = GET_LOW_BYTE(Position_1);
    LobotTxBuf[9] = GET_HIGH_BYTE(Position_1);//填充目标位置高八位
    LobotTxBuf[10] = 2;//左舵机
    LobotTxBuf[11] = GET_LOW_BYTE(Position_2);
    LobotTxBuf[12] = GET_HIGH_BYTE(Position_2);//填充目标位置高八位

    USART2_send_str_SERVO(LobotTxBuf,13);
}
void servo_low()
{
    servo_contorl_boat(305,790,1500);
    delay_ms(1600);
}

void servo_high()
{
    servo_contorl_boat(570,515,1500);
    delay_ms(1600);
}