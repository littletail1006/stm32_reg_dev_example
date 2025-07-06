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
#include "i2c_io.h"
#include "stm32f103xe.h"

#define I2C_DELAY()         I2C_Delay()

#define I2C_SCL_HIGH()    ( GPIOB->BSRR|=1<<6 )
#define I2C_SCL_LOW()     ( GPIOB->BRR|=1<<6  )
#define I2C_SDA_HIGH()    ( GPIOB->BSRR|=1<<7 )
#define I2C_SDA_LOW()     ( GPIOB->BRR|=1<<7  )
#define I2C_SDA_READ()    ( GPIOB->IDR&1<<7   )

/* 2、I2C起始信号/停止信号 */
static void I2C_Delay(void)
{
    uint8_t i;
    /* 100k 10us */
    for(i = 0; i < 10; i++);
}
void i2c_start(void)
{
    /* SCL高电平时 SDA由高变低 */          
    I2C_SDA_HIGH();
    I2C_SCL_HIGH();
    I2C_DELAY();
    I2C_SDA_LOW();
    I2C_DELAY();
    I2C_SCL_LOW();
    I2C_DELAY();
}
void i2c_stop(void)
{
    /* SCL高电平时，SDA由低变高 */
    I2C_SDA_LOW();
    I2C_SCL_HIGH();
    I2C_DELAY();
    I2C_SDA_HIGH();
}

void i2c_ack(void)
{
    I2C_SDA_LOW();	/* 驱动SDA = 0 */
    I2C_DELAY();
    I2C_SCL_HIGH();	/* 产生1个时钟 */
    I2C_DELAY();
    I2C_SCL_LOW();
    I2C_DELAY();
    I2C_SDA_HIGH();	/* 释放SDA总线 */
}
void i2c_nack(void)
{
    I2C_SDA_HIGH();	/* 驱动SDA = 1 */
    I2C_DELAY();
    I2C_SCL_HIGH();	/* 产生1个时钟 */
    I2C_DELAY();
    I2C_SCL_LOW();
    I2C_DELAY();
}
uint8_t i2c_wait_ack(void)
{
    uint8_t ret;

    I2C_SDA_HIGH();	/* 释放SDA总线 */
    I2C_DELAY();
    I2C_SCL_HIGH();	/* 驱动SCL = 1, 此时器件会返回ACK应答 */
    I2C_DELAY();
    if(I2C_SDA_READ()) {	/* 读取SDA线状态 */
        ret = 1;
    } else {
        ret = 0;
    }
    I2C_SCL_LOW();
    I2C_DELAY();
    return ret;
}
/* 4、写/读一个字节数据 */
void i2c_write_byte(uint8_t byte)
{
    uint8_t i;

    /* 先发送字节的高位bit7 */
    for(i = 0; i < 8; i++) {
        if(byte & 0x80) {
            I2C_SDA_HIGH();
        } else {
            I2C_SDA_LOW();
        }
        I2C_DELAY();
        I2C_SCL_HIGH();
        I2C_DELAY();
        I2C_SCL_LOW();
        if(i == 7) {
            I2C_SDA_HIGH(); // 释放总线
        }
        byte <<= 1;	/* 左移一个bit */
        I2C_DELAY();
    }
}
uint8_t i2c_read_byte(void)
{
    uint8_t i;
    uint8_t value;

    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for(i = 0; i < 8; i++) {
        value <<= 1;
        I2C_SCL_HIGH();
        I2C_DELAY();
        if(I2C_SDA_READ()) {
            value++;
        }
        I2C_SCL_LOW();
        I2C_DELAY();
    }
    return value;
}

/*
 * [i2c1_init I2C初始化]
 */
void sw_i2c_init(void)
{
    /*  1. 使能时钟————————————————————————————————————————————————————————————*/
    RCC->APB2ENR |= 1 << 3;     // 使能GPIOB时钟
    /*  2. 配置I2C IO口———————————————————————————————————————————————————————*/
    GPIOB->CRL &= 0x00FFFFFF;  // PB6 7通用开漏输出
    GPIOB->CRL |= 0x77000000;  // PB6 7通用开漏输出

}
/**
 * [sw_i2c_write_byte I2C1主机模式 写单字节]
 * @param  dev_addr [从设备地址]
 * @param  reg_addr [写的地址]
 * @param  data     [数据]
 * @return          []
 */
void sw_i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, const uint8_t data)
{
    /* 1. 发送起始信号 */
    i2c_start();
    /* 2. 发送从机地址(写) */
    i2c_write_byte(dev_addr|0);
    i2c_wait_ack();
    /* 3. 发送寄存器地址 */
    i2c_write_byte(reg_addr);
    i2c_wait_ack();
    /* 4. 发送数据 */
    i2c_write_byte(data);
    i2c_wait_ack();
    /* 5. 发送停止信号 */
    i2c_stop();
}

/**
 * [sw_i2c_read I2C1主机模式 读数据]
 * @param  dev_addr [从设备地址]
 * @param  reg_addr [读的地址]
 * @param  data     [数据]
 * @return          []
 */
uint8_t sw_i2c_read_byte(uint8_t dev_addr, uint8_t reg_addr)
{
    uint8_t data;

    /* 1. 发送起始信号 */
    i2c_start();
    /* 2. 发送从机地址(写) */
    i2c_write_byte(dev_addr|0);
    i2c_wait_ack();
    /* 3. 发送寄存器地址 */
    i2c_write_byte(reg_addr);
    i2c_wait_ack();
    /* 6. 再次发送起始信号 */
    i2c_start();
    /* 7. 发送从机地址(读) */
    i2c_write_byte(dev_addr|1);
    i2c_wait_ack();
    /* 9. 读取数据 */
    data = i2c_read_byte();
    i2c_nack();
    /* 5. 发送停止信号 */
    i2c_stop();

    return data;
}
/**
 * [sw_i2c_write I2C1主机模式 发送数据]
 * @param  dev_addr [从设备地址]
 * @param  data     [数据]
 * @param  len      [数据大小]
 * @return          []
 */
void sw_i2c_write(uint8_t dev_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len)
{
    /* 1. 发送起始信号 */
    i2c_start();
    /* 2. 发送从机地址(写) */
    i2c_write_byte(dev_addr|0);
    /* 3. 发送寄存器地址 */
    i2c_wait_ack();
    i2c_write_byte(reg_addr);
    /* 4. 发送数据 */
    i2c_wait_ack();
    /* 5. 发送数据 */
    for(int i = 0; i < len; i++) {
        i2c_write_byte(data[i]);
        i2c_wait_ack();
    }
    /* 5. 发送停止信号 */
    i2c_stop();
}

/**
 * [sw_i2c_read I2C1主机模式 接收数据]
 * @param  dev_addr [从设备地址]
 * @param  data     [数据]
 * @param  len      [数据大小]
 * @return          []
 */
void sw_i2c_read(uint8_t dev_addr, uint8_t reg_addr,  uint8_t *data, uint16_t len)
{
    /* 1. 发送起始信号 */
    i2c_start();
    /* 2. 发送从机地址(写) */
    i2c_write_byte(dev_addr|0);
    i2c_wait_ack();
    /* 3. 发送寄存器地址 */
    i2c_write_byte(reg_addr);
    i2c_wait_ack();
    /* 6. 再次发送起始信号 */
    i2c_start();
    /* 7. 发送从机地址(读) */
    i2c_write_byte(dev_addr|1);
    i2c_wait_ack();
    /* 8. 读取数据 */
    for(int i = 0; i < len; i++) {
        data[i] = i2c_read_byte();
        i2c_ack();
    }
    /* 8. 不应答 停止位 */
    i2c_nack();
    data[len - 1] = i2c_read_byte();
    i2c_stop();  
}
