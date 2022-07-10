///*
// * key.c
// *
// *  Created on: 2022年6月23日
// *      Author: 35509
// */
//#include "debug.h"
//#include "key.h"
//
//
//
////
//////按键初始化函数
////void KEY_Init(void) //IO初始化
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////
////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
////
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
////    GPIO_Init(GPIOE, &GPIO_InitStructure);
////
////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
////    GPIO_Init(GPIOA, &GPIO_InitStructure);
////
////
////}
////
////
////u8 KEY_Scan(u8 mode)
////{
////    static u8 key_up=1;//按键按松开标志
////    if(mode)key_up=1;  //支持连按
////    if(key_up&&(KEY0==1||KEY1==0||KEY2==0))
////    {
////        Delay_Ms(10);//去抖动
////        key_up=0;
////        if(KEY0==1)return KEY0_PRES;
////        else if(KEY1==0)return KEY1_PRES;
////        else if(KEY2==0)return KEY2_PRES;
////    }else if(KEY0==0&&KEY1==1&&KEY2==1)key_up=1;
////    return 0;// 无按键按下
////}
////
