#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\lvgl.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\porting\lv_port_disp.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\lv_examples.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\gui_app\huxing.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\lv_conf.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\draw\lv_draw.h"
#include "D:\Embedded chip and system design competition (Qinxin)\芯片资料\CH32V307EVT例程\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\font\lv_font.h"
#include "time.h"
extern unsigned int  turn;
   static void set_angle(void * obj,int32_t v)
{
   lv_arc_set_value(obj,v);


}
/*************************************************
 *  函数名称 :  arc_show_2
 *  参    数 ： 无
 *  函数功能 ： 圆弧示例二
 *************************************************/
void arc_show_2()
{

   lv_obj_t * arc = lv_arc_create(lv_scr_act());//创建圆弧对象
   lv_arc_set_rotation(arc,0);                  //设置零度位置
   lv_arc_set_bg_angles(arc,0,360);             //设置角度
   lv_arc_set_range(arc,0,360);
   lv_arc_set_change_rate(arc,1);

   lv_obj_set_size(arc,200,200);                   //设置尺寸

   lv_obj_remove_style(arc,NULL,LV_PART_KNOB);  //移除样式
   lv_obj_clear_flag(arc,LV_OBJ_FLAG_CLICKABLE);//清除标志位
//   lv_obj_center(arc);                          //居中显示
   lv_obj_align(arc, LV_ALIGN_TOP_MID, 0, 40);
   lv_anim_t a;                                 //创建动画对象
   lv_anim_init(&a);                            //初始化对象
   lv_anim_set_var(&a,arc);                     //绑定动画对象
   lv_anim_set_exec_cb(&a,set_angle);           //设置回调
   lv_anim_set_time(&a,turn);                  //设置时间   10000
   lv_anim_set_repeat_count(&a,0); //设置重复  LV_ANIM_REPEAT_INFINITE
   lv_anim_set_repeat_delay(&a,500);            //设置重复延时
   lv_anim_set_values(&a,0,360);                //设置动画的开始和结束值
   lv_anim_start(&a);                           //开始动画
}


