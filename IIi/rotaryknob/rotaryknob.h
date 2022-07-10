/*
 * rotaryknob.h
 *
 *  Created on: 2022��6��25��
 *      Author: 35509
 */

#ifndef ROTARYKNOB_ROTARYKNOB_H_
#define ROTARYKNOB_ROTARYKNOB_H_


#define ENCODER_PORT_E  GPIOE       //����IO�ӿ���
#define ENCODER_L   GPIO_Pin_13  //����IO�ӿڣ�DT����ť��ת
#define ENCODER_D   GPIO_Pin_14  //����IO�ӿ�,SW;��ť����

#define ENCODER_PORT_D  GPIOD       //����IO�ӿ���
#define ENCODER_R   GPIO_Pin_3  //����IO�ӿ�,CLK����ť��ת

void ENCODER_Init(void);//��ʼ��
unsigned int ENCODER_READ(void);

#endif /* ROTARYKNOB_ROTARYKNOB_H_ */
