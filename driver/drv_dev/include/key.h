/*******************************************************************************
 * @file     key.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2024-01-19 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __KEY_H 
#define __KEY_H

#ifdef __cplusplus
extern "C" {
#endif

// [include]————————————————————————————————————————————————————————————————————
#include <stdint.h>

// [define]—————————————————————————————————————————————————————————————————————
#define GPIOC_BASE_ADDR   (unsigned int)0X40011000
#define RCC_BASE_ADDR     (unsigned int)0x40021000
#define RCC_APB2ENR     *((volatile unsigned int*)(RCC_BASE_ADDR+0x18))
#define GPIOC_CRH       *((volatile unsigned int*)(GPIOC_BASE_ADDR+0x04))
#define GPIOC_IDR       *((volatile unsigned int*)(GPIOC_BASE_ADDR+0x08))
#define GPIOC_BSRR      *((volatile unsigned int*)(GPIOC_BASE_ADDR+0x10))
#define GPIOC_BRR       *((volatile unsigned int*)(GPIOC_BASE_ADDR+0x14))

#define KEY_UP            0
#define KEY_NO            1
#define KEY1              (GPIOC_IDR&(1<<13))


// [function declaration]———————————————————————————————————————————————————————
extern void key_init(void);
extern uint8_t key_scan(void);



#ifdef __cplusplus
}
#endif

#endif
