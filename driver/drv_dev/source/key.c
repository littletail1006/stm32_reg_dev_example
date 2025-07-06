/*******************************************************************************
 * @file     key.c
 * @brief    key配置及相关操作代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2024-01-04 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/

// [include]————————————————————————————————————————————————————————————————————
#include "key.h"


/**
 * [key_init KEY初始化]
 */
void key_init(void)
{
    /* 1、使能GPIOC的时钟 */
    RCC_APB2ENR |= 1 << 4;
    /* 2、配置PC13为上拉输入模式 */
    GPIOC_CRH &= ~(0xf << 20);
    GPIOC_CRH |= 0x8 << 20;
    /* 3、设置默认为高电平 */
    GPIOC_BSRR |= 1 << 13;

    /* example_06加入 */
    /* 2、配置PC14为上拉输入模式 */
    GPIOC_CRH &= ~(0xf << 24);
    GPIOC_CRH |= 0x8 << 24;
    /* 3、设置默认为高电平 */
    GPIOC_BSRR |= 1 << 14;
}
/**
 * [key_scan 按键扫描]
 */
uint8_t key_scan(void)
{
    if((GPIOC_IDR & (1 << 13)) == 0) {
        for(int i = 0; i < 120000; i++) ;
        if((GPIOC_IDR & (1 << 13)) == 0)
            return 1;
        else
            return 0;
    } else
        return 0;
}
