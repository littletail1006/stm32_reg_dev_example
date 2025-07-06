/*******************************************************************************
 * @file     usart.c
 * @brief    usart配置及相关操作代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "usart.h"
#include "stm32f103xe.h"

/**
 * [usart1_send 串口1发送1字符]
 * @param ch [字符]
 */
void usart1_send(uint8_t ch)
{
    USART1->SR;
    USART1->DR = ch;
    while(!(USART1->SR & (1 << 6)))
        ;
}

/**
 * [usart1_send_str 串口1发送字符串]
 * @param str [字符串]
 */
void usart1_send_str(uint8_t *str)
{
    while(*str != '\0') {
        usart1_send(*str);
        str++;
    }
}
/**
 * [usart1_tx_dma 串口1 DMA发送]
 * @param  buf  [发送数据]
 * @param  len  [长度]
 * @param  flag [阻塞标志 1阻塞 0不]
 * @return      [传输的数据个数]
 */
uint32_t usart1_tx_dma(uint8_t *buf, uint32_t len, uint8_t flag)
{

    DMA1_Channel4->CCR &= ~(1 << 0);            // 关闭DMA
    DMA1_Channel4->CMAR = (uint32_t) buf;       // 存储器地址
    DMA1_Channel4->CNDTR = len;                 // 传输数量大小
    DMA1_Channel4->CCR |= 1 << 0;               // 开启DMA
    if(flag) {                                  // 是否阻塞
        while(!(DMA1->ISR & 1 << 1)) {
        };
    } else {
        ;
    }
    return 0;
}

uint32_t usart1_rx_dma_int(uint8_t *buf, uint32_t len)
{
    DMA1_Channel5->CCR &= ~(1 << 0);            // 关闭DMA
    DMA1_Channel5->CMAR = (uint32_t) buf;       // 存储器地址
    DMA1_Channel5->CNDTR = len;                 // 传输数量大小
    DMA1_Channel5->CCR |= 1 << 0;               // 开启DMA

    return  0;
}

/**
 * [usart1_init USART1初始化]
 */
void usart1_init(void)
{
    /* 1、使能PA9 PA10 USART1时钟 */
    RCC->APB2ENR |= 1 << 2 | 1 << 14;
    /* 2、配置PA9 PA10引脚模式 */
    GPIOA->CRH &= ~(0xff << 4);
    GPIOA->CRH |= 11 << 4 | 4 << 8;        // TX 复用推挽 RX 浮空输入
    /* 3、配置波特率 */
    USART1->BRR |= 39 << 4 | 1;            // 115200
    /* 4、配置数据位、停止位、校验位 */
    USART1->CR1 &= ~(1 << 12 | 1 << 10);   // 8位数据位 无校验
    USART1->CR1 &= ~(3 << 12);             // 1位停止位
    /* 5、使能串口接收和发送 */
    USART1->CR1 |= 1 << 2 | 1 << 3;

#if 0
    /* 使能DMA发送 */
    USART1->CR3 |= 1 << 7;
#endif

#if 0
    /* 使能DMA接收 */
    USART1->CR3 |= 1 << 6;
#endif

#if 1
    /* 6、使能串口接收中断、空闲中断 */
    USART1->CR1 |= 1 << 5 | 1 << 4;
#endif

    /* 7、使能串口 */
    USART1->CR1 |= 1 << 13;
    /* 8、使能串口1中断 */
    NVIC->ISER[1] |= 1 << (USART1_IRQn & 0x1f);
#if 1
    /* 2、配置中断优先级 */
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_PRIORITYGROUP_2, 0, 1));
#endif
}
