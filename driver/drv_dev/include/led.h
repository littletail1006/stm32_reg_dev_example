/*******************************************************************************
 * @file     led.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2024-01-19 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __LED_H 
#define __LED_H

// [include]————————————————————————————————————————————————————————————————————
#include "common.h"

// [define]—————————————————————————————————————————————————————————————————————
#define GPIOB_BASE_ADDR   (unsigned int)0X40010C00
#define RCC_BASE_ADDR     (unsigned int)0x40021000
#define RCC_APB2ENR     *((volatile unsigned int*)(RCC_BASE_ADDR+0x18))
#define GPIOB_CRL       *((volatile unsigned int*)(GPIOB_BASE_ADDR+0x00))
#define GPIOB_ODR       *((volatile unsigned int*)(GPIOB_BASE_ADDR+0x0c))
#define GPIOB_BSRR      *((volatile unsigned int*)(GPIOB_BASE_ADDR+0x10))
#define GPIOB_BRR       *((volatile unsigned int*)(GPIOB_BASE_ADDR+0x14))

#define LED              PB_OUT(5)
#define LED_STATE        PB_IN(5)
// [function declaration]———————————————————————————————————————————————————————
extern void led_init(void);
extern void led_on(void);
extern void led_off(void);

#endif
