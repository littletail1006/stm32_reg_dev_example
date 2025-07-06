/*******************************************************************************
 * @file     example.c
 * @brief    实验的应用逻辑程序相关代码
 * @history
 * Date       Version Author    description
 * ========== ======= ========= ================================================
 * 2025-05-05 V0.0    Xiaoyibar Create
 *
 * @Copyright Xiaoyibar all right reserved
 ******************************************************************************/
// [include]————————————————————————————————————————————————————————————————————
#include <stdio.h>
#include "example.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "lwrb.h"
#include "dma.h"
#include "i2c.h"
#include "i2c_io.h"
#include "oled.h"
#include "tim.h"
#include "adc.h"
#include "wdg.h"
#include "rtc.h"

#ifdef example_28_enable

date_t date;
    
void sec_func()
{
   rtc_date_get(&date);
   printf("Date Time:[%04d-%02d-%02d %02d:%02d:%02d]\n",date.year,date.month,date.day, \
                                                 date.hour, date.minute, date.second);
}
void alarm_func()
{
   printf("[%04d-%02d-%02d %02d:%02d:%02d] 时间到\n",date.year,date.month,date.day, \
                                                 date.hour, date.minute, date.second);
}
void example_28_rtc(void)
{
    usart1_init();
    rtc_init();
#if 1    
    #if 0
    rtc_time_set(1751677972);   // 时间戳方式设置日期时间
    #else
    //     date_t now = {
    //     .year = 2025,
    //     .month = 7,
    //     .day = 4,
    //     .hour = 12,
    //     .minute = 34,
    //     .second = 56,
    // };
    date_t now=DEFAULT_DATE;
    rtc_date_set(&now);    // 日期方式设置日期时间
    #endif
    #if 0
    rtc_alarm_time_set(rtc_time_get()+10);  //时间戳方式设置闹钟时间 10S后
    #else
    now.second+=10;
    rtc_alarm_date_set(&now);      // 日期方式设置闹钟 10s后
    #endif
#endif    
    rtc_int_callback_set(SEC_HANDLE,sec_func);
    rtc_int_callback_set(ALARM_HANLDE,alarm_func);
    while(1)
    {

    }

}

#endif

#ifdef example_27_enable

void example_27_wdg(void)
{
    uint32_t cnt=0;
    
    usart1_init();
    iwdg_init(4,500);        // 64分频 重装在值500  (4*2^4)*500 / 40000 = 0.8秒= 800ms
    wwdg_init(3,0x5f,0x7f);  //  8分频 窗口值5f 计数器值7f  29.18-57.42ms内
    printf("system init ok\n");
    while(1)
    {
        #if 0 
        /* 1. 单独测试iwdg 800ms内喂狗不会复位 */ 
        printf("working\n");
        delay_ms(900);
        iwdg_feed();
        #endif
        #if 0
        /* 2. 单独测试wwdg 8  29.18-57.42ms内喂狗不会复位 */ 
        printf("working\n");
        delay_ms(28);
        wwdg_feed();
        #endif
        #if 1
        /* 3. 同时使用 */
        delay_ms(10);
        cnt++;
        if(cnt%5==0)       // 50ms
        {
           printf("1 working\n");
           wwdg_feed();
        }
        if(cnt%70==0)      //700ms
        {
           printf("2 working\n");
           iwdg_feed();
           cnt=0;
        }
        #endif

    }

}

#endif

#ifdef example_26_enable

void example_26_adc_int(void)
{
    adc1_init();
    while(1)
    {

    }

}

#endif

#ifdef example_25_enable

uint16_t value=0;
extern uint32_t adc_value1[3]; 
void example_25_adc_poll_03(void)
{
//    adc1_init();
    adc1_dma_init();
    while(1)
    {
//        value=adc1_start_read();
    }

}

#endif

#ifdef example_24_enable

extern uint16_t adc_value[3]; 

void example_24_adc_poll_02(void)
{
//    adc1_init();
    adc1_dma_init();
    while(1)
    {
//         adc_value[0]=adc1_start_read();
//         delay_ms(100);
//         adc_value[1]=adc1_start_read();
//         delay_ms(100);  
//        adc_value[2]=adc1_start_read();
//         delay_ms(100);
    }

}

#endif

#ifdef example_23_enable

uint16_t adc_values=0;

void example_23_adc_poll_01(void)
{
    adc1_init();
    while(1)
    {
         adc_values=adc1_start_read();
         delay_ms(100);     
    }

}

#endif

#ifdef example_22_enable

float freq=0.0;

void test(uint32_t period)
{
    freq=1000000.0/(period);
}

void example_22_tim_ic(void)
{
    /* 1. TIM1 CH1 10KHZ 72M/2/3600=10KHZ 占空比50% */
    tim1_pwm_ch1_init(1,3599);
    set_pwm_ch1_duty_cycle(TIM1,1799);
    /* 2. TIM2 CH1 计数器频率1MHZ 输入捕获 不带溢出处理最大测1Mhz */   
    tim2_ic_ch1_init(71,0xFFFF);
    set_tim_capture_handle(test);
    while(1)
    {

    }
}

#endif

#ifdef example_21_enable

uint16_t val=1000;

void TIM1_CC_IRQHandler()
{
    if(TIM1->SR&1<<1)
    {
        TIM1->CNT=0;
        TIM1->CCR1=val;
    }
    TIM1->SR&=~(1<<1);
}

void example_21_tim_oc(void)
{
    /* 1. 频率500HZ=72M/72/2/CCR1 */
    tim1_oc_ch1_init(71,0XFFFF);
    while(1)
    {

    }
}

#endif

#ifdef example_20_enable

void example_20_tim_pwm(void)
{
    /* 1. TIM1 CH1 10KHZ  72M/2/3600=10KHZ 占空比50% */
    tim1_pwm_ch1_init(1,3599);
    set_pwm_ch1_duty_cycle(TIM1,1799);
    /* 2. TIM2 CH1 10KHZ 72M/72/100=10KHZ 占空比30% */
    tim2_pwm_ch1_init(71,99);
    set_pwm_ch1_duty_cycle(TIM2,70);
    while(1)
    {

    }
}

#endif

#ifdef example_19_enable

void tim1_handle(void)
{
    printf("TIM1 500ms up\n");
}
void tim2_handle(void)
{
    printf("TIM2 1s up\n");
}
void example_19_tim_timing(void)
{
    usart1_init();
    /* 1. TIM1 500MS 定时 */
    tim1_init(7199,5000);
    /* 2. TIM2 1S 定时 */
    tim2_init(7199,10000);
    /* 3. 绑定定时器处理函数 */
    set_tim_timing_handle(0,tim1_handle);
    set_tim_timing_handle(1,tim2_handle);
    while(1)
    {

    }
}

#endif

#ifdef example_18_enable

void example_18_oled(void)
{
    oled_init();   

    /* 1. 显示字符 */
//    oled_put_char(0, 0, '1', EN_8X16); 
//    oled_put_char(0, 1, '2', EN_8X16);
//    oled_put_char(0, 1, '3', EN_16X32);
    /* 2. 显示字符串 */
//    oled_put_string(0, 0, "123456", EN_8X16);
//    oled_put_string(0, 1, "123456", EN_8X16);   
//    oled_put_string(0, 0, "123456", EN_16X32);
//    oled_put_string(0, 1, "123456", EN_16X32);
    /* 3. 显示数字 */
//    oled_put_num(0, 0, 123, EN_8X16);
//    oled_put_num(0, 1, 123, EN_8X16);
//    oled_put_num(0, 1, 12345678, EN_16X32);
    /* 4. 显示汉字 */
//    oled_put_chinese(0, 0, 0, CN_8X8);
//    oled_put_chinese(0, 1, 0, CN_8X8);
    oled_put_chinese(0, 1, 0, CN_16X16);  
//    oled_put_chinese(0, 1, 0, CN_32X32);
    /* 5. 滚动显示 */
//    oled_h_scroll(H_RIGHT,0x02,0x07,0x03);
//    oled_v_scroll_area_set(0x00,32);
//    oled_hv_scroll(HV_RIGHT,0x00,0x02,0x03,1);      
//    oled_hv_scroll(HV_RIGHT,0x02,0x01,0x03,0x12);

}

#endif

#ifdef example_17_enable

void example_17_sw_i2c(void)
{
    sw_i2c_init();
    
    sw_i2c_write_byte(0x78,0x10,0x11);
    
    uint8_t data=sw_i2c_read_byte(0x78,0x10);
    
    uint8_t wr[3]={0x10,0x11,0x12};
    sw_i2c_write(0x78,0x10,wr,sizeof(wr));
    
    uint8_t rd[3];
    sw_i2c_read(0x78,0x10,rd,sizeof(rd));
}

#endif

#ifdef example_16_enable

void example_16_hw_i2c(void)
{
    i2c1_init();
    
    i2c1_master_write_byte(0x78,0x10,0x11);
    
    uint8_t data=i2c1_master_read_byte(0x78,0x10);
    
    uint8_t wr[3]={0x10,0x11,0x12};
    i2c1_master_write(0x78,0x10,wr,sizeof(wr));
    
    uint8_t rd[3];
    i2c1_master_read(0x78,0x10,rd,sizeof(rd));
}

#endif

#ifdef example_15_enable
#include <string.h>

/* 协议相关定义 */
#define FRAME_HEADER1 0X77
#define FRAME_HEADER2 0X88
#define FRAME_TOOTER  0X0D
#define FRAME_MAXSIZE 256
#define CODE1         0XA1      //主机请求
#define CODE2         0XA7      //从机回应
#define CODE3         0x10      //周期
#define CODE4         0x18      //指令

/* 数据结构体 */
typedef struct
{
    uint8_t code;
    uint8_t data_len;
    uint8_t data[FRAME_MAXSIZE-6];
}dataframe;


uint8_t calculate_crc8_direct(uint8_t *data, uint8_t length) {
    const uint8_t poly = 0x07;
    uint8_t crc = 0x00;

    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ poly;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}
/**
 * 数据打包
 */
uint8_t frame_pack(uint8_t code ,uint8_t *data,uint8_t data_len,\
                    uint8_t *out_buf,uint16_t buf_size)
{
    uint8_t pos=0;
    /* 1、检查长度有效性 */
    if(data_len>FRAME_MAXSIZE-6|| buf_size<FRAME_MAXSIZE)
        return 0;
    /* 2、填充帧头 */
    out_buf[pos++]=FRAME_HEADER1;
    out_buf[pos++]=FRAME_HEADER2;
    /* 3、填充功能码 */
    out_buf[pos++]=code;
    /* 4、填充数据长度 */
    out_buf[pos++]=data_len;
    /* 5、填充数据 */
    memcpy(out_buf+pos,data,data_len);
    pos=pos+data_len;
    /* 6、填充校验 */
    out_buf[pos]=calculate_crc8_direct(out_buf,pos);
    pos++;
    /* 7、填充帧尾 */
    out_buf[pos++]=FRAME_TOOTER;

    /* 返回总长度 */
    return pos;
}

int frame_parse(uint8_t *buf,uint8_t len,dataframe *frame)
{
    /* 检查数据段有效性 */
    if(len<6) return -1;
    /* 判断帧头 */
    if(buf[0]!=FRAME_HEADER1||buf[1]!=FRAME_HEADER2) return -1;
    /* 判断功能码是否有效 */
    if(buf[2]!=CODE1&&buf[2]!=CODE4) return -1;
    /* 数据长度 */
    uint8_t data_len=buf[3];
    if(len!=data_len+6) return -1;
    /* 帧尾*/
    if(buf[len-1]!=FRAME_TOOTER) return -1;
    /* 校验码 */
    if(buf[len-2]!=calculate_crc8_direct(buf,len-2)) return -1;
    /* 拷贝数据 */
    frame->code=buf[2];
    frame->data_len=data_len;
    memcpy(frame->data,buf+3,data_len);

    return 0;
}

lwrb_t rb_rx;                         // 定义接收环形缓存区实例对象
uint8_t rb_rx_buf[FRAME_MAXSIZE];     // 定义接收环形缓存区
uint8_t dma_rx_buf[FRAME_MAXSIZE];    // 定义DMA接收缓存区
uint8_t dma_tx_buf[FRAME_MAXSIZE];    // 定义DMA发送缓存区
dataframe frame;                     // 解析后帧数据
uint8_t led_state=0;                 // LED状态

void SysTick_Handler(void)
{
    /* 周期发送 */
    led_state=!LED_STATE;
    uint8_t data[10]={0x03,led_state,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    uint8_t len=frame_pack(CODE3,data,sizeof(data),dma_tx_buf,sizeof(dma_tx_buf));
    usart1_tx_dma(dma_tx_buf,len,0);
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & (1 << 4))                      // 空闲
    {
        DMA1_Channel5->CCR &= ~(1 << 0);            // 关闭DMA
        USART1->SR;
        USART1->DR;
        lwrb_write(&rb_rx,dma_rx_buf, sizeof(dma_rx_buf)- DMA1_Channel5->CNDTR);      //每接收1帧数据写入环形缓存区

        usart1_rx_dma_int(dma_rx_buf,sizeof(dma_rx_buf));
    }
}


void example_15_usart_dma_idle_ringbuf(void)
{
    int ret=-1;

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    systick_init(100);
    led_init();
    usart1_init();
    lwrb_init(&rb_rx,rb_rx_buf,sizeof(rb_rx_buf));
    dma1_ch5_per2mem_init();
    dma1_ch4_mem2per_init();
    usart1_rx_dma_int(dma_rx_buf,sizeof(dma_rx_buf));

    while(1)
    {
        /* 读出数据就解析 */
        uint8_t read_data[128] = { 0 };
        int len = lwrb_read(&rb_rx, read_data, sizeof(read_data));
        if (len > 0) {
            ret = frame_parse(read_data, len, &frame);
            printf("\r\n%d",frame.data_len);
        }
        /* 解析成功一帧数据 处理功能 */
        if (ret == 0) {
            switch (frame.code) {
            case CODE1:
                uint8_t data[10] = { 0x03, 0x04, 0xff, 0xff, 0xff, 0xff, 0xff,
                        0xff, 0xff, 0xff };
                uint8_t len = frame_pack(CODE2, data, sizeof(data), dma_tx_buf,
                        sizeof(dma_tx_buf));
                usart1_tx_dma(dma_tx_buf, len, 0);
                SysTick->CTRL |= 1 << 0;
                ret = 1;
                break;
            case CODE4:
                if (frame.data[1] == 0x01) {
                    LED = 0;
                } else
                    LED = 1;
                break;
            }
        }
    }

}

#endif

#ifdef example_14_enable

uint8_t dma_flag=0;
uint8_t rx_buf[120]={0};
uint32_t rx_cnt=0;
void USART1_IRQHandler(void)
{
    if (USART1->SR & (1 << 5))
    {
            USART1->DR;
    }
    if (USART1->SR & (1 << 4))           // 空闲
    {
        USART1->SR;
        USART1->DR;
        rx_cnt=sizeof(rx_buf)- DMA1_Channel5->CNDTR;// 接收个数
        usart1_rx_dma_int(rx_buf,sizeof(rx_buf));
        dma_flag = 1;   
    }
}
void DMA1_Channel5_IRQHandler(void)
{
    if (DMA1->ISR & 1 << 17)         // 触发传输完成中断
    {
        DMA1->IFCR |= 1 << 17;       // 清除完成中断
//        rx_cnt=sizeof(rx_buf)- DMA1_Channel5->CNDTR;// 接收个数
//        usart1_rx_dma_int(rx_buf,sizeof(rx_buf));
//        dma_flag = 1;
    }
}
void example_14_usart_dma_rx_per2mem(void)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    usart1_init();
    dma1_ch5_per2mem_init();
    usart1_rx_dma_int(rx_buf, sizeof(rx_buf));
    while(1)
    {
        /* 处理 */
        if (dma_flag) {
//            __disable_irq();    //如果你的处理很重要害怕被中断打断
            printf("rx=%ld\r\n", rx_cnt);
            dma_flag = 0;
//            __enable_irq();
        }
    }
}
#endif

#ifdef example_13_enable

void example_13_usart_dma_tx_mem2per(void)
{
    usart1_init();
    dma1_ch4_mem2per_init();
    while(1)
    {
        usart1_tx_dma((uint8_t *)"21312321312312",sizeof("21312321312312"),0);
        delay_ms(1000);
    }
}
#endif

#ifdef example_12_enable

uint8_t buf1[1000];// 源
uint8_t buf2[1000];// 目标
uint8_t dma_flag=0;

void DMA1_Channel1_IRQHandler(void)
{
    if (DMA1->ISR & 1 << 1)         // 触发传输完成中断
    {
        DMA1->IFCR |= 1 << 1;       // 清除完成中断
        dma_flag = 1;               // 置位处理标志
        printf("\n%d\n",(uint16_t)DMA1_Channel1->CNDTR);
    }
//    if (DMA1->ISR & 1 << 2)         // 触发传输一半中断
//    {
//        DMA1->IFCR |= 1 << 2;       // 清除一半中断
//    }
//    if (DMA1->ISR & 1 << 3)         // 触发传输错误中断
//    {
//        DMA1->IFCR |= 1 << 3;       // 清除错误中断
//    }
}

/**
 * [example_12_dma_mem2mem_interrupt DMA实验2 存储器到存储器搬运 中断式(使能dma传输完成中断)]
 */
void example_12_dma_mem2mem_interrupt(void)
{
    usart1_init();
    dma1_ch1_men2men_init();
    memset(buf1,'1',sizeof(buf1));
    DMA1_Channel1->CCR|=1<<0;           // 开启DMA
    while(1)
    {
        printf("\n%d\n",(uint16_t)DMA1_Channel1->CNDTR);
        if(dma_flag){
            printf("%s\r\n",buf2);
            memset(buf2,0,sizeof(buf2));
            dma_flag=0;
            /* 开启下次传输 */
            DMA1_Channel1->CCR&=~(1<<0);        // 关闭DMA
            DMA1_Channel1->CNDTR=sizeof(buf1);  // 重新设置传输大小
            DMA1_Channel1->CCR|=1<<0;           // 开启DMA
        }
    }
}
#endif

#ifdef example_11_enable

uint8_t buf1[1000];// 源
uint8_t buf2[1000];// 目标
/**
 * [example_11_dma_mem2mem DMA实验1 存储器到存储器搬运数据 查询式(不使用dma中断)]
 */
void example_11_dma_mem2mem_poll(void)
{
    int i=0;

    dma1_ch1_men2men_init();
    memset(buf1,'1',sizeof(buf1));

    while(1)
    {
        if(DMA1->ISR&1<<1)              // 检测传输完成标志 每5毫秒检测1次
        {
            DMA1->IFCR|=1<<1;           // 清除完成标志
            memset(buf2,0,sizeof(buf2));
        }
        if(i%100==0)                    // 每500ms 开启1次DMA传输
        {
            DMA1_Channel1->CCR&=~(1<<0);        // 关闭DMA
            DMA1_Channel1->CNDTR=sizeof(buf1);  // 重新设置传输大小
            DMA1_Channel1->CCR|=1<<0;           // 开启DMA
        }
        i++;
        delay_ms(5);
    }
}
#endif


#ifdef example_10_enable

char rx_buf[100]={0};       // 接收区大小
int rx_cnt=0;               // 接收计数
uint8_t rx_flag=0;          // 接收完标志 1完成 0未完成

lwrb_t rb_rx;               // 定义接收环形缓存区实例
uint8_t rb_rx_buf[128];     // 定义接收环形缓存区

void USART1_IRQHandler(void)
{
/* 使用环形缓存区+IDLE中断接收不定长数据——————————————————————————————————————————*/
#if 0
    if (USART1->SR & (1 << 5))           // 接收到数据
            {
        uint8_t ch = USART1->DR;
        lwrb_write(&rb_rx, &ch, 1);      //每接收1个字节写入环形缓存区
        rx_cnt++;
    }
    if (USART1->SR & (1 << 4))           // 空闲
            {
        rx_flag = 1;                     // 接收一帧数据完成
        char ch = USART1->DR;            // 清除IDLE中断
        (void) ch;                       // 消去未使用警告
    }

#else
/* 使用空闲中断接收不定长数据————————————————————————————————————————————————————*/
    {
    /* 一般接收数据写法如下 */
        if(USART1->SR & (1 << 5))             // 接收到数据
        {
            rx_buf[rx_cnt]=USART1->DR;
            if (rx_buf[rx_cnt] == '\n')       // 回车
            {
                rx_cnt = 0;
                rx_flag = 1;
            }
            rx_cnt++;
        }
        if(USART1->SR & (1 << 4))             // 空闲
        {
            rx_cnt = 0;
            rx_flag = 1;
            char ch=USART1->DR;             // 清除IDLE中断
            (void)ch;                       // 消去未使用警告
        }

        if(rx_cnt>sizeof(rx_buf)) rx_cnt=0;
#endif
}

/**
 * [example_10_usart_ringbuffer USART实验3 环形缓冲区+IDLE中断接收不定长数据]
 */
void example_10_usart_ringbuffer(void)
{
    usart1_init();
    lwrb_init(&rb_rx,rb_rx_buf,sizeof(rb_rx_buf));
    while(1)
    {
        if(rx_flag)
        {
#if 1       //使用环形缓存区
            char read_data[128]={0};
            int len = lwrb_read(&rb_rx, read_data, sizeof(read_data));
            if(len>0){
                printf(read_data,"%s\r\n");
            }
            rx_cnt=0;
            rx_flag=0;
#else       // 不使用环形缓存区
            printf(rx_buf,"%s\r\n");
            memset(rx_buf,0,sizeof(rx_buf));
            rx_flag=0;
#endif
        }
    }
}
#endif


#ifdef example_09_enable
/**
 * [example_09_usart_printf USART实验2 实现printf重定向]
 */
void example_09_usart_printf(void)
{
    usart1_init();

    while(1)
    {
        printf("hello printf\r\n");
//        my_printf("www\r\n");
    }
}
#endif

#ifdef example_08_enable
uint8_t rx_ch;

void USART1_IRQHandler(void)
{
    rx_ch=USART1->DR;
}

/**
 * [example_08_usart_polltx_isrrx USART实验1 实现查询式发送和中断式接收]
 */
void example_08_usart_polltx_isrrx(void)
{
    led_init();
    usart1_init();
    usart1_send_str((uint8_t *)"hello usart\r\n");
    while(1)
    {
       if(rx_ch=='1')
       {
           LED=0;
       }else if(rx_ch=='0')
       {
           LED=1;
       }
    }
}
#endif

#ifdef example_07_enable
/**
 * [example_07_delay Systick实验 实现精确延时函数]
 */
void example_07_delay(void)
{
    led_init();
    while(1)
    {
        delay_ms(500);
        LED=!LED;
    }
}
#endif

#if defined(example_05_enable) || defined(example_06_enable)
/**
 * [EXTI15_10_IRQHandler 外部中断服务函数]
 */
void EXTI15_10_IRQHandler(void)
{
   int i=100000;

   /* 检测按键电平 PC13 */
   if((GPIOC->IDR&(1<<13))==0)
   {   
       while(i--);          /* 消抖 */
       if(EXTI->PR&(1<<13)) /* 判断外部中断对应挂起位 */
            LED=!LED;  
   }
#ifdef example_06_enable
   /* PC14 */
   else if((GPIOC->IDR&(1<<14))==0)
   {
       if(EXTI->PR&(1<<14)) /* 判断外部中断对应挂起位 */
            LED=!LED;  
   }
#endif
   /* 清除挂起位 */
   EXTI->PR|=1<<13|1<<14;
}
#endif

#ifdef example_06_enable
void nvic_init(void)
{
    /* 1、配置中断优先级分组为组2 抢占[2bit]0-3 子[2bit]0-3 */ 
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    /* 2、配置中断优先级 */
    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_PRIORITYGROUP_2, 3, 3));
    
}
#endif

#if defined(example_05_enable) || defined(example_06_enable)
/**
 * [exti_init EXTI初始化]
 */
void exti_init(void)
{
    /* 1、使能AFIO的时钟 */
    RCC->APB2ENR|=1<<0;
    /* 2、绑定IO口中断线 PC13->对应13中断线 */
    AFIO->EXTICR[3]|=2<<4;
    /* 3、配置中断触发方式: 下降沿触发 */
    EXTI->FTSR|=1<<13;
    /* 4、开放中断线13的请求 */
    EXTI->IMR|=1<<13;
    /* 5、使能该中断 */
    NVIC->ISER[1]|=1<<8;    //等价NVIC->ISER[1]|=1<<(EXTI15_10_IRQn&0x1f);

#ifdef example_06_enable
    /* 2、绑定IO口中断线 PC14->对应14中断线 */
    AFIO->EXTICR[3]|=2<<8;
    /* 3、配置中断触发方式: 下降沿触发 */
    EXTI->FTSR|=1<<14;
    /* 4、开放中断线14的请求 */
    EXTI->IMR|=1<<14;
    // /* 5、使能该中断 */
    // NVIC->ISER[1]|=1<<8;
#endif
}
#endif

#ifdef example_06_enable
/**
 * [example_06_irq_priority EXTI实验 中断优先级配置]
 */
void example_06_irq_priority(void)
{
    led_init();
    key_init();
    exti_init();
    nvic_init();
}
#endif

#ifdef example_05_enable
/**
 * [example_05_exti_key EXTI实验 按键中断]
 */
void example_05_exti_key(void)
{
     led_init();
     key_init();
     exti_init();
}
#endif

#ifdef example_04_enable
/**
 * [example_04_gpio_bitband GPIO实验4 使用位带操作点亮LED]
 */
void example_04_gpio_bitband (void)
{
    led_init();
    LED=1;      /* 使用位带操作 PB5输出低电平 */
    GPIOB->BRR|=1<<5;
}
#endif

#ifdef example_03_enable
/**
 * [example_03_gpio_remap GPIO实验3 使用重映射后IO点亮LED]
 */
void example_03_gpio_remap(void)
{
    /* 1、使能GPIOB及AFIO时钟 */
    RCC->APB2ENR|=1<<3|1<<0;
    /* 2、将JTAG/SWD调试接口引脚 PB3重映射为普通IO */
    AFIO->MAPR|=2<<24;
    /* 3、配置PB3为推挽输出速度50MHZ */
    GPIOB->CRL&=0XFFFF0FFF;
    GPIOB->CRL|=0X00003000; 
    /* 4、设置PB3输出高电平即LED灯灭 */
    GPIOB->BRR|=1<<3;
}
#endif

#ifdef example_02_enable
/**
 * [example_02_gpio_key GPIO实验2 按键输入]
 */
void example_02_gpio_key(void)
{
    uint8_t key_ret;
    
    key_init();
    led_init();
    
    while(1)
    {
        key_ret = key_scan();
        if(key_ret==1)
        {
            GPIOB_ODR^=1<<5;
        }
    }
}
#endif

#ifdef example_01_enable
/**
 * [example_01_gpio_led GPIO实验1 点亮LED]
 */
void example_01_gpio_led(void)
{
    led_init();
    led_on();
}
#endif

