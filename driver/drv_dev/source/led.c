/*******************************************************************************
 * @file     led.c
 * @brief    led配置及相关操作代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2024-01-02 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "led.h"


/**
 * [led_init LED初始化]
 */
void led_init(void)
{
    /* 1、使能GPIOB时钟 */
    RCC_APB2ENR |= 1 << 3;
    /* 2、配置PB5为推挽输出速度50MHZ */
    GPIOB_CRL &= ~(0xf << 20);   // 等价GPIOB_CRL&=0xFF0FFFFF;
    GPIOB_CRL |= 3 << 20;        // 等价GPIOB_CRL|=0x00300000;
    /* 3、设置PB5输出高电平即LED灯灭 */
    GPIOB_ODR |= 1 << 5;
//  GPIOB_BSRR|=1<<5;
}
/**
 * [led_on LED打开]
 */
void led_on(void)
{
    GPIOB_BSRR |= 1 << 21;  // 使用BSRR寄存器设置输出低
//     GPIOB_ODR|=1<<5;     // 使用ODR寄存器设置输出低
}
/**
 * [led_off LED关闭]
 */
void led_off(void)
{
    GPIOB_BSRR |= 1 << 5;
//     GPIOB_BRR|=1<<5;     // 使用BRR寄存器设置输出高
}
