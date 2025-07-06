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
#ifndef __I2C_H
#define __I2C_H

// [include]————————————————————————————————————————————————————————————————————
#include "common.h"

// [define]—————————————————————————————————————————————————————————————————————


// [function declaration]———————————————————————————————————————————————————————
extern void i2c1_init(void);
extern void i2c1_master_write_byte(uint8_t dev_addr,uint8_t reg_addr, const uint8_t data);
extern uint8_t i2c1_master_read_byte(uint8_t dev_addr,uint8_t reg_addr);
extern void i2c1_master_write(uint8_t dev_addr,uint8_t reg_addr, const uint8_t *data,uint16_t len);
extern void i2c1_master_read(uint8_t dev_addr,uint8_t reg_addr,  uint8_t *data, uint16_t len);

#endif
