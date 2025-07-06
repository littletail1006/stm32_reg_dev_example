/*******************************************************************************
 * @file     common.h
 * @brief    header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2024-01-19 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
*******************************************************************************/
#ifndef __COMMON_H
#define __COMMON_H


#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f103xe.h"



/* 延时函数实现方式 */
#define    REALIZE_TYPE      USE_SYSTICK

#define    USE_SYSTICK       1  // 使用systick定时器
#define    USE_SYSTICK_IRQ   2  // 使用systick中断
#define    USE_SOFTWARE      3  // 使用软件
#define    USE_DWT           4  // 使用DWT



#define HSE     8000000UL
#define SYSCLK 72000000UL
#define PLL    (SYSCLK/HSE)

#define BITBAND(addr, bitnum) \
              ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)          *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_ADDR    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_ADDR    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_ADDR    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_ADDR    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_ADDR    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_ADDR    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_ADDR    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_ADDR    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_ADDR    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_ADDR    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_ADDR    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_ADDR    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_ADDR    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_ADDR    (GPIOG_BASE+8) //0x40011E08 
 

#define PA_OUT(n)   BIT_ADDR(GPIOA_ODR_ADDR,n)  //输出 
#define PA_IN(n)    BIT_ADDR(GPIOA_IDR_ADDR,n)  //输入 

#define PB_OUT(n)   BIT_ADDR(GPIOB_ODR_ADDR,n)  //输出 
#define PB_IN(n)    BIT_ADDR(GPIOB_IDR_ADDR,n)  //输入 

#define PC_OUT(n)   BIT_ADDR(GPIOC_ODR_ADDR,n)  //输出 
#define PC_IN(n)    BIT_ADDR(GPIOC_IDR_ADDR,n)  //输入 

#define PD_OUT(n)   BIT_ADDR(GPIOD_ODR_ADDR,n)  //输出 
#define PD_IN(n)    BIT_ADDR(GPIOD_IDR_ADDR,n)  //输入 

#define PE_OUT(n)   BIT_ADDR(GPIOE_ODR_ADDR,n)  //输出 
#define PE_IN(n)    BIT_ADDR(GPIOE_IDR_ADDR,n)  //输入

#define PF_OUT(n)   BIT_ADDR(GPIOF_ODR_ADDR,n)  //输出 
#define PF_IN(n)    BIT_ADDR(GPIOF_IDR_ADDR,n)  //输入

#define PG_OUT(n)   BIT_ADDR(GPIOG_ODR_ADDR,n)  //输出 
#define PG_IN(n)    BIT_ADDR(GPIOG_IDR_ADDR,n)  //输入

#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */

//#define printf my_printf

//extern int my_printf(const char *fmt, ...);
extern void delay_ms(uint32_t ms);
extern void delay_us(uint32_t ns);
extern void delay_init(void);
extern void systemclock_init(void);
extern void systick_init(uint32_t ms);
#ifdef __cplusplus
}
#endif

#endif











