/*******************************************************************************
 * @file     rtc.c
 * @brief    rtc驱动代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 *******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include "rtc.h"
#include <time.h>
/**
 * [rtc_init RTC初始化]
 */
void rtc_init(void)
{
    /* 1. 使能 PWR 和 BKP 模块的时钟，并解锁备份区域 */  
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;    // 开启 PWR 时钟
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;    // 开启 BKP 时钟
    PWR->CR |= PWR_CR_DBP;                // 允许访问备份域

    /* 第一次初始化 */
    if (BKP->DR1 != 0x7777) {
        /* 2. 使能时钟 LSI/LSE */
//        RCC->CSR |= RCC_CSR_LSION; 
//        while((RCC->CSR & RCC_CSR_LSIRDY) == 0);
        RCC->BDCR |= RCC_BDCR_LSEON;
        while (!(RCC->BDCR & RCC_BDCR_LSERDY)); 

        /* 3. 选择 RTC 时钟源并启用 RTC）*/
//        RCC->BDCR |= RCC_BDCR_RTCSEL_LSI;     // 选择 LSI 作为 RTC 时钟源
        RCC->BDCR |= RCC_BDCR_RTCSEL_LSE;     // 选择 LSE 作为 RTC 时钟源
        RCC->BDCR |= RCC_BDCR_RTCEN;          // 使能 RTC    
        
        /* 4. 等待 RTC 寄存器同步 */
        RTC->CRL &= ~(RTC_CRL_RSF);           // 清除 RSF 同步标志
        while(!(RTC->CRL & RTC_CRL_RSF));     // 等待同步完成
        
        /* 5. 进入配置模式 设置预分频 */
        RTC->CRL |= RTC_CRL_CNF;              // 进入配置模式
        RTC->PRLH = 0x0000;                   // 预分频高字节
//        RTC->PRLL = 40000-1;                  // 40000Hz/ (39999+1) = 1秒
        RTC->PRLL = 0X7FFF;                   // 32768Hz/  (32677+1) = 1秒
        RTC->CRL &= ~(RTC_CRL_CNF);           // 退出配置模式
        
        /* 6. 等待OK */
        while(!(RTC->CRL & RTC_CRL_RTOFF));   // 等待写操作完成

        date_t now=DEFAULT_DATE;
        rtc_date_set(&now);                  // 日期方式设置日期时间
        
        BKP->DR1 = 0x7777;                    // 向备份寄存器写入一个值 
    } else  /* 已初始化过 */
    {
//        RCC->CSR |= RCC_CSR_LSION; 
//        while((RCC->CSR & RCC_CSR_LSIRDY) == 0);
        while(!(RTC->CRL & RTC_CRL_RSF));      // 等待同步完成
        while(!(RTC->CRL & RTC_CRL_RTOFF));    // 等待写操作完成
    }
    /* 开启中断 */
    RTC->CRH |= RTC_CRH_SECIE | RTC_CRH_ALRIE; // 秒和闹钟中断使能
    NVIC_EnableIRQ(RTC_IRQn);    
}

void rtc_time_set(uint32_t sec)
{
    RTC->CRL |= RTC_CRL_CNF;               // 进入配置模式

    RTC->CNTH = sec >> 16;;                // 高16位
    RTC->CNTL = sec & 0xFFFF;              // 低16位

    RTC->CRL &= ~(RTC_CRL_CNF);            // 退出配置模式

    while (!(RTC->CRL & RTC_CRL_RTOFF));   // 等待写完成
}

uint32_t rtc_time_get(void)
{
     return ((uint32_t)RTC->CNTH << 16) | RTC->CNTL;
}

void timestamp_to_calendar(uint32_t timestamp, struct tm *clalendar)
{
    time_t rtc_seconds = rtc_time_get();
    
    struct tm *timeinfo = localtime(&rtc_seconds);

}

/******************************************************************************/
// 判断闰年函数
static uint8_t is_leap_year(uint16_t year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

static const uint8_t days_in_month_table[12] = {
    31,28,31,30,31,30,31,31,30,31,30,31
};

//秒数 → 日期时间（timestamp → date）
void rtc_seconds_to_date(uint32_t seconds, date_t *date) {
    uint32_t days = seconds / 86400;
    uint32_t remaining = seconds % 86400;

    // ==== 时分秒 ====
    date->hour   = remaining / 3600;
    remaining   %= 3600;
    date->minute = remaining / 60;
    date->second = remaining % 60;

    // ==== 年 ====
    date->year = 1970;
    while (1) {
        uint16_t days_in_year = is_leap_year(date->year) ? 366 : 365;
        if (days >= days_in_year) {
            days -= days_in_year;
            date->year++;
        } else {
            break;
        }
    }

    // ==== 月 ====
    date->month = 1;
    while (1) {
        uint8_t dim = days_in_month_table[date->month - 1];
        if (date->month == 2 && is_leap_year(date->year)) dim++; // 补2月闰年
        if (days >= dim) {
            days -= dim;
            date->month++;
        } else {
            break;
        }
    }

    // ==== 日 ====
    date->day = days + 1;
}

//日期时间 → 秒数（date → timestamp）
uint32_t rtc_date_to_seconds(const date_t *date) {
    uint32_t seconds = 0;

    // 年累加
    for (uint16_t y = 1970; y < date->year; y++) {
        seconds += is_leap_year(y) ? 366 * 86400 : 365 * 86400;
    }

    // 月累加
    for (uint8_t m = 1; m < date->month; m++) {
        uint8_t dim = days_in_month_table[m - 1];
        if (m == 2 && is_leap_year(date->year)) dim++;
        seconds += dim * 86400;
    }

    // 日累加
    seconds += (date->day - 1) * 86400;

    // 时分秒
    seconds += date->hour * 3600 + date->minute * 60 + date->second;

    return seconds;
}

void rtc_date_set(date_t *date)
{
    uint32_t ts = rtc_date_to_seconds(date);

    rtc_time_set(ts);

}

void rtc_date_get(date_t *date)
{
    uint32_t cur_s = rtc_time_get();
    
    rtc_seconds_to_date(cur_s, date);
}

void rtc_alarm_time_set(uint32_t alarm_s)
{
    RTC->CRL |= RTC_CRL_CNF;             // 进入配置模式

    RTC->ALRH = (alarm_s >> 16) & 0xFFFF;
    RTC->ALRL = alarm_s & 0xFFFF;

    RTC->CRL &= ~RTC_CRL_CNF;            // 退出配置模式

    while (!(RTC->CRL & RTC_CRL_RTOFF)); // 等待写完成
}
void rtc_alarm_date_set(date_t *date)
{
    uint32_t ts = rtc_date_to_seconds(date);
    
    rtc_alarm_time_set(ts);
}


void (*sec_handle)(void);
void (*alarm_handle)(void);

void rtc_int_callback_set(enum CB_TYPE type,void (*pfun_cb)(void))
{
   if(pfun_cb==NULL)
        return ;
   if(type==SEC_HANDLE)         sec_handle=pfun_cb; 
   else if(type==ALARM_HANLDE)  alarm_handle=pfun_cb; 
}

void RTC_IRQHandler(void) {
    /* 秒中断 */
    if (RTC->CRL & RTC_CRL_SECF) {
        RTC->CRL &= ~(RTC_CRL_SECF); // 清除秒中断标志
        // 处理代码
        sec_handle();
    }
    /* 闹钟中断 */
    if (RTC->CRL & RTC_CRL_ALRF) {
        RTC->CRL &= ~(RTC_CRL_ALRF); // 清除秒中断标志
        // 处理代码
        alarm_handle();
    }
}
