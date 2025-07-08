/*******************************************************************************
 * @file     pwr.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __PWR_H
#define __PWR_H

// [include]————————————————————————————————————————————————————————————————————
#include "stm32f103xe.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void pwr_enter_sleep_mode(void);
extern void pwr_enter_stop_mode(void);
extern void pwr_enter_standby_mode(void);
extern void pwr_stop_wakeup_usart(void); 
#endif
