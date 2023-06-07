#ifndef __PSTWO_H
#define __PSTWO_H
#include  "main.h"

#define DI   HAL_GPIO_ReadPin(PS2_DI_GPIO_Port,PS2_DI_Pin)          //PB5  输入

#define DO_H HAL_GPIO_WritePin(PS2_DO_GPIO_Port,PS2_DO_Pin,1)        //命令位高
#define DO_L HAL_GPIO_WritePin(PS2_DO_GPIO_Port,PS2_DO_Pin,0)         //命令位低

#define CS_H HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,1)       //CS拉高
#define CS_L HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,0)        //CS拉低

#define CLK_H HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,1)      //时钟拉高
#define CLK_L HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,0)      //时钟拉低

//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8
#define u8 uint8_t
#define u16 uint16_t
extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;


typedef struct
{
    uint8_t A_D;                                       //模拟(红灯)为1 数字(无灯)为0
    int8_t Rocker_RX, Rocker_RY, Rocker_LX, Rocker_LY; //摇杆值(模拟状态为实际值0-0xFF)(数字态为等效的值0,0x80,0xFF)
    //按键值0为未触发,1为触发态
    uint8_t Key_L1, Key_L2, Key_R1, Key_R2;                //后侧大按键
    uint8_t Key_L_Right, Key_L_Left, Key_L_Up, Key_L_Down; //左侧按键
    uint8_t Key_R_Right, Key_R_Left, Key_R_Up, Key_R_Down; //右侧按键
    uint8_t Key_Select;                                    //选择键
    uint8_t Key_Start;                                     //开始键
    uint8_t Key_Rocker_Left, Key_Rocker_Right;             //摇杆按键

} PS2_TypeDef;


void PS2_Init(void);
u8 PS2_RedLight(void);   //判断是否为红灯模式
void PS2_ReadData(void); //读手柄数据
void PS2_Cmd(u8 CMD);		  //向手柄发送命令
u8 PS2_DataKey(void);		  //按键值读取
u8 PS2_AnologData(u8 button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区
void PS2_Vibration(u8 motor1, u8 motor2);//振动设置motor1  0xFF开，其他关，motor2  0x40~0xFF

void PS2_EnterConfing(void);	 //进入配置
void PS2_TurnOnAnalogMode(void); //发送模拟量
void PS2_VibrationMode(void);    //振动设置
void PS2_ExitConfing(void);	     //完成配置
void PS2_SetInit(void);		     //配置初始化
void PS2_Receive (void);


void PS2_Read_Data(void);




//代码2
void PS2_Cmd_2(u8 cmd);
void PS2_Read(void);
u8 PS2_DataKey_1(void);
#endif




