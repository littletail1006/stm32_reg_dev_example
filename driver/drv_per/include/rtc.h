/*******************************************************************************
 * @file     adc.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __RTC_H
#define __RTC_H

// [include]————————————————————————————————————————————————————————————————————
#include "stm32f103xe.h"

// [define]—————————————————————————————————————————————————————————————————————
typedef struct {
    uint16_t year;   // e.g. 2025
    uint8_t  month;  // 1-12
    uint8_t  day;    // 1-31
    uint8_t  hour;   // 0-23
    uint8_t  minute; // 0-59
    uint8_t  second; // 0-59
} date_t;

enum CB_TYPE{
    SEC_HANDLE,
    ALARM_HANLDE
};
#define  DEFAULT_DATE \
{                     \
      2025,           \
         7,           \
         5,           \
         9,           \
        18,           \
        10            \
}

// [function declaration]———————————————————————————————————————————————————————
extern void rtc_init(void);
extern void rtc_time_set(uint32_t sec);
extern uint32_t rtc_time_get(void);
extern void rtc_date_set(date_t *cal);
extern void rtc_date_get(date_t *cal);
extern void rtc_alarm_time_set(uint32_t alarm_s);
extern void rtc_alarm_date_set(date_t *cal);
extern void rtc_int_callback_set(enum CB_TYPE type,void (*pfun_cb)(void));
#endif
