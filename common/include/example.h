/*******************************************************************************
 * @file     example.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __EXAMPLE_H
#define __EXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

// [include]————————————————————————————————————————————————————————————————————

// [define]—————————————————————————————————————————————————————————————————————
//#define example_01_enable
//#define example_02_enable
//#define example_03_enable
//#define example_04_enable
//#define example_05_enable
//#define example_06_enable
//#define example_07_enable
//#define example_08_enable
//#define example_09_enable
//#define example_10_enable
//#define example_11_enable
//#define example_12_enable
//#define example_13_enable
//#define example_14_enable
//#define example_15_enable
//#define example_16_enable
//#define example_17_enable
//#define example_18_enable
//#define example_19_enable
//#define example_20_enable
//#define example_21_enable
//#define example_22_enable
//#define example_23_enable
//#define example_24_enable
//#define example_25_enable
//#define example_26_enable
//#define example_27_enable
//#define example_28_enable
//#define example_29_enable
//#define example_30_enable
#define example_31_enable
// [function declaration]———————————————————————————————————————————————————————
extern void example_01_gpio_led(void);
extern void example_02_gpio_key(void);
extern void example_03_gpio_remap(void);
extern void example_04_gpio_bitband(void);
extern void example_05_exti_key(void);
extern void example_06_irq_priority(void);
extern void example_07_delay(void);
extern void example_08_usart_polltx_isrrx(void);
extern void example_09_usart_printf(void);
extern void example_10_usart_ringbuffer(void);
extern void example_11_dma_mem2mem_poll(void);
extern void example_12_dma_mem2mem_interrupt(void);
extern void example_13_usart_dma_tx_mem2per(void);
extern void example_14_usart_dma_rx_per2mem(void);
extern void example_15_usart_dma_idle_ringbuf(void);
extern void example_16_hw_i2c(void);
extern void example_17_sw_i2c(void);
extern void example_18_oled(void);
extern void example_19_tim_timing(void);
extern void example_20_tim_pwm(void);
extern void example_21_tim_oc(void);
extern void example_22_tim_ic(void);
extern void example_23_adc_poll_01(void);
extern void example_24_adc_poll_02(void);
extern void example_25_adc_poll_03(void);
extern void example_26_adc_int(void);
extern void example_27_wdg(void);
extern void example_28_rtc(void);
extern void example_29_pwr_sleep(void);
extern void example_30_pwr_stop(void);
extern void example_31_pwr_standby(void);
             
#ifdef __cplusplus
}
#endif

#endif
