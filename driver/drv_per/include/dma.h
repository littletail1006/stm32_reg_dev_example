/*******************************************************************************
 * @file     dma.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __DMA_H
#define __DMA_H

// [include]————————————————————————————————————————————————————————————————————
#include "common.h"
#include <stdbool.h>

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void dma1_ch1_mem2mem_init(void);
extern void dma1_ch4_mem2per_init(void);
extern void dma1_ch5_per2mem_init(void);

#endif
