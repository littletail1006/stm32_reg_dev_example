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
#ifndef __I2C_IO_H
#define __I2C_IO_H

// [include]————————————————————————————————————————————————————————————————————
#include "common.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void sw_i2c_init(void);
extern void sw_i2c_write_byte(uint8_t dev_addr,uint8_t reg_addr, const uint8_t data);
extern uint8_t sw_i2c_read_byte(uint8_t dev_addr,uint8_t reg_addr);
extern void sw_i2c_write(uint8_t dev_addr,uint8_t reg_addr, const uint8_t *data,uint16_t len);
extern void sw_i2c_read(uint8_t dev_addr,uint8_t reg_addr,  uint8_t *data, uint16_t len);

#endif
