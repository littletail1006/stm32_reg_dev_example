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
#ifndef __WDG_H
#define __WDG_H

// [include]————————————————————————————————————————————————————————————————————
#include "stm32f103xe.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void iwdg_init(uint8_t pre,uint16_t rlr);
extern void wwdg_init(uint8_t pre, uint8_t wr, uint8_t tr);
extern void iwdg_feed(void);
extern void wwdg_feed(void);


#endif
