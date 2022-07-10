//日期：2022年7月1日11:46:23
/*
 * Log dated 29 June 2022
 * SW1   开始计时
 * SW2   统计
 * UP    改时间
 *
 */
/*
 * 外设gpio位置
 *              1.滑动旋钮
 * GND--->接地
 * VCC--->3.3V
 * CLK--->D3
 * DT---->E13
 * SW---->E14
 *              2.4.0寸TFT屏幕
 * GND--->接地
 * VCC--->3.3V
 * SCL--->A1
 * SDA--->D10
 * RES--->D9
 * DC---->D11
 * CS---->D8
 * BLK--->E15
 *
 */
#include "debug.h"
#include "AHT_10.h"
#include "lcdinit.h"
#include "bigcd.h"
#include "lcd.h"
#include "pic.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\lvgl.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\porting\lv_port_disp.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\lv_examples.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\gui_app\huxing.h"
//下三条为随机数搞的头文件，不用可删除
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\blue\blue.h"
//#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\key\key.h"
///
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\rotaryknob\rotaryknob.h"

#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\beep\beep.h"






                  unsigned int intratemporal,minute,second,correctiontime,suspend,overall,turn,in=0,bluetooth=2;   //时间为n00分钟的倒计时初始化
                  unsigned int front[6]={260,260,260,260,260,260};
                  u8 a=0,b=0,c=0x01;






                    /* Global Variable */
                    u16 TxBuf[1024];
                    s16 Calibrattion_Val = 0;


                    void EXTI0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
                    void EXTI15_10_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

                    /*******************************************************************************
                    * Function Name  : EXTI0_INT_INIT
                    * Description    : Initializes EXTI0 collection.
                    * Input          : None
                    * Return         : None
                    *******************************************************************************/
                    void EXTI_INT_INIT(void)
                    {
                      GPIO_InitTypeDef  GPIO_InitStructure;
                        EXTI_InitTypeDef EXTI_InitStructure;
                        NVIC_InitTypeDef NVIC_InitStructure;

                      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
                      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
                      GPIO_Init(GPIOE, &GPIO_InitStructure);

                      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
                        GPIO_Init(GPIOA, &GPIO_InitStructure);

                        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_13;
                          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
                          GPIO_Init(GPIOD, &GPIO_InitStructure);



                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
                      GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource13);


                      EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line13;
                      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
                      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
                      EXTI_InitStructure.EXTI_LineCmd = ENABLE;
                      EXTI_Init(&EXTI_InitStructure);

                        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
                      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
                      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
                      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
                      NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
                        NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
                        NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
                      NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
                        NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
                      NVIC_Init(&NVIC_InitStructure);

                      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
                        NVIC_Init(&NVIC_InitStructure);
                    }


                    /*******************************************************************************
                    * Function Name  : main
                    * Description    : Main program.
                    * Input          : None
                    * Return         : None
                    *******************************************************************************/









/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{


//    minute=intratemporal/100;         //分钟位
//    second=intratemporal%100;         //秒位

        EXTI_INT_INIT();     //外部中断

        BEEP_Init();            //初始化蜂鸣器端口
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);    //一个白色模板
	float temperature, humidity;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();

    ENCODER_Init(); //旋转编码器初始化

	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
//	KEY_Init();          //初始化与按键连接的硬件接口
    LCD_Init();//LCD初始化
    lcd_init();
    lcd_set_color(BLACK,WHITE);
    lcd_show_string(0, 0, 32,"TEMP & Humidity");
    /*
     * lvgl的入口程序
     */
                    lv_init();
                    lv_port_disp_init();

                    delay_ms(10);

                    DMA_INIT();
                    USARTx_CFG();                                                 /* USART INIT */
                    USART_DMACmd(UART7,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);

                    GPIO_CFG();
                    GPIO_WriteBit(GPIOA, GPIO_Pin_7,RESET); //进入 AT
                    GPIO_WriteBit(GPIOC, GPIO_Pin_13,SET); //enable CH9141
                    Delay_Ms(1000);




	while(AHT10_Init())            //初始化AHT10
    {
        printf("AHT10 Error");    //验证数据是否进入
    }

    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);               //设置背景为白色

    lcd_show_image(0,134,240,100,gImage_dadas);    //在小lcd上显示一个图片





	while(1)
	{




		temperature = AHT10_Read_Temperature();    //获得湿度
		printf("read AHT10 hum\r\n");
		humidity = AHT10_Read_Humidity();          //获得温度

		lcd_set_color(BLACK,GREEN);
		lcd_show_string(10, 70, 32,"TEMP    :%2d C", (int)(temperature));     //显示当前的温度
		lcd_show_string(10, 102, 32,"Humidity:%2dRH", (int)(humidity));       //显示当前的湿度

//            LCD_ShowIntNum(248,110,second,2,RED,WHITE,32);    //显示定时时间的秒位
//            LCD_ShowString(232,110,":",RED,WHITE,32,0);       //显示单位“:”
//            LCD_ShowIntNum(200,110,minute,2,RED,WHITE,32);    //显示定时时间的分钟位



		suspend++;

		int a = rand()%10;
		if (suspend==5)
		{
	        LCD_Fill(0,0,480,24,WHITE);               //设置背景为白色
		switch(a)
		{
		case 0:
		    LCD_ShowChinese(0,0,"一寸光阴一寸金  寸金难买寸光阴",RED,WHITE,24,0);
		    break;
        case 1:
            LCD_ShowChinese(0,0,"世上最累人的事  莫过于虚伪的过日子",RED,WHITE,24,0);
            break;
        case 2:
            LCD_ShowChinese(0,0,"游手好闲的人最没有空闲",RED,WHITE,24,0);
            break;
        case 3:
            LCD_ShowChinese(0,0,"立志宜思真品格  读书须尽苦功夫",RED,WHITE,24,0);
            break;
        case 4:
            LCD_ShowChinese(0,0,"鸟欲高飞先振翅  人求上进先读书",RED,WHITE,24,0);
            break;
        case 5:
            LCD_ShowChinese(0,0,"学而不思则罔  思而不学则殆",RED,WHITE,24,0);
            break;
        case 6:
            LCD_ShowChinese(0,0,"知之者不如好之者  好之者不如乐之者",RED,WHITE,24,0);
            break;
        case 7:
            LCD_ShowChinese(0,0,"苦读是做学问的一个好方法",RED,WHITE,24,0);
            break;
        case 8:
            LCD_ShowChinese(0,0,"博观而约取  厚积而薄发",RED,WHITE,24,0);
            break;
        case 9:
            LCD_ShowChinese(0,0,"发奋识遍天下字  立志读尽人间书",RED,WHITE,24,0);
            break;

		}
		suspend=0;
        }
        Delay_Ms(1000);
        LCD_Fill(0,100,160,320,LIGHTBLUE);
        LCD_ShowChinese(0,100,"改时",WHITE,LIGHTBLUE,32,0);
        LCD_Fill(160,100,320,320,GREEN);
        LCD_ShowChinese(160,100,"定时",WHITE,GREEN,32,0);
        LCD_Fill(320,100,480,320,BRRED);
        LCD_ShowChinese(320,100,"统计",WHITE,BRRED,32,0);




	}

}










            /*******************************************************************************
            * Function Name  : EXTI0_IRQHandler
            * Description    : This function handles EXTI0 Handler.
            * Input          : None
            * Return         : None
            *******************************************************************************/
            void EXTI0_IRQHandler(void)                            //外部中断0，调整所需的时间
            {




//                LCD_Fill(0,0,LCD_W,LCD_H,GRAY240);

              if(EXTI_GetITStatus(EXTI_Line0)!=RESET)      //up按键

              {

                  printf("KEY2 !\r\n");
                                        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
                                        Delay_Ms(50);


                                            LCD_DrawLine(50,260,440,260,BLACK);
                                            LCD_DrawLine(59,20,59,270,BLACK);


                                            LCD_ShowIntNum(40,265,0,1,BLACK,WHITE,24);       //0
                                            LCD_ShowIntNum(26,220,10,2,BLACK,WHITE,24);       //10
                                            LCD_ShowIntNum(26,180,20,2,BLACK,WHITE,24);       //20
                                            LCD_ShowIntNum(26,140,30,2,BLACK,WHITE,24);       //30
                                            LCD_ShowIntNum(26,100,40,2,BLACK,WHITE,24);       //40
                                            LCD_ShowIntNum(26,60,50,2,BLACK,WHITE,24);       //50
                                            LCD_ShowIntNum(26,20,60,2,BLACK,WHITE,24);       //60

                                            LCD_ShowIntNum(79,270,1,1,BLACK,WHITE,24);        //1
                                            LCD_ShowIntNum(139,270,2,1,BLACK,WHITE,24);       //2
                                            LCD_ShowIntNum(199,270,3,1,BLACK,WHITE,24);       //3
                                            LCD_ShowIntNum(259,270,4,1,BLACK,WHITE,24);       //4
                                            LCD_ShowIntNum(319,270,5,1,BLACK,WHITE,24);       //5
                                            LCD_ShowIntNum(379,270,6,1,BLACK,WHITE,24);        //6


                  //                              front=front+20;
                  //                              behind=behind+80;

                                                LCD_Fill(60,front[0],110,260,ORANGE);      //橘色，柱状图   宽50，高front
                                                LCD_Fill(120,front[1],170,260,ORANGE);
                                                LCD_Fill(180,front[2],230,260,ORANGE);
                                                LCD_Fill(240,front[3],290,260,ORANGE);
                                                LCD_Fill(300,front[4],350,260,ORANGE);
                                                LCD_Fill(360,front[5],410,260,ORANGE);



                                                Delay_Ms(5000);

                                                LCD_Fill(0,0,LCD_W,LCD_H,WHITE);    //一个白色模板


                                                LCD_Fill(0,100,160,320,LIGHTBLUE);
                                                LCD_ShowChinese(0,100,"改时",WHITE,LIGHTBLUE,32,0);
                                                LCD_Fill(160,100,320,320,GREEN);
                                                LCD_ShowChinese(160,100,"定时",WHITE,GREEN,32,0);
                                                LCD_Fill(320,100,480,320,BRRED);
                                                LCD_ShowChinese(320,100,"统计",WHITE,BRRED,32,0);

                EXTI_ClearITPendingBit(EXTI_Line0);     /* Clear Flag */

              }
            }

            /*******************************************************************************
            * Function Name  : EXTI0_IRQHandler
            * Description    : This function handles EXTI0 Handler.
            * Input          : None
            * Return         : None
            *******************************************************************************/
            void EXTI1_IRQHandler(void)
            {
              if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
              {
                printf("UP !\r\n");
                EXTI_ClearITPendingBit(EXTI_Line1);     /* Clear Flag */
              }
            }

            /*******************************************************************************
            * Function Name  : EXTI0_IRQHandler
            * Description    : This function handles EXTI0 Handler.
            * Input          : None
            * Return         : None
            *******************************************************************************/
            void EXTI2_IRQHandler(void)
            {
              if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
              {
                printf("DOWN !\r\n");
                EXTI_ClearITPendingBit(EXTI_Line2);     /* Clear Flag */
              }
            }

            void EXTI3_IRQHandler(void)
            {
              if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
              {

                printf("RIGHT !\r\n");
                EXTI_ClearITPendingBit(EXTI_Line3);     /* Clear Flag */
              }
            }


            void EXTI4_IRQHandler(void)
            {

                if (EXTI_GetITStatus(EXTI_Line4)!=RESET) {


















                     LCD_Fill(0,0,LCD_W,LCD_H,WHITE);    //一个白色模板
                                       Delay_Ms(40);
                                       LCD_Fill(0,100,160,320,LIGHTBLUE);
                                       LCD_ShowChinese(0,100,"改时",WHITE,LIGHTBLUE,32,0);

                                       LCD_ShowChinese(10,10,"修改时间为",BRRED,WHITE,32,0);

                                       LCD_ShowChinese(256,10,"分钟",BRRED,WHITE,32,0);
                                                           while(1)
                                                            {

                                                                b=ENCODER_READ();   //读出旋转编码器值
                                                                Delay_Ms(10);
                                                                if(b==1){intratemporal=intratemporal+100;turn=turn+250;} //分析按键值，并加减计数器值。
                                                                Delay_Ms(10);
                                                                if(b==2){intratemporal=intratemporal-100;turn=turn-250;}
                                                                Delay_Ms(10);
                                       //                         if(b==3)a=0;
                                                                if(b!=0){ //如果有旋转器的操作

                                                                LCD_ShowIntNum(180,10,intratemporal/100,4,RED,WHITE,32);

                                                                if (b==3) {              //按下旋钮中间的时候，就退出这个中断
                                                                    break;
                                                               }

                                                                }


                                                              printf("KEY1 !\r\n");
                                                            }
                                                           LCD_Fill(0,0,LCD_W,LCD_H,WHITE);    //一个白色模板


                                                           LCD_Fill(0,100,160,320,LIGHTBLUE);
                                                           LCD_ShowChinese(0,100,"改时",WHITE,LIGHTBLUE,32,0);
                                                           LCD_Fill(160,100,320,320,GREEN);
                                                           LCD_ShowChinese(160,100,"定时",WHITE,GREEN,32,0);
                                                           LCD_Fill(320,100,480,320,BRRED);
                                                           LCD_ShowChinese(320,100,"统计",WHITE,BRRED,32,0);



                    EXTI_ClearITPendingBit(EXTI_Line4);     /* Clear Flag */

                }

            }

            void EXTI9_5_IRQHandler(void)
            {
              if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
              {
                printf("LEFT !\r\n");
                EXTI_ClearITPendingBit(EXTI_Line6);     /* Clear Flag */
              }else {
                  if(EXTI_GetITStatus(EXTI_Line5)!=RESET)                          //进入统计模式(模式3)
                    {
                      LCD_Fill(0,0,LCD_W,LCD_H,GRAY240);
                      bluetooth=intratemporal/100;
                      front[in]=260-(intratemporal/100)*4;
                      bluetooth=intratemporal/100;
                      minute=intratemporal/100;         //分钟位
                      second=intratemporal%100;         //秒位



                      overall=overall+intratemporal/100;

                                        arc_show_2();        //lvgl全部代码

                                        while(!(minute==0&second==0))
                                        {

                                            lv_task_handler();
                                            Delay_Ms(10);
                                            //需周期调用的函数
                                              lv_tick_inc(5);

                                              Delay_Ms(1);

                                              Delay_Ms(887);     //嘀嗒定时器*1秒

                                        }

                                        LCD_Fill(0,0,LCD_W,LCD_H,WHITE);               //程序结束后进行下一步操作（空余入口）

                                        printf("Congratulations on completing a 35-minute session\r\n");

                                        in++;
  //                                    time=120;
                                        LCD_ShowChinese(10,40,"共完成",BRRED,WHITE,32,0);
                                        LCD_ShowIntNum(180,40,overall,4,RED,WHITE,32);
                                        LCD_ShowChinese(256,40,"分钟",BRRED,WHITE,32,0);

                                        LCD_Fill(0,100,160,320,LIGHTBLUE);
                                        LCD_ShowChinese(0,100,"改时",WHITE,LIGHTBLUE,32,0);
                                        LCD_Fill(160,100,320,320,GREEN);
                                        LCD_ShowChinese(160,100,"定时",WHITE,GREEN,32,0);
                                        LCD_Fill(320,100,480,320,BRRED);
                                        LCD_ShowChinese(320,100,"统计",WHITE,BRRED,32,0);
                                        Delay_Ms(20);

  Delay_Ms(100);

                       switch (bluetooth)
                       {
                       case 1: Delay_Ms(100);while(uartWriteBLEstr("accomplish:1minute\r\n")==RESET);Delay_Ms(100);int num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 2: Delay_Ms(100);while(uartWriteBLEstr("accomplish:2minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 3: Delay_Ms(100);while(uartWriteBLEstr("accomplish:3minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 4: Delay_Ms(100);while(uartWriteBLEstr("accomplish:4minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 5: Delay_Ms(100);while(uartWriteBLEstr("accomplish:5minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 6: Delay_Ms(100);while(uartWriteBLEstr("accomplish:6minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 7: Delay_Ms(100);while(uartWriteBLEstr("accomplish:7minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 8: Delay_Ms(100);while(uartWriteBLEstr("accomplish:8minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 9: Delay_Ms(100);while(uartWriteBLEstr("accomplish:9minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 10: Delay_Ms(100);while(uartWriteBLEstr("accomplish:10minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 11: Delay_Ms(100);while(uartWriteBLEstr("accomplish:11minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 12: Delay_Ms(100);while(uartWriteBLEstr("accomplish:12minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 13: Delay_Ms(100);while(uartWriteBLEstr("accomplish:13minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 14: Delay_Ms(100);while(uartWriteBLEstr("accomplish:14minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 15: Delay_Ms(100);while(uartWriteBLEstr("accomplish:15minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 16: Delay_Ms(100);while(uartWriteBLEstr("accomplish:16minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 17: Delay_Ms(100);while(uartWriteBLEstr("accomplish:17minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 18: Delay_Ms(100);while(uartWriteBLEstr("accomplish:18minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 19: Delay_Ms(100);while(uartWriteBLEstr("accomplish:19minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 20: Delay_Ms(100);while(uartWriteBLEstr("accomplish:20minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 21: Delay_Ms(100);while(uartWriteBLEstr("accomplish:21minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 22: Delay_Ms(100);while(uartWriteBLEstr("accomplish:22minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 23: Delay_Ms(100);while(uartWriteBLEstr("accomplish:23minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 24: Delay_Ms(100);while(uartWriteBLEstr("accomplish:24minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 25: Delay_Ms(100);while(uartWriteBLEstr("accomplish:25minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 26: Delay_Ms(100);while(uartWriteBLEstr("accomplish:26minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 27: Delay_Ms(100);while(uartWriteBLEstr("accomplish:27minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 28: Delay_Ms(100);while(uartWriteBLEstr("accomplish:28minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 29: Delay_Ms(100);while(uartWriteBLEstr("accomplish:29minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 30: Delay_Ms(100);while(uartWriteBLEstr("accomplish:30minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 31: Delay_Ms(100);while(uartWriteBLEstr("accomplish:31minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 32: Delay_Ms(100);while(uartWriteBLEstr("accomplish:32minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 33: Delay_Ms(100);while(uartWriteBLEstr("accomplish:33minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 34: Delay_Ms(100);while(uartWriteBLEstr("accomplish:34minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 35: Delay_Ms(100);while(uartWriteBLEstr("accomplish:35minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 36: Delay_Ms(100);while(uartWriteBLEstr("accomplish:36minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 37: Delay_Ms(100);while(uartWriteBLEstr("accomplish:37minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 38: Delay_Ms(100);while(uartWriteBLEstr("accomplish:38minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 39: Delay_Ms(100);while(uartWriteBLEstr("accomplish:39minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 40: Delay_Ms(100);while(uartWriteBLEstr("accomplish:40minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 41: Delay_Ms(100);while(uartWriteBLEstr("accomplish:41minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 42: Delay_Ms(100);while(uartWriteBLEstr("accomplish:42minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 43: Delay_Ms(100);while(uartWriteBLEstr("accomplish:43minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 44: Delay_Ms(100);while(uartWriteBLEstr("accomplish:44minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 45: Delay_Ms(100);while(uartWriteBLEstr("accomplish:45minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 46: Delay_Ms(100);while(uartWriteBLEstr("accomplish:46minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 47: Delay_Ms(100);while(uartWriteBLEstr("accomplish:47minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 48: Delay_Ms(100);while(uartWriteBLEstr("accomplish:48minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 49: Delay_Ms(100);while(uartWriteBLEstr("accomplish:49minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 50: Delay_Ms(100);while(uartWriteBLEstr("accomplish:50minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 51: Delay_Ms(100);while(uartWriteBLEstr("accomplish:51minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 52: Delay_Ms(100);while(uartWriteBLEstr("accomplish:52minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 53: Delay_Ms(100);while(uartWriteBLEstr("accomplish:53minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 54: Delay_Ms(100);while(uartWriteBLEstr("accomplish:54minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 55: Delay_Ms(100);while(uartWriteBLEstr("accomplish:55minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 56: Delay_Ms(100);while(uartWriteBLEstr("accomplish:56minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 57: Delay_Ms(100);while(uartWriteBLEstr("accomplish:57minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 58: Delay_Ms(100);while(uartWriteBLEstr("accomplish:58minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                           break;
                       case 59: Delay_Ms(100);while(uartWriteBLEstr("accomplish:59minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       case 60: Delay_Ms(100);while(uartWriteBLEstr("accomplish:60minute\r\n")==RESET);Delay_Ms(100); num = uartAvailableBLE();if (num > 0 ){char buffer[1024]={"\0"};uartReadBLE(buffer , num);printf("Revceived:%s\r\n",buffer);}GPIO_WriteBit(GPIOA, GPIO_Pin_7,SET); // 退出AT。可用手机或电脑连接CH9141,测试数据收发
                                                break;
                       }








//蜂鸣器提示部分
                       GPIO_SetBits(GPIOB,GPIO_Pin_1);
                       delay_ms(2000);
                       GPIO_ResetBits(GPIOB,GPIO_Pin_1);











                      EXTI_ClearITPendingBit(EXTI_Line5);     /* Clear Flag */
                    }
            }
            }

            void EXTI15_10_IRQHandler(void)
            {
              if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
              {
                printf("SEL !\r\n");
                EXTI_ClearITPendingBit(EXTI_Line13);     /* Clear Flag */
              }
            }
