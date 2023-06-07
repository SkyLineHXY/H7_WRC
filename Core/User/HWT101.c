
#include "HWT101.h"
char YAWCMD[5] = {0XFF,0XAA,0X76,0X00,0X00};//Z轴置零指令

char HWT101_linpian[5]={0xFF,0xAA,0x48,0x01,0x00};//Z轴自动获取零偏
static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0;
struct SAngle 	stcAngle;
struct SGyro    stcGyro;
float Yaw_current=0,yaw_t;
float Gyro_z=0;


extern struct USART_RX_Data USART_RX_DATA;
void CopeSerial6Data(unsigned char ucData)
{

    USART_RX_DATA.U6_RX_BUF[USART_RX_DATA.U6_RX_COUNT++]=ucData;	//将收到的数据存入缓冲区中
    if (USART_RX_DATA.U6_RX_BUF[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
    {
        USART_RX_DATA.U6_RX_COUNT=0;
        return;
    }
    if (USART_RX_DATA.U6_RX_COUNT<11) {return;}//数据不满11个，则返回
    else
    {
        switch(USART_RX_DATA.U6_RX_BUF[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
        {
            case 0x52:	memcpy(&stcGyro, &USART_RX_DATA.U6_RX_BUF[2],8); break;
            case 0x53:	memcpy(&stcAngle,&USART_RX_DATA.U6_RX_BUF[2],8);break;
        }
        USART_RX_DATA.U6_RX_COUNT=0;//清空缓存区
    }
}

short IF_Angle_Close_to(float target_angle)
{
    float bais=target_angle-Yaw_current;//判断当前角度与目标值偏差，取绝对值后小于1°即认为接近
    if (fabs(bais)<1.0)
        return 1;
    else
        return 0;
}
void Config_Z(void)
{
    sendcmd(YAWCMD); //Z轴置零指令
}

void huoqulinpian(void)
{
    sendcmd(HWT101_linpian);
}

void sendcmd(char cmd[])
{
    char i;
    for(i=0;i<5;i++)
        USART_send_char(&huart6,cmd[i]);
}

void USART6_Put_String(unsigned char *Str)
{
    while(*Str)
    {
        if(*Str=='\r')USART_send_char(&huart6,0x0d);
        else if(*Str=='\n')USART_send_char(&huart6,0x0a);
        else USART_send_char(&huart6,*Str);
        Str++;
    }
}


