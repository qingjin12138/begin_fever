///*
// * key.c
// *
// *  Created on: 2022��6��23��
// *      Author: 35509
// */
//#include "debug.h"
//#include "key.h"
//
//
//
////
//////������ʼ������
////void KEY_Init(void) //IO��ʼ��
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
////    static u8 key_up=1;//�������ɿ���־
////    if(mode)key_up=1;  //֧������
////    if(key_up&&(KEY0==1||KEY1==0||KEY2==0))
////    {
////        Delay_Ms(10);//ȥ����
////        key_up=0;
////        if(KEY0==1)return KEY0_PRES;
////        else if(KEY1==0)return KEY1_PRES;
////        else if(KEY2==0)return KEY2_PRES;
////    }else if(KEY0==0&&KEY1==1&&KEY2==1)key_up=1;
////    return 0;// �ް�������
////}
////
