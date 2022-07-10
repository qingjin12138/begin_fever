#include "rotaryknob.h"
#include "debug.h"
u8 KUP;//旋钮锁死标志（1为锁死）
u16 cou;

void ENCODER_Init(void){ //接口初始化
    GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_D; //选择端口号
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻
    GPIO_Init(ENCODER_PORT_E,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ENCODER_R; //选择端口号
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻
    GPIO_Init(ENCODER_PORT_D,&GPIO_InitStructure);
}

unsigned int ENCODER_READ(void){ //接口初始化
    u8 a;//存放按键的值
    u8 kt;
    a=0;
    if(GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L))KUP=0;   //判断旋钮是否解除锁死
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)&&KUP==0){ //判断是否旋转旋钮，同时判断是否有旋钮锁死
        Delay_Us(100);
        kt=GPIO_ReadInputDataBit(ENCODER_PORT_D,ENCODER_R); //把旋钮另一端电平状态记录
        Delay_Ms(3); //延时
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)){ //去抖
            if(kt==0){ //用另一端判断左或右旋转
                a=1;//右转
            }else{
                a=2;//左转
            }
            cou=0; //初始锁死判断计数器
            while(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)&&cou<60000){ //等待放开旋钮，同时累加判断锁死
                cou++;KUP=1;Delay_Us(20); //
            }
        }
    }
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_D)&&KUP==0){ //判断旋钮是否按下
        Delay_Ms(20);
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_D)){ //去抖动
            a=3;//在按键按下时加上按键的状态值
            while(ENCODER_D==0);
        }
    }
    return a;
}



