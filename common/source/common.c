/*******************************************************************************
 * @file     example.c
 * @brief    实验的应用逻辑程序相关代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V1.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "common.h"
#include "usart.h"
#include "mini-printf.h"


// [define]—————————————————————————————————————————————————————————————————————
#define    DEM_CR_TRCENA       (1<<24)
#define    DWT_CR_CYCCNTENA    (1<<0)

#if 0
char printf_buf[200]={0};
int my_printf(const char *fmt, ...)
{
    int ret;

    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(printf_buf, sizeof(printf_buf)-1, fmt, va);

    usart1_send_str((uint8_t*)printf_buf);

    va_end(va);

    return ret;
}
#endif

#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#include <stdio.h>

#endif

PUTCHAR_PROTOTYPE
{
    usart1_send(ch);

    return ch;
}

/**
 * [delay_us us延时]
 * @param us [微秒 范围0-59652 DWT下]
 *                 范围0-1864134 SYSTICK下
 *            dwt     32位计数器 (0xffffffff-1)/(72000000/1000000)
 *            systick 24位计数器 (0xffffff-1)/(9000000/1000000)
 */
void delay_us(uint32_t us)
{
#if (REALIZE_TYPE==USE_SYSTICK_IRQ)
    ；
#elif  (REALIZE_TYPE==USE_DWT)

    uint32_t cnt, delay_cnt;
    uint32_t start;

    start = (uint32_t)DWT->CYCCNT;
    cnt = 0;
    delay_cnt = us * (SYSCLK / 1000000);

    while(cnt < delay_cnt) {
        cnt = (uint32_t) DWT->CYCCNT - start;
    }

#elif (REALIZE_TYPE==USE_SOFTWARE)

    for(int i = 0; i < 10*us; i++) ;            // 具体i值需要测试

#elif  (REALIZE_TYPE==USE_SYSTICK)

    SysTick->VAL = 0;                        // 设置计数当前值
    SysTick->LOAD = 9 * us - 1;              // 重装载计数值
    SysTick->CTRL |= 1 << 0;                 // 时钟来源HCLK/8(9M)，打开定时器
    while(!(SysTick->CTRL & (1 << 16)));     // 等待计数到0
    SysTick->CTRL &= ~(1 << 0);              // 关闭定时器

#endif

}
/**
 * [delay_ms ms延时]
 * @param ms [毫秒 范围0-59652 DWT下]
 *                 范围0-1864 SYSTICK下
 *            dwt     32位计数器 (0xffffffff-1)/(72000000/1000)
 *            systick 24位计数器 (0xffffff-1)/(9000000/1000)
 */
void delay_ms(uint32_t ms)
{
#if (REALIZE_TYPE==USE_SYSTICK_IRQ)
    ；
#elif  (REALIZE_TYPE==USE_DWT)

    uint32_t cnt, delay_cnt;
    uint32_t start;

    start = (uint32_t)DWT->CYCCNT;
    cnt = 0;
    delay_cnt = ms * (SYSCLK / 1000);

    while(cnt < delay_cnt) {
        cnt = (uint32_t)DWT->CYCCNT - start;
    }


#elif (REALIZE_TYPE==USE_SOFTWARE)
    for(int i = 0; i < 10000*ms; i++) ; // 具体i值需要测试

#elif  (REALIZE_TYPE==USE_SYSTICK)

    SysTick->VAL = 0;
    SysTick->LOAD = 9000 * ms - 1;
    SysTick->CTRL |= 1 << 0;
    while(!(SysTick->CTRL & (1 << 16)));
    SysTick->CTRL &= ~(1 << 0);

#endif

}
/**
 * [delay_init 初始化delay延时 ]
 */
void  delay_init(void)
{
#if (REALIZE_TYPE==USE_SYSTICK_IRQ)

#elif  (REALIZE_TYPE==USE_DWT)

    CoreDebug->DEMCR |= (uint32_t)DEM_CR_TRCENA;
    DWT->CYCCNT = (uint32_t)0UL;
    DWT->CTRL |= (uint32_t)DWT_CR_CYCCNTENA;

#endif
}

void systick_init(uint32_t ms)
{
    SysTick->VAL = 0;
    SysTick->LOAD = 9000 * ms - 1;
    SysTick->CTRL |=1<<1;
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_PRIORITYGROUP_2, 1, 2));
}

/**
 * [stm32_systemclock_init 系统时钟初始化为72MHZ]
 */
void systemclock_init(void)
{
    uint8_t PLL_OK;
    /* 1、开启HSE外部高速时钟 */
    RCC->CR |= 1 << 16;
    /* 2、检测HSE是否开启成功 */
    while(!(RCC->CR & (1 << 17)));
    /* 3、开启预取缓冲并设置FLASH访问周期为2个等待周期 */
    FLASH->ACR |= 2 << 0 | 1 << 4;
    /* 4、设置APB1外设总线时钟 36MHZ */
    RCC->CFGR |= 4 << 8;
    /* 5、设置HSE为PLL时钟源 */
    RCC->CFGR |= 1 << 16;
    /* 6、设置PLL倍频输出 */
    RCC->CFGR |= (PLL - 2) << 18;
    /* 7、开启PLL */
    RCC->CR |= 1 << 24;
    /* 8、等待PLL就绪 */
    while(!(RCC->CR & (1 << 25)));
    /* 9、设置系统时钟为PLL输出时钟 */
    RCC->CFGR |= 2 << 0;
    /* 10、等待PLL输出时钟作为系统时钟成功 */
    do {
        PLL_OK = RCC->CFGR & 0X0C;
    } while(PLL_OK != 0X08);

}














