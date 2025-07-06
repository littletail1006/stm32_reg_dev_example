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
#ifndef __ADC_H
#define __ADC_H

// [include]————————————————————————————————————————————————————————————————————
#include "stm32f103xe.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void adc1_init(void);
extern void adc1_dma_init(void);
extern  uint16_t adc1_start_read(void);


#endif
