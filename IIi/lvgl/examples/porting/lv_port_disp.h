/**
 * @file lv_port_disp_templ.h
 *
 */

/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "D:\Embedded chip and system design competition (Qinxin)\Ð¾Æ¬×ÊÁÏ\CH32V307EVTÀý³Ì\opench-ch32v307-master\firmware\IIC_Sensor\lvgl\lvgl.h"
#include "lcdinit.h"

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES 480
#define MY_DISP_VER_RES 320

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_port_disp_init(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/
