/*******************************************************************************
 * @file     adc.c
 * @brief    tim驱动代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "adc.h"


// 定义多通道（通道1/2/3）
#define ADC_CH_CNT  3
uint16_t adc_value[ADC_CH_CNT];  // 存储转换结果
uint32_t adc_value1[ADC_CH_CNT];  // 存储转换结果
/**
 * [adc1_init adc1初始化]
 */
void adc1_init(void)
{
    /*1. 使能时钟——————————————————————————————————————————————————————————————*/
    RCC->APB2ENR |= 1 << 9 | 1 << 2;          // 使能ADC1和GPIOA时钟
    RCC->CFGR |= 2 << 14;                     // 设置ADC时钟12M 分配系数6 72/6=12
    /*2. 配置引脚——————————————————————————————————————————————————————————————*/
    GPIOA->CRL &= ~(0xFFF << 4);                // 清除PA1配置
    GPIOA->CRL |= (0x0 << 4);                 // 模拟输入模式
    /*3. 配置ADC——————————————————————————————————————————————————————————————*/
    // [3.1 ADC基本配置]
    ADC1->CR1 = 0x00000000;                   // 独立模式，12位分辨率
    ADC1->CR2 = 0x00000000;
    ADC1->CR2 |= (1 << 1);                    // 连续转换模式
    #if 0 // [单通道] 规则通道
    // [3.2 设置采样时间 通道1]
    ADC1->SMPR2 |= (7 << 3);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    // [3.3 规则序列配置 单通道]
    ADC1->SQR1 = 0000<<20;                    // 1个转换
    ADC1->SQR3 |= (1 << 0);                   // 第1个转换：通道1
    #endif
    #if 1 // [单通道] 注入通道
    // [3.2 设置采样时间 通道1]
    ADC1->SMPR2 |= (7 << 3);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    // [3.3 规则序列配置 单通道]
    ADC1->JSQR = 00<<20;                        // 1个转换
    ADC1->JSQR |= (1 << 15);                    // 第4个转换：通道1
    ADC1->CR1 |= 1<<10;                         // 自动注入
    #endif
    #if 0 // [多通道] 规则通道
    ADC1->CR1 |= ADC_CR1_SCAN;                // 扫描模式
    // [3.2 设置采样时间 通道1]
    ADC1->SMPR2 |= (7 << 3);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    ADC1->SMPR2 |= (7 << 6);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    ADC1->SMPR2 |= (7 << 9);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    // [3.3 规则序列配置 单通道]
    ADC1->SQR1 = (ADC_CH_CNT-1)<<20;          // 3个转换
    ADC1->SQR3 |= (1 << 0);                   // 第1个转换：通道1
    ADC1->SQR3 |= (2 << 5);                   // 第2个转换：通道2
    ADC1->SQR3 |= (3 << 10);                  // 第3个转换：通道3
    #endif
    #if 0 // [多通道] 注入通道
    ADC1->CR1 |= 1<<10;                        // 自动注入
    ADC1->CR1 |= ADC_CR1_SCAN;                // 扫描模式
    // [3.2 设置采样时间 通道1]
    ADC1->SMPR2 |= (7 << 3);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    ADC1->SMPR2 |= (7 << 6);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    ADC1->SMPR2 |= (7 << 9);                  // 239.5周期采样（通道1在SMPR2[3:5]）
    // [3.3 注入序列配置 单通道]
    ADC1->JSQR = (ADC_CH_CNT-1)<<20;          // 3个转换
    ADC1->JSQR |= (1 << 15);                  // 第4个转换：通道1
    ADC1->JSQR |= (2 << 10);                  // 第3个转换：通道2
    ADC1->JSQR |= (3 << 5);                   // 第2个转换：通道3
    #endif
    
    ADC1->CR2 |= (1 << 0);                    // 开启ADC
    // [3.4 校准]
    ADC1->CR2 |= (1 << 3);                    // 初始化校准
    while(ADC1->CR2 & (1 << 3));              // 等待校准完成
    ADC1->CR2 |= (1 << 2);                    // 开始校准
    while(ADC1->CR2 & (1 << 2));              // 等待校准完成
    
    #if 1  // 使能EOC中断
    ADC1->CR1 |= 1 << 5;                       // 使能EOC中断
    ADC1->CR1 |= 1 << 7;                       // 使能jEOC中断
    NVIC->ISER[0] |= 1 << (ADC1_2_IRQn);
    #endif
    ADC1->CR2 |= (1 << 0);                    // 启动转换
}
/**
 * [adc1_start_read 开启一次转换并获取数据]
 * @return     [采集到的AD值]
 */
uint16_t adc1_start_read(void)
{
    #if 1
    while(!(ADC1->SR & (1 << 1)));            // 等待EOC标志
    return ADC1->DR;                          // 返回12位数据
    #endif
//    while(!(ADC1->SR & (1 << 2)));             // JEOC 
//    return ADC1->JDR1;
}

void ADC1_2_IRQHandler(void)
{
    if(ADC1->SR & (1<<1))    //eoc
    {
         ;
    }
    if(ADC1->SR & (1<<2))   //jeoc
    {
         ;
    }
    ADC1->SR =0;
}


/**
 * [adc1_dma_init tim1初始化]
 */
void adc1_dma_init(void)
{
    // 1. 开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;
    RCC->AHBENR |= 1 << 0;
    // 2. 配置GPIO为模拟输入（PA1/PA2/PA3）
    GPIOA->CRL &= ~(0xFFF << 4);  // 清除PA1/PA2/PA3配置

    // 3. ADC基础配置
    ADC1->CR1 = 0x00;              // 独立模式，12位分辨率
    ADC1->CR2 = (1 << 1) |         // 连续转换模式
                (1 << 8) |         // DMA使能
                (1 << 0);          // 开启ADC
    // 扫描模式
    ADC1->CR1 |= ADC_CR1_SCAN;

    // 4. 采样时间配置（所有通道239.5周期）
    ADC1->SMPR2 = (7 << 3) | (7 << 6) | (7 << 9);  // 通道1/2/3
    #if 0
    // 5. 规则序列配置（3个转换）
    ADC1->SQR1 = (ADC_CH_CNT-1) << 20;      // 总转换数=3
    ADC1->SQR3 = (1 << 0) | (2 << 5) | (3 << 10);  // 顺序：CH1→CH2→CH3
        // 6. 启用DMA（需先配置DMA控制器）
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;    // ADC数据寄存器地址
    DMA1_Channel1->CMAR = (uint32_t)adc_value;    // 存储数组地址
    DMA1_Channel1->CNDTR = ADC_CH_CNT;            // 传输数据量
    DMA1_Channel1->CCR = (1 << 7) | (1 << 5);     // 循环模式，16位传输 目的址自增
    DMA1_Channel1->CCR |= 1<<8;
    DMA1_Channel1->CCR |= 1<<10;
    #endif
    #if 1
    // 5. 注入序列配置（3个转换）
    ADC1->CR1 |= 1<<10;                        // 自动注入
    ADC1->JSQR = (ADC_CH_CNT-1)<<20;          // 3个转换
    ADC1->JSQR |= (1 << 5);                   // 第2个转换：通道1
    ADC1->JSQR |= (2 << 10);                  // 第3个转换：通道2
    ADC1->JSQR |= (3 << 15);                   // 第4个转换：通道3
    // 6. 启用DMA（需先配置DMA控制器）
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->JDR1;    // ADC数据寄存器地址
    DMA1_Channel1->CMAR = (uint32_t)adc_value1;     // 存储数组地址
    DMA1_Channel1->CNDTR = ADC_CH_CNT;              // 传输数据量
    DMA1_Channel1->CCR = (1 << 7) | (1 << 5) | (1 << 6); // 循环模式，32位传输 目外设和的址自增
    DMA1_Channel1->CCR |= 2<<8;            
    DMA1_Channel1->CCR |= 2<<10;
    #endif

    
    
    DMA1_Channel1->CCR |= (1 << 0);
    // 7. 校准并启动
    ADC1->CR2 |= (1 << 3);          // 初始化校准
    while(ADC1->CR2 & (1 << 3));
    ADC1->CR2 |= (1 << 2);          // 开始校准
    while(ADC1->CR2 & (1 << 2));
    
//    ADC1->CR2 |= (1 << 22);         // 启动转换
    ADC1->CR2 |= (1 << 0);                    // 启动转换
}
