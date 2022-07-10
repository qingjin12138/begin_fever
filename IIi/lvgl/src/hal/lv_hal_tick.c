/**
 * @file lv_hal_tick.c
 * Provide access to the system tick with 1 millisecond resolution
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_hal_tick.h"
#include <stddef.h>


#include "lcdinit.h"
#include "bigcd.h"
#if LV_TICK_CUSTOM == 1
    #include LV_TICK_CUSTOM_INCLUDE
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
#if !LV_TICK_CUSTOM
    static uint32_t sys_time = 0;
    static volatile uint8_t tick_irq_flag;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

#if !LV_TICK_CUSTOM
/**
 * You have to call this function periodically
 * @param tick_period the call period of this function in milliseconds
 */
LV_ATTRIBUTE_TICK_INC void lv_tick_inc(uint32_t tick_period)
{
    extern unsigned int minute;
    extern unsigned int second;
    extern unsigned int intratemporal;
    extern unsigned int suspend;
    tick_irq_flag = 0;
    sys_time += tick_period;

    LCD_ShowIntNum(248,110,second,2,RED,WHITE,32);    //显示定时时间的秒位
    LCD_ShowString(232,110,":",RED,WHITE,32,0);       //显示单位“:”
    LCD_ShowIntNum(200,110,minute,2,RED,WHITE,32);    //显示定时时间的分钟位
    LCD_ShowIntNum(230,150,intratemporal/100,2,RED,WHITE,24);

    if (minute|second!=0) {

    if (minute<=0) {
        minute=0;
    }
    if (second<=0) {
        second=60;
        minute--;
    }
    if (minute<=60) {
        second--;
    }
    }
    else {
        minute=0;second=0;
    }

    suspend++;

    int a = rand()%10;
    if (suspend==5)
    {
        LCD_Fill(0,0,480,24,GRAY240);               //设置背景为白色
    switch(a)
    {
    case 0:
        LCD_ShowChinese(0,0,"一寸光阴一寸金  寸金难买寸光阴",RED,GRAY240,24,0);
        break;
    case 1:
        LCD_ShowChinese(0,0,"世上最累人的事  莫过于虚伪的过日子",RED,GRAY240,24,0);
        break;
    case 2:
        LCD_ShowChinese(0,0,"游手好闲的人最没有空闲",RED,GRAY240,24,0);
        break;
    case 3:
        LCD_ShowChinese(0,0,"立志宜思真品格  读书须尽苦功夫",RED,GRAY240,24,0);
        break;
    case 4:
        LCD_ShowChinese(0,0,"鸟欲高飞先振翅  人求上进先读书",RED,GRAY240,24,0);
        break;
    case 5:
        LCD_ShowChinese(0,0,"学而不思则罔  思而不学则殆",RED,GRAY240,24,0);
        break;
    case 6:
        LCD_ShowChinese(0,0,"知之者不如好之者  好之者不如乐之者",RED,GRAY240,24,0);
        break;
    case 7:
        LCD_ShowChinese(0,0,"苦读是做学问的一个好方法",RED,GRAY240,24,0);
        break;
    case 8:
        LCD_ShowChinese(0,0,"博观而约取  厚积而薄发",RED,GRAY240,24,0);
        break;
    case 9:
        LCD_ShowChinese(0,0,"发奋识遍天下字  立志读尽人间书",RED,GRAY240,24,0);
        break;

    }
    suspend=0;
    }

}
#endif

/**
 * Get the elapsed milliseconds since start up
 * @return the elapsed milliseconds
 */
uint32_t lv_tick_get(void)
{
#if LV_TICK_CUSTOM == 0

    /*If `lv_tick_inc` is called from an interrupt while `sys_time` is read
     *the result might be corrupted.
     *This loop detects if `lv_tick_inc` was called while reading `sys_time`.
     *If `tick_irq_flag` was cleared in `lv_tick_inc` try to read again
     *until `tick_irq_flag` remains `1`.*/
    uint32_t result;
    do {
        tick_irq_flag = 1;
        result        = sys_time;
    } while(!tick_irq_flag); /*Continue until see a non interrupted cycle*/

    return result;
#else
    return LV_TICK_CUSTOM_SYS_TIME_EXPR;
#endif
}

/**
 * Get the elapsed milliseconds since a previous time stamp
 * @param prev_tick a previous time stamp (return value of lv_tick_get() )
 * @return the elapsed milliseconds since 'prev_tick'
 */
uint32_t lv_tick_elaps(uint32_t prev_tick)
{
    uint32_t act_time = lv_tick_get();

    /*If there is no overflow in sys_time simple subtract*/
    if(act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    }
    else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
