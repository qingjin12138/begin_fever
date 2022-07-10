/*
 * lcdinit.c
 *
 *  Created on: 2022��6��12��
 *      Author: 35509
 */
#include "lcdinit.h"
#include "debug.h"
#include "lcd.h"

void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��A�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_14);
}

/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
    u8 i;
    LCD_CS_Clr();
    for(i=0;i<8;i++)
    {
        LCD_SCLK_Clr();
        if(dat&0x80)
        {
           LCD_MOSI_Set();
        }
        else
        {
           LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat<<=1;
    }
  LCD_CS_Set();
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
    LCD_Writ_Bus(dat>>8);
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();//д����
    LCD_Writ_Bus(dat);
    LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//������д
}

void LCD_Init(void)
{
    LCD_GPIO_Init();//��ʼ��GPIO

    LCD_RES_Clr();//��λ
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);

    LCD_BLK_Set();//�򿪱���
  delay_ms(100);

    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); //Sleep out
    delay_ms(120);              //Delay 120ms
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0Xf0);
    LCD_WR_DATA8(0xc3);
    LCD_WR_REG(0Xf0);
    LCD_WR_DATA8(0x96);
    LCD_WR_REG(0x36);    // Memory Access Control
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x48);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0x88);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x28);
    else LCD_WR_DATA8(0xE8);
    LCD_WR_REG(0X3a);
    LCD_WR_DATA8(0x05);
    LCD_WR_REG(0Xe6);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0xf2);
    LCD_WR_DATA8(0x3f);
    LCD_WR_DATA8(0x4f);
    LCD_WR_DATA8(0x4f);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x0e);
    LCD_WR_DATA8(0x00);
    LCD_WR_REG(0Xc5);
    LCD_WR_DATA8(0x2a);
    LCD_WR_REG(0Xe0);
    LCD_WR_DATA8(0xf0);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x0a);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x1c);
    LCD_WR_DATA8(0x3b);
    LCD_WR_DATA8(0x55);
    LCD_WR_DATA8(0x4a);
    LCD_WR_DATA8(0x0a);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x1c);
    LCD_WR_DATA8(0x1f);
    LCD_WR_REG(0Xe1);
    LCD_WR_DATA8(0xf0);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x0a);
    LCD_WR_DATA8(0x0c);
    LCD_WR_DATA8(0x0c);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x54);
    LCD_WR_DATA8(0x49);
    LCD_WR_DATA8(0x0f);
    LCD_WR_DATA8(0x1b);
    LCD_WR_DATA8(0x18);
    LCD_WR_DATA8(0x1b);
    LCD_WR_DATA8(0x1f);
    LCD_WR_REG(0Xf0);
    LCD_WR_DATA8(0x3c);
    LCD_WR_REG(0Xf0);
    LCD_WR_DATA8(0x69);
    LCD_WR_REG(0X29);
}








