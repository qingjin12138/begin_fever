/*
 * rotaryknob.h
 *
 *  Created on: 2022年6月25日
 *      Author: 35509
 */

#ifndef ROTARYKNOB_ROTARYKNOB_H_
#define ROTARYKNOB_ROTARYKNOB_H_


#define ENCODER_PORT_E  GPIOE       //定义IO接口组
#define ENCODER_L   GPIO_Pin_13  //定义IO接口，DT，旋钮左转
#define ENCODER_D   GPIO_Pin_14  //定义IO接口,SW;旋钮按下

#define ENCODER_PORT_D  GPIOD       //定义IO接口组
#define ENCODER_R   GPIO_Pin_3  //定义IO接口,CLK，旋钮右转

void ENCODER_Init(void);//初始化
unsigned int ENCODER_READ(void);

#endif /* ROTARYKNOB_ROTARYKNOB_H_ */
