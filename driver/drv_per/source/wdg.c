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
#include "wdg.h"

/**
 * [iwdg_init 窗口看门狗初始化]
 * @param pre [预分频系数]
 *            低3位有效 0-7
 *            | 0 0 0 |  4分频 | 0 0 1 |  8分频 | 0 1 0 |  16分频 |
 *            | 0 1 1 | 32分频 | 1 0 0 | 64分频 | 1 0 1 | 128分频 |
 *            | 1 1 0 |256分频 | 1 1 1 |256分频 | 
 * @param rlr [重装在值]
 *            12位 最大值4095
 * 
 *            时间计算：(4 * 2^PR) * RLR / LSI频率
 *            eg 64分频 重装在值500 
 *               (4*2^4)*500 / 40000 = 0.8秒
 */
void iwdg_init(uint8_t pre,uint16_t rlr)
{
    /* 1. 使能时钟 LSI */
//    RCC->CSR |= RCC_CSR_LSION; 
//    while((RCC->CSR & RCC_CSR_LSIRDY) == 0);  

    /* 2. 解锁IWDG_PR和IWDG_RLR寄存器（写入0x5555到IWDG_KR）*/
    IWDG->KR = 0x5555;
    
    /* 3. 设置预分频系数 */
    IWDG->PR = pre;
    
    /* 4. 设置重装载值 */
    IWDG->RLR = rlr;
    
    /* 5. 喂狗（写入0xAAAA到IWDG_KR）*/
    IWDG->KR = 0xAAAA;
    
    /* 6. 启动独立看门狗 */
    IWDG->KR = 0xCCCC;
}

void iwdg_feed(void)
{
    IWDG->KR = 0xAAAA; 
}
/**
 * [wwdg_init 独立看门狗]
 * @param pre [预分频] 0-3   2位有效
 *                     | 0 0 | PLCK1/4096/1  | 0 1 | PLCK1/4096/2
 *                     | 1 0 | PLCK1/4096/4  | 1 1 | PLCK1/4096/8
 * @param wr  [窗口值] 0-127 7位有效
 * @param tr  [计数值] 64~127 0x40-0x7f

 *            时间计算：(计数值-0x40+1) x WWDG 时钟频率(PCLK1/4096/(2^WDGTB)) 
 *            eg 8分频 计数值0x7F 窗口值0x5F   不能早于0x5f对应时间 不能晚于0x7f时间
 *               (0x7f-0x40 + 1) / (36000000/4096/8) = 57.46ms
 *               (0x7f-0x5f + 1) / (36000000/4096/8) = 29.184ms
 */
void wwdg_init(uint8_t pre, uint8_t wr, uint8_t tr)
{
    /* 1. 使能WWDG时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_WWDGEN;
    
    /* 2. 设置预分频系数 */
    WWDG->CFR &= ~(3<<7);      // 清除原有预分频设置
    WWDG->CFR |= (pre << 7);   // 设置WDGTB[8:7]
    
    /* 3. 设置窗口值（必须小于计数器值）*/
    WWDG->CFR &= ~0x7F;        // 清除原有窗口值
    WWDG->CFR |= (wr & 0x7F);  // 设置窗口值（低7位有效）
    
    /* 4. 设置计数器值并启动WWDG */
    WWDG->CR = 1<<7 | (tr & 0x7F);  // 计数器值必须大于窗口值
}
void wwdg_feed(void)
{
    WWDG->CR = 0x7F; // 需要在窗口内 (窗口值~计数器值)
}
