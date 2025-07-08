/*******************************************************************************
 * @file     wdg.c
 * @brief    wdg
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "pwr.h"

/**
 * [pwr_enter_sleep_mode 进入睡眠模式]
 *  唤醒方式         通过任意中断/事件唤醒
 *  SLEEP NOW        该模式下唤醒后 正常工作 
 *  SLEEP ON EXTI    该模式下唤醒后 会再次进入SELLP 即主循环不工作 中断中工作
 */
void pwr_enter_sleep_mode(void) {
    /* 1 SLEEP NOW */ 
//    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
//    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
//    __WFI(); // __WFE 效果一样
    /* 2 SLEEP ON EXTI */ 
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    __WFI();  
}
/**
 * [pwr_enter_stop_mode 进入停止模式]
 *  唤醒方式         通过外部中断/事件唤醒
 *                   唤醒后 需要重新配置系统时钟及外设
 */
void pwr_enter_stop_mode(void) {
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;      // 使能PWR
    PWR->CR |= PWR_CR_CWUF;                 // 清除 WakeUp 标志
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;      // 设置为深度睡眠模式
    PWR->CR &= ~PWR_CR_PDDS;                // 确保是 Stop 而非 Standby
    PWR->CR |= PWR_CR_LPDS;                 // 低功耗调压器（可选）
    __WFI();                                // 等待中断唤醒
}
void pwr_stop_wakeup_usart(void) {
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
    USART1->CR1 &= ~(1 << 13);
    NVIC_DisableIRQ(USART1_IRQn);
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN     // GPIOB 时钟使能
                  | RCC_APB2ENR_AFIOEN;    // AFIO 时钟使能
    GPIOA->CRH &= ~(0xF << 8);             // PB10 清除控制位
    GPIOA->CRH |=  (0x4 << 8);             // 输入模式，浮空输入（0b0100）
    EXTI->IMR  |=  (1 << 10);   // 中断屏蔽寄存器：使能 EXTI10
    EXTI->FTSR |=  (1 << 10);   // 下降沿触发
    EXTI->RTSR &= ~(1 << 10);   // 禁止上升沿触发（可选）
    NVIC_EnableIRQ(EXTI15_10_IRQn); 
}
void pwr_enter_standby_mode(void) {
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_PDDS;      // 设置为 Standby
    PWR->CR |= PWR_CR_CWUF;      // 清除唤醒标志
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; 
    __WFI();                     // 进入待机
}

void pwr_standby_mode_wakeup_set(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_DBP;
    PWR->CSR |= PWR_CSR_EWUP;      // 启用 WKUP 引脚唤醒
    
    /* PA0的上升沿中断触发配置 */
}