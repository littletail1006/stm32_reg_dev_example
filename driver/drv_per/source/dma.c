/*******************************************************************************
 * @file     dma.c
 * @brief    dma配置及相关操作代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "dma.h"
#include "stm32f103xe.h"

#ifdef __GCC__
extern uint8_t buf1[1000], buf2[1000];
#else
uint8_t buf1[1000], buf2[1000];
#endif

void dma1_ch1_mem2mem_init(void)
{
    /* 1、使能DMA时钟 */
    RCC->AHBENR |= 1 << 0;
    /* 2、配置存储器、外设的地址 */
    DMA1_Channel1->CPAR = (uint32_t)&buf1[0]; // 外设地址
    DMA1_Channel1->CMAR = (uint32_t)&buf2[0]; // 存储器
    /* 3、配置传输数据大小和宽度、传输方向、传输模式、外设和存储器模式 */
    DMA1_Channel1->CCR &= ~(0xff << 0);
    DMA1_Channel1->CCR |= 1 << 14;  //传输模式 存储器到存储器
    DMA1_Channel1->CCR &= ~(3 << 10); //存储器数据宽度 8位 1字节
    DMA1_Channel1->CCR &= ~(3 << 8); //外设数据宽度 8位 1字节
    DMA1_Channel1->CCR |= 1 << 7;   //存储器地址递增
    DMA1_Channel1->CCR |= 1 << 6;   //外设地址递增
    DMA1_Channel1->CCR &= ~(1 << 5); //存储器到存储器模式 只能单次 不能循环
    DMA1_Channel1->CCR &= ~(1 << 4); //从外设读数据(buf1->外设 搬到 buf2 存储器)
    DMA1_Channel1->CNDTR = sizeof(buf1); //传输数量大小
    /* 4、设置通道优先级 */
    DMA1_Channel1->CCR |= 1 << 12;      // 中优先

#if 1
// 中断式 example12--------------------------------------------------------------
    DMA1_Channel1->CCR |= 1 << 1;   //使能传输完成中断
//    DMA1_Channel1->CCR|=1<<2;       //使能传输一半中断
//    DMA1_Channel1->CCR|=1<<3;       //使能传输错误中断
    /* 5、使能中断 */
    NVIC->ISER[0] |= 1 << (DMA1_Channel1_IRQn); //使能DMA1通道1中断
#endif
}

void dma1_ch4_mem2per_init(void)
{
    /* 1、使能DMA时钟 */
    RCC->AHBENR |= 1 << 0;
    /* 2、配置存储器、外设的地址 */
    DMA1_Channel4->CPAR = (uint32_t)&USART1->DR; // 外设地址    串口1数据寄存器
//    DMA1_Channel1->CMAR=(uint32_t)&buf2[0];    // 存储器
    /* 3、配置传输数据大小和宽度、传输方向、传输模式、外设和存储器模式 */
    DMA1_Channel4->CCR &= ~(0xff << 0);
    DMA1_Channel4->CCR &= (1 << 14); //传输模式 非存储器到存储器
    DMA1_Channel4->CCR &= ~(3 << 10); //存储器数据宽度 8位 1字节
    DMA1_Channel4->CCR &= ~(3 << 8); //外设数据宽度 8位 1字节
    DMA1_Channel4->CCR |= 1 << 7;   //存储器地址递增
    DMA1_Channel4->CCR &= ~(1 << 6); //外设地址不递增
    DMA1_Channel4->CCR &= ~(1 << 5); //单次传输 不循环
    DMA1_Channel4->CCR |= 1 << 4;   //从存储器读数据(存储器 -> USART1->DR)
//    DMA1_Channel1->CNDTR=sizeof(buf1);  //传输数量大小
    /* 4、设置通道优先级 */
    DMA1_Channel4->CCR |= 1 << 12;  // 中优先

#if 0
    DMA1_Channel1->CCR |= 1 << 1;   //使能传输完成中断
//    DMA1_Channel1->CCR|=1<<2;       //使能传输一半中断
//    DMA1_Channel1->CCR|=1<<3;       //使能传输错误中断
    /* 5、使能中断 */
    NVIC->ISER[0] |= 1 << (DMA1_Channel1_IRQn); //使能DMA1通道1中断
#endif
}

void dma1_ch5_per2mem_init(void)
{
    /* 1、使能DMA时钟 */
    RCC->AHBENR |= 1 << 0;
    /* 2、配置存储器、外设的地址 */
    DMA1_Channel5->CPAR = (uint32_t)&USART1->DR; // 外设地址    串口1数据寄存器
    /* 3、配置传输数据大小和宽度、传输方向、传输模式、外设和存储器模式 */
    DMA1_Channel5->CCR &= ~(0xff << 0);
    DMA1_Channel5->CCR &= 1 << 14;  //传输模式 非存储器到存储器
    DMA1_Channel5->CCR &= ~(3 << 10); //存储器数据宽度 8位 1字节
    DMA1_Channel5->CCR &= ~(3 << 8); //外设数据宽度   8位 1字节
    DMA1_Channel5->CCR |= 1 << 7;   //存储器地址递增
    DMA1_Channel5->CCR &= ~(1 << 6); //外设地址不递增
    DMA1_Channel5->CCR &= ~(1 << 5); //单次传输 不循环
    DMA1_Channel5->CCR &= ~(1 << 4); //从外设读数据( USART1->DR->存储器)
    /* 4、设置通道优先级 */
    DMA1_Channel5->CCR |= 2 << 12;  //高优先
    /* 5、使能传输完成中断 */
    DMA1_Channel5->CCR |= 1 << 1;   //使能传输完成中断
    /* 6、使能中断 */
    NVIC->ISER[0] |= 1 << (DMA1_Channel5_IRQn); //使能DMA1通道5中断
#if 1
    /* 2、配置中断优先级 */
    NVIC_SetPriority(DMA1_Channel5_IRQn, NVIC_EncodePriority(NVIC_PRIORITYGROUP_2, 1, 0));
#endif
}
