/*******************************************************************************
 * @file     usart.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __USART_H
#define __USART_H

// [include]————————————————————————————————————————————————————————————————————
#include "common.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void usart1_init(void);
extern void usart1_send(uint8_t ch);
extern void usart1_send_str(uint8_t *str);
extern uint32_t usart1_tx_dma(uint8_t *buf,uint32_t len,uint8_t flag);
extern uint32_t usart1_rx_dma_int(uint8_t *buf,uint32_t len);
#endif
