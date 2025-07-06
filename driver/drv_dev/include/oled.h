
#ifndef __OLED_H
#define __OLED_H

#ifdef __cplusplus
extern "C" {
#endif
#include "common.h"
#define OLED_API
/* Includes ------------------------------------------------------------------*/
#define I2C_TYPE                          USE_SW_I2C 
#define USE_HW_I2C                        1
#define USE_SW_I2C                        0 

/* 字体相关参数 ---------------------------------------------------------------*/
#define EN_8X16_WIDTH                     8
#define EN_8X16_HEIGHT                    16
#define EN_16X32_WIDTH                    16
#define EN_16X32_HEIGHT                   32
#define CN_8X8_WIDTH                      8
#define CN_8X8_WIDTH                      8
#define CN_16X16_WIDTH                    16
#define CN_16X16_HEIGHT                   16
#define CN_32X32_WIDTH                    32
#define CN_32X32_HEIGHT                   32
/* OLED相关参数 ---------------------------------------------------------------*/
#define OLED_WIDTH                        128
#define OLED_HEIGHT                       64
/* OLED设备地址 */
#define OLED_DEVICE_ADDR                  0X78
/* OLED控制字节 */
#define OLED_CMD                          0X00
#define OLED_DATA                         0X40

/* 基本命令  ------------------------------------------------------------------*/
#define SET_CONTRAST_CONTROL              0X81        /* 设置对比度 */
#define ENTIRE_DISPLAY_ON                 0xA4        /* 全局显示关 */
#define ENTIRE_DISPLAY_OFF                0xA5        /* 全局显示开 */
#define SET_NORMAL_DISPLAY                0xA6        /* 正常显示 */
#define SET_INVERSE_DISPLAY               0xA7        /* 反色显示 */
#define SET_DISPLAY_ON                    0xAE        /* 显示开 */
#define SET_DISPLAY_OFF                   0XAF        /* 显示关 */
/* 地址设置命令  --------------------------------------------------------------*/
#define SET_LOWER_COLUMN_PAGE(addr)     ((0x00+addr&0x0F)) /* 设置列的起始地址低位 范围0x00-0x0F */
#define SET_HIGHER_COLUMN_PAGE(addr)    ((0x10+(addr>>4)))   /* 设置列的起始地址高位 范围0x10-0x1F */
#define SET_PAGE_START_ADDRESS(page)    ((0xB0+page&0x0F)) /* 设置页起始地址 */
    

enum FONT_SIZE
{
    EN_8X16=0,
    EN_16X32,
    CN_8X8,
    CN_16X16,
    CN_32X32
};
enum H_SCROLL_DIR
{
    H_RIGHT     = 0x26,
    H_LEFT      = 0x27
};  // 水平滚动方向

enum HV_SCROLL_DIR
{
    HV_RIGHT    = 0x29,
    HV_LEFT     = 0x2A
};  // 水平和垂直滚动的方向


/*
 X列坐标 范围 [显示屏宽度/字体宽度]
 Y行坐标 范围 [显示屏高度/字体高度]
 ========坐标示例=========
      --------------- X
      |             |
      |             |
      |             |
    Y |             |
      ---------------
 ========================
 */
/* OLED功能函数 ---------------------------------------------------------------*/
/**
 * [oled_init OLED初始化]
 */
void oled_init(void);
/**
 * [oled_showchar 显示一个字符]
 * @param x     [列坐标   0-127]
 * @param y     [行坐标    0-63]
 * @param chr   [显示的字符]
 * @param size  [字体大小 8x8 16x16 32x32]
 */

void oled_put_char(uint8_t x, uint8_t y, uint8_t ch, enum FONT_SIZE size);
/**
 * [oled_show_string OLED显示字符串]
 * @param x    [X坐标]
 * @param y    [y坐标]
 * @param str  [字符串]
* @param size  [字体大小 8x8 16x16 32x32]
 */
void oled_put_string(uint8_t x,uint8_t y,uint8_t *str,enum FONT_SIZE size);
/**
 * [oled_show_num OLED显示数字]
 * @param x    [X坐标]
 * @param y    [X坐标]
 * @param num  [显示的数]
 * @param size [字体大小 8x8 16x16 32x32]
 */
void oled_put_num(uint8_t x,uint8_t y,uint32_t num,enum FONT_SIZE size);
/**
 * [oled_put_chinese OLED显示汉字]
 * @param x        [X坐标]
 * @param y        [Y坐标]
 * @param cn_index [汉字索引]
 * @param size     [字体大小 8x8 16x16 32x32]
 */
void oled_put_chinese(int8_t x,uint8_t y,uint8_t cn_index,enum FONT_SIZE size);

/**
 * [oled_clear 清空屏幕内容]
 */
void oled_clear(void);
/**
 * @brief 水平滚动显示
 * @param [in] dir 显示方向 H_RIGHT向右 H_LEFT向左
 * @param [in] s_page  起始页地址 
 * @param [in] fr_time 帧间隔时间 速度快慢 0x00-0x07
 * @param [in] e_page 结束页地址
 */
void oled_h_scroll(enum H_SCROLL_DIR dir,uint8_t s_page,uint8_t fr_time,uint8_t e_page);

/**
 * @brief 水平滚动显示
 * @param [in] dir 显示方向 H_RIGHT向右 H_LEFT向左
 * @param [in] s_page  起始页地址 
 * @param [in] fr_time 帧间隔时间 速度快慢 0x00-0x07
 * @param [in] e_page 结束页地址
 */
void oled_hv_scroll(enum HV_SCROLL_DIR dir,uint8_t s_page,uint8_t fr_time,uint8_t e_page,uint8_t offset);

/**
 * @brief 
 * @param [in] area 
 * @param [in] row_num 
 */
void oled_v_scroll_area_set(uint8_t area, uint8_t row_num);

#ifdef __cplusplus
}
#endif

#endif
