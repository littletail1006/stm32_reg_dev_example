/*******************************************************************************
 * @file     i2c.c
 * @brief    i2c驱动代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "i2c.h"
#include "stm32f103xe.h"

/**
 * [i2c1_init I2C初始化]
 */
void i2c1_init(void)
{
    /*1. 使能时钟————————————————————————————————————————————————————————————*/
    RCC->APB1ENR |= 1 << 21;    // 使能I2C1时钟
    RCC->APB2ENR |= 1 << 3;     // 使能GPIOB时钟
    /*2. 配置I2C IO口————————————————————————————————————————————————————————*/
    GPIOB->CRL &= 0x00000000;  // PB6 7复用开漏输出
    GPIOB->CRL |= 0xFF000000;  // PB6 7复用开漏输出
    /*3. 配置模式————————————————————————————————————————————————————————————*/
    // I2C1->CR1 |= 1 << 10;   // 使能ACK
    /*4. 配置时钟相关————————————————————————————————————————————————————————*/
    I2C1->CR2 |= 36 << 0;   // 输入时钟 36M
    I2C1->CCR |= 1 << 15;   // 快速模式 400k
    I2C1->CCR &= ~(1 << 0); // 占空比 TL/Th=2
    I2C1->CCR |= 30 << 0;   // 快速模式下时钟分配系数 3x(CCR x 1/36000k)=1/400k
    //                         CCR=36000k/(3x400k)=30
    /*5. 配置上升时间————————————————————————————————————————————————————————*/
    I2C1->TRISE = 12;       // 快速模式 300ns/(1000/36)ns=11+1
    /*6. 使能———————————————————————————————————————————————————————————————*/
    I2C1->CR1 |= 1 << 0;    // 使能I2C
}
/**
 * [i2c1_master_write_byte I2C1主机模式 写单字节]
 * @param  dev_addr [从设备地址]
 * @param  reg_addr [写的地址]
 * @param  data     [数据]
 * @return          []
 */
void i2c1_master_write_byte(uint8_t dev_addr, uint8_t reg_addr, const uint8_t data)
{
    /* 1. 总线是否忙碌 */
    while(I2C1->SR2 & 1 << 1);          // [BUSY]
    /* 2. 发送起始信号 */
    I2C1->CR1 |= 1 << 8;                // [START]
    while(!(I2C1->SR1 & 1 << 0));       // [SB]
    /* 3. 发送从机地址(写) */
    I2C1->DR = (dev_addr&0xfe)|0;
    while(!(I2C1->SR1 & 1 << 1));      // [ADDR]
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    /* 4. 发送寄存器地址 */
    I2C1->DR = reg_addr;
    while(!(I2C1->SR1 & 1 << 7));      // [TXE]
    /* 5. 发送数据 */
    I2C1->DR = data;
    while(!(I2C1->SR1 & 1 << 2));      // [BTF]
    while(!(I2C1->SR1 & 1 << 7));      // [BTF]
    /* 5. 发送停止信号 */
    I2C1->CR1 |= 1 << 9;                // [STOP]
}

/**
 * [i2c1_master_read I2C1主机模式 读数据]
 * @param  dev_addr [从设备地址]
 * @param  reg_addr [读的地址]
 * @param  data     [数据]
 * @return          []
 */
uint8_t i2c1_master_read_byte(uint8_t dev_addr, uint8_t reg_addr)
{
    uint8_t data;

    /* 1. 总线是否忙碌 */
    while(I2C1->SR2 & 1 << 1);
    /* 2. 发送起始信号 */
    I2C1->CR1 |= 1 << 8;
    while(!(I2C1->SR1 & 1 << 0));
    /* 3. 发送从机地址(写) */
    I2C1->DR =  (dev_addr&0xfe)|0;
    while(!(I2C1->SR1 & 1 << 1));
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    /* 4. 发送寄存器地址 */
    I2C1->DR = reg_addr;
    while(!(I2C1->SR1 & 1 << 7));
    /* 6. 再次发送起始信号 */
    I2C1->CR1 |= 1 << 8;
    while(!(I2C1->SR1 & 1 << 0));
    /* 7. 发送从机地址(读) */
    I2C1->DR = (dev_addr&0xfe)|1;
    while(!(I2C1->SR1 & 1 << 1));
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    /* 8. 不应答 停止位 */
    I2C1->CR1 &= ~(1 << 10);
    I2C1->CR1 |= 1 << 9;
    /* 9. 读取数据 */
    while(!(I2C1->SR1 & 1 << 6));
    data = I2C1->DR;

    return data;
}
/* [] */ 
/**
 * [i2c1_master_write I2C1主机模式 发送数据]
 * @param  dev_addr [从设备地址]
 * @param  data     [数据]
 * @param  len      [数据大小]
 * @return          []
 */
void i2c1_master_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len)
{
    /* 1. 总线是否忙碌 */
    while(I2C1->SR2 & 1 << 1);
    /* 2. 发送起始信号 */
    I2C1->CR1 |= 1 << 8;
    while(!(I2C1->SR1 & 1 << 0));
    /* 3. 发送从机地址(写) */
    I2C1->DR = (dev_addr&0xfe)|0;
    while(!(I2C1->SR1 & 1 << 1));
    uint8_t temp=I2C1->SR1;
    temp=I2C1->SR2;
    /* 4. 发送寄存器地址 */
    I2C1->DR = reg_addr;
    while(!(I2C1->SR1 & 1 << 2));
    /* 5. 发送数据 */
    for(int i = 0; i < len; i++) {   
        I2C1->DR = data[i];
        while(!(I2C1->SR1 & 1 << 2));
    }
    /* 6. 发送停止信号 */
    I2C1->CR1 |= 1 << 9;

}

/**
 * [i2c1_master_read I2C1主机模式 接收数据]
 * @param  dev_addr [从设备地址]
 * @param  data     [数据]
 * @param  len      [数据大小]
 * @return          []
 */
void i2c1_master_read(uint8_t dev_addr, uint8_t reg_addr,  uint8_t *data, uint16_t len)
{
    /* 1. 总线是否忙碌 */
    while(I2C1->SR2 & 1 << 1);
    /* 2. 发送起始信号 */
    I2C1->CR1 |= 1 << 8;
    while(!(I2C1->SR1 & 1 << 0));
    /* 3. 发送从机地址(写) */
    I2C1->DR = (dev_addr&0xfe)|0;
    while(!(I2C1->SR1 & 1 << 1));
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    /* 4. 发送寄存器地址 */
    I2C1->DR = reg_addr;
    while(!(I2C1->SR1 & 1 << 7));
    /* 6. 再次发送起始信号 */
    I2C1->CR1 |= 1 << 8;
    while(!(I2C1->SR1 & 1 << 0));
    /* 7. 发送从机地址(读) */
    I2C1->DR = (dev_addr&0xfe) | 1;
    while(!(I2C1->SR1 & 1 << 1));
    (void)I2C1->SR1;
    (void)I2C1->SR2;
    /* 8. 读取数据 */
    I2C1->CR1 |= 1 << 10; // 启用ACK
    for(int i = 0; i < len; i++) {
        while(!(I2C1->SR1 & 1 << 6));
        data[i] = I2C1->DR;
    }
    /* 9. 不应答 停止位 */
    I2C1->CR1 &= ~(1 << 10);
    I2C1->CR1 |= 1 << 9;

    while(!(I2C1->SR1 & 1 << 6));
    data[len - 1] = I2C1->DR;/* [*] */

}
