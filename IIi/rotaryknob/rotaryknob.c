#include "rotaryknob.h"
#include "debug.h"
u8 KUP;//��ť������־��1Ϊ������
u16 cou;

void ENCODER_Init(void){ //�ӿڳ�ʼ��
    GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = ENCODER_L | ENCODER_D; //ѡ��˿ں�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������
    GPIO_Init(ENCODER_PORT_E,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ENCODER_R; //ѡ��˿ں�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������
    GPIO_Init(ENCODER_PORT_D,&GPIO_InitStructure);
}

unsigned int ENCODER_READ(void){ //�ӿڳ�ʼ��
    u8 a;//��Ű�����ֵ
    u8 kt;
    a=0;
    if(GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L))KUP=0;   //�ж���ť�Ƿ�������
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)&&KUP==0){ //�ж��Ƿ���ת��ť��ͬʱ�ж��Ƿ�����ť����
        Delay_Us(100);
        kt=GPIO_ReadInputDataBit(ENCODER_PORT_D,ENCODER_R); //����ť��һ�˵�ƽ״̬��¼
        Delay_Ms(3); //��ʱ
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)){ //ȥ��
            if(kt==0){ //����һ���ж��������ת
                a=1;//��ת
            }else{
                a=2;//��ת
            }
            cou=0; //��ʼ�����жϼ�����
            while(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_L)&&cou<60000){ //�ȴ��ſ���ť��ͬʱ�ۼ��ж�����
                cou++;KUP=1;Delay_Us(20); //
            }
        }
    }
    if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_D)&&KUP==0){ //�ж���ť�Ƿ���
        Delay_Ms(20);
        if(!GPIO_ReadInputDataBit(ENCODER_PORT_E,ENCODER_D)){ //ȥ����
            a=3;//�ڰ�������ʱ���ϰ�����״ֵ̬
            while(ENCODER_D==0);
        }
    }
    return a;
}



