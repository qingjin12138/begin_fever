#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\lvgl.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\porting\lv_port_disp.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\examples\lv_examples.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\gui_app\huxing.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\lv_conf.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\draw\lv_draw.h"
#include "D:\Embedded chip and system design competition (Qinxin)\оƬ����\CH32V307EVT����\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\src\font\lv_font.h"
#include "time.h"
extern unsigned int  turn;
   static void set_angle(void * obj,int32_t v)
{
   lv_arc_set_value(obj,v);


}
/*************************************************
 *  �������� :  arc_show_2
 *  ��    �� �� ��
 *  �������� �� Բ��ʾ����
 *************************************************/
void arc_show_2()
{

   lv_obj_t * arc = lv_arc_create(lv_scr_act());//����Բ������
   lv_arc_set_rotation(arc,0);                  //�������λ��
   lv_arc_set_bg_angles(arc,0,360);             //���ýǶ�
   lv_arc_set_range(arc,0,360);
   lv_arc_set_change_rate(arc,1);

   lv_obj_set_size(arc,200,200);                   //���óߴ�

   lv_obj_remove_style(arc,NULL,LV_PART_KNOB);  //�Ƴ���ʽ
   lv_obj_clear_flag(arc,LV_OBJ_FLAG_CLICKABLE);//�����־λ
//   lv_obj_center(arc);                          //������ʾ
   lv_obj_align(arc, LV_ALIGN_TOP_MID, 0, 40);
   lv_anim_t a;                                 //������������
   lv_anim_init(&a);                            //��ʼ������
   lv_anim_set_var(&a,arc);                     //�󶨶�������
   lv_anim_set_exec_cb(&a,set_angle);           //���ûص�
   lv_anim_set_time(&a,turn);                  //����ʱ��   10000
   lv_anim_set_repeat_count(&a,0); //�����ظ�  LV_ANIM_REPEAT_INFINITE
   lv_anim_set_repeat_delay(&a,500);            //�����ظ���ʱ
   lv_anim_set_values(&a,0,360);                //���ö����Ŀ�ʼ�ͽ���ֵ
   lv_anim_start(&a);                           //��ʼ����
}


