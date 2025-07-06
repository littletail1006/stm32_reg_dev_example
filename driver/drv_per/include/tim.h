/*******************************************************************************
 * @file     tim.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __TIM_H
#define __TIM_H

// [include]————————————————————————————————————————————————————————————————————
#include "stm32f103xe.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void tim1_init(uint16_t psc,uint16_t arr);
extern void tim2_init(uint16_t psc,uint16_t arr);
extern void tim7_init(uint16_t psc,uint16_t arr);
extern void tim1_pwm_ch1_init(uint16_t psc,uint16_t arr);
extern void tim2_pwm_ch1_init(uint16_t psc,uint16_t arr);
extern void tim1_oc_ch1_init(uint16_t psc,uint16_t arr);
extern void tim2_ic_ch1_init(uint16_t psc,uint16_t arr);
extern void set_pwm_ch1_duty_cycle(TIM_TypeDef *tim,uint16_t value);
extern void set_tim_timing_handle(uint8_t tim,void (*cb)(void));
extern void set_tim_capture_handle(void (*cb)(uint32_t value));

#endif
