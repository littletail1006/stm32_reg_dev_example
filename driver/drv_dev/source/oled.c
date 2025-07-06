#include "oled.h"
#include "oledfont.h"
#include "i2c.h"
#include "i2c_io.h"
#include <stdio.h>



/**
 * [oled_write_byte OLED写一个字节 命令/数据]
 * @param ctl  [控制字节 CMD/DATA指令]
 * @param data [指令/数据]
 */
void oled_write_byte(uint8_t ctl, uint8_t data)
{
#if (I2C_TYPE==USE_HW_I2C)
    i2c1_master_write_byte(OLED_DEVICE_ADDR, ctl, data);
#elif(I2C_TYPE==USE_SW_I2C)
    sw_i2c_write_byte(OLED_DEVICE_ADDR, ctl, data);
#endif
}
/**
 * [oled_write_byte 给OLED写多个字节数据]
 * @param data [数据指针]
 * @param size [数据大小]
 */
void oled_write(uint8_t* data, uint8_t size)
{

#if (I2C_TYPE==USE_HW_I2C)
    i2c1_master_write(OLED_DEVICE_ADDR, OLED_DATA, data, size);
#elif(I2C_TYPE==USE_SW_I2C)
    sw_i2c_write(OLED_DEVICE_ADDR, OLED_DATA, data, size);
#endif
}

/**
 * [set_col_addr_page 设置页列址 页寻址模式下]
 * @param col_addr [列地址]
 */
static void set_col_addr_page(uint8_t col_addr)
{
    if(col_addr > OLED_WIDTH - 1)   return;
    /* 设置列起始地址低4位 */
    oled_write_byte(OLED_CMD, SET_LOWER_COLUMN_PAGE(col_addr));
    /* 设置列起始地址高4位 */
    oled_write_byte(OLED_CMD, SET_HIGHER_COLUMN_PAGE(col_addr));
}
/**
 * @brief 设置页起始地址(页寻址模式下)
 * @param [in] addr [页地址]
 */
/* [] */
static void set_page_addr_page(uint8_t page)
{
    if(page > 7) return;
    /* 设置起始页地址 */
    oled_write_byte(OLED_CMD, 0xB0 + page);
}
/**
 * @brief 设置显示光标位置
 * @param [in] page 页地址(0-7)
 * @param [in] col  列地址(0-127)
 */
void oled_set_pos(uint8_t page, uint8_t col)
{
    set_page_addr_page(page);
    set_col_addr_page(col);
}

/**
 * [oled_clear OLED清屏]
 */
void oled_clear(void)
{
    uint8_t buf[128] = {0};

    for(uint8_t i = 0; i < 8; i++) {
        oled_set_pos(i, 0);
        oled_write(&buf[0], sizeof(buf));
    }
}

/**
 * [OLED_ShowChar 显示一个字符]
 * @param x     [列坐标   8x16->0-7  16x32->0-3]
 * @param y     [行坐标   8x16->0-15 16x32->0-2]
 * @param chr   [显示的字符]
 * @param size1 [字体大小 EN_8X16 EN_16X32]
 */
void oled_put_char(uint8_t x, uint8_t y, uint8_t ch, enum FONT_SIZE size)
{

    uint8_t page = 0;
    uint8_t col  = 0;
    uint8_t size_heigth = 0;
    uint8_t size_width = 0;
    uint8_t *ptr_en_font = NULL; /* 指向字模地址 */
    
    if(y > 7 || x > 15)
        return;

    if(size == EN_8X16) {

        col = x * EN_8X16_WIDTH;
        size_heigth = EN_8X16_HEIGHT;
        size_width=EN_8X16_WIDTH;
        ptr_en_font = (uint8_t*)&ascii_font_8x16[0][0];

    } else if(size == EN_16X32) {
        col = x * EN_16X32_WIDTH;
        size_heigth = EN_16X32_HEIGHT;
        size_width=EN_16X32_WIDTH;
        ptr_en_font = (uint8_t*)&ascii_font_16x32[0][0];
    }
    page = y * (size_heigth % 8);  
    
    for(int i = 0; i < size_heigth / 8; i++) {
        oled_set_pos(page + i, col);
        oled_write((ptr_en_font + ch * size_width*size_heigth/8  + i * size_width), size_width);

    }
}
/**
 * @brief 显示字符串
 * @param [in] x 列坐标   8x16->0-7  16x32->0-3
 * @param [in] y 行坐标   8x16->0-7  16x32->0-3
 * @param [in] str 字符串内容
 * @param [in] size 字体大小 EN_8X16 EN_16X32
 */
void oled_put_string(uint8_t x, uint8_t y, uint8_t *str, enum FONT_SIZE size)
{
    while(*str != '\0') {
        if(size == EN_8X16) {
            oled_put_char(x, y, *str, EN_8X16);
            x++;
            if(x > OLED_WIDTH / EN_8X16_WIDTH - 1) {
                x = 0;
                y += OLED_HEIGHT / EN_8X16_HEIGHT;
            }
        } else if(size == EN_16X32) {
            oled_put_char(x, y, *str, EN_16X32);
            x++;
            if(x > OLED_WIDTH / EN_16X32_WIDTH - 1) {
                x = 0;
                y += OLED_HEIGHT / EN_16X32_HEIGHT;
            }
        }

        str++;
    }
}
/**
 * @brief 显示整型数字
 * @param [in] x 列坐标   8x16->0-7  16x32->0-3
 * @param [in] y 行坐标   8x16->0-7  16x32->0-3
 * @param [in] num 数字
 * @param [in] size 字体大小 EN_8X16 EN_16X32
 */
void oled_put_num(uint8_t x, uint8_t y, uint32_t num, enum FONT_SIZE size)
{
    uint8_t str[16] = {0};

    if(num != 0) {
        sprintf((char *)&str, "%d", num);
        if(size == EN_8X16) {
            oled_put_string(x, y, str, EN_8X16);
        } else if(size == EN_16X32) {
            oled_put_string(x, y, str, EN_16X32);
        }
    } else
        oled_put_char(x, y, '0', EN_16X32);

}
/**
 * @brief 显示汉字
 * @param [in] x 列坐标   8x8->0-15  16x16->0-7 32x32->0-3
 * @param [in] y 行坐标   8x8->0-7   16x16->0-3 32x32->0-1
 * @param [in] num 数字
 * @param [in] size 字体大小 CN_8X8 CN_16X16 CN_32X32
 */
void oled_put_chinese(int8_t x, uint8_t y, uint8_t cn_index, enum FONT_SIZE size)
{
    uint8_t page = 0;
    uint8_t col  = 0;
    uint8_t size_width = 0;  
    uint8_t *ptr_cn_font = NULL; /* 指向字模地址 */
    

    if(size == CN_8X8) {
        col = x * CN_8X8_WIDTH;
        size_width = CN_8X8_WIDTH;
        ptr_cn_font = (uint8_t*)&cn_font_8x8[0][0];

    } else if(size == CN_16X16) {
        col = x * CN_16X16_WIDTH;
        size_width = CN_16X16_WIDTH;
        ptr_cn_font = (uint8_t*)&cn_font_16x16[0][0];

    } else if(size == CN_32X32) {
        col = x * CN_32X32_WIDTH;
        size_width = CN_32X32_WIDTH;
        ptr_cn_font = (uint8_t*)&cn_font_32x32[0][0];
    }
    
    page = y * (size_width % 8);  
    
    for(int i = 0; i < size_width / 8; i++) {
        oled_set_pos(page + i, col);
        oled_write((ptr_cn_font + cn_index * size_width * size_width / 8 + i * size_width), size_width);
    }

}


/**
 * @brief 水平滚动显示
 * @param [in] dir 显示方向 H_RIGHT向右 H_LEFT向左
 * @param [in] s_page  起始页地址
 * @param [in] fr_time 帧间隔时间 速度快慢 0x00-0x07
 * @param [in] e_page 结束页地址
 */
void oled_h_scroll(enum H_SCROLL_DIR dir, uint8_t s_page, uint8_t fr_time, uint8_t e_page)
{
    if((dir != H_RIGHT) && (dir != H_LEFT))     return;
    if((s_page > 0x07) || (fr_time > 0x07) || (e_page > 0x07))    return;

    oled_write_byte(OLED_CMD, 0x2E);
    oled_write_byte(OLED_CMD, dir);
    oled_write_byte(OLED_CMD, 0x00);
    oled_write_byte(OLED_CMD, s_page);
    oled_write_byte(OLED_CMD, fr_time);
    oled_write_byte(OLED_CMD, e_page);
    oled_write_byte(OLED_CMD, 0x00);
    oled_write_byte(OLED_CMD, 0xFf);
    oled_write_byte(OLED_CMD, 0x2F);
}

/**
 * @brief 水平滚动显示
 * @param [in] dir 显示方向 H_RIGHT向右 H_LEFT向左
 * @param [in] s_page  起始页地址
 * @param [in] fr_time 帧间隔时间 速度快慢 0x00-0x07
 * @param [in] e_page 结束页地址
 */
void oled_hv_scroll(enum HV_SCROLL_DIR dir, uint8_t s_page, uint8_t fr_time, uint8_t e_page, uint8_t offset)
{
    if((dir != HV_RIGHT) && (dir != HV_LEFT))     return;
    if((s_page > 0x07) || (fr_time > 0x07) || (e_page > 0x07) || offset > 0x3f)    return;

    oled_write_byte(OLED_CMD, 0x2E);

    oled_write_byte(OLED_CMD, dir);
    oled_write_byte(OLED_CMD, 0x01);    /* 0x01水平开*/
    oled_write_byte(OLED_CMD, s_page);
    oled_write_byte(OLED_CMD, fr_time);
    oled_write_byte(OLED_CMD, e_page);
    oled_write_byte(OLED_CMD, offset);
    oled_write_byte(OLED_CMD, 0X00);   /* 水平 列起始 */
    oled_write_byte(OLED_CMD, 0x7F);

    oled_write_byte(OLED_CMD, 0x2F);
}

void oled_v_scroll_area_set(uint8_t area, uint8_t row_num)
{
    if((area > 0x3F) || (row_num > 0x7F))       return;
    oled_write_byte(OLED_CMD, 0xA3);
    oled_write_byte(OLED_CMD, area);
    oled_write_byte(OLED_CMD, row_num);

}
/**
 * @brief oled初始化
 */
void oled_init(void)
{
    /* 1、初始化I2C */
#if (I2C_TYPE==USE_HW_I2C)
    i2c1_init();
#elif(I2C_TYPE==USE_SW_I2C)
    sw_i2c_init();
#endif
    /* 2、配置OLED */
#if 0
    /* */
    oled_write_byte(OLED_CMD, 0xAE); // 关闭OLED -- turn off oled panel
    oled_write_byte(OLED_CMD, 0xD5); // 设置显示时钟分频因子/振荡器频率 -- set display clock divide ratio/oscillator frequency
    oled_write_byte(OLED_CMD, 0x80); // A[3:0] 分频因子, A[7:4] 震荡频率设置 Set Clock as 100 Frames/Sec
    oled_write_byte(OLED_CMD, 0x20); // 设置内存寻址模式 -- Set Memory Addressing Mode (0x00 / 0x01 / 0x02)
    oled_write_byte(OLED_CMD, 0x02); // Page Addressing 设置为页寻址模式
    oled_write_byte(OLED_CMD, 0xA8); // 设置多路传输比率 -- set multiplex ratio (16 to 63)
    oled_write_byte(OLED_CMD, 0x3F); // 1 / 64 duty
    oled_write_byte(OLED_CMD, 0xDA); // 设置列引脚硬件配置 -- set com pins hardware configuration
    oled_write_byte(OLED_CMD, 0x12); // Sequential COM pin configuration，Enable COM Left/Right remap
    oled_write_byte(OLED_CMD, 0xA1); // 设置段重映射 -- Set SEG / Column Mapping     0xA0左右反置（复位值） 0xA1正常（重映射值）
    oled_write_byte(OLED_CMD, 0xC8); // 设置行输出扫描方向 -- Set COM / Row Scan Direction   0xc0上下反置（复位值） 0xC8正常（重映射值）
    oled_write_byte(OLED_CMD, 0x40); // 设置设置屏幕（GDDRAM）起始行 -- Set Display Start Line (0x40~0x7F)
    oled_write_byte(OLED_CMD, 0xD3); // 设置显示偏移 -- set display offset (0x00~0x3F)
    oled_write_byte(OLED_CMD, 0x00); // not offset 偏移值是 0
    oled_write_byte(OLED_CMD, 0x81); // 设置对比度 -- set contrast control register (0x00~0x100)
    oled_write_byte(OLED_CMD, 0xCF); // Set SEG Output Current Brightness
    oled_write_byte(OLED_CMD, 0xD9); // 设置预充电期间的持续时间 -- set pre-charge period
    oled_write_byte(OLED_CMD, 0xF1); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    oled_write_byte(OLED_CMD, 0xDB); // 调整VCOMH调节器的输出 -- set vcomh (0x00 / 0x20 / 0x30)
    oled_write_byte(OLED_CMD, 0x20); // Set VCOM Deselect Level
    oled_write_byte(OLED_CMD, 0x8D); // 电荷泵设置 -- set Charge Pump enable / disable (0x14 / 0x10)
    oled_write_byte(OLED_CMD, 0x14); // 启用电荷泵 Enable charge pump during display on
    oled_write_byte(OLED_CMD, 0xA4); // 全局显示开启(黑屏/亮屏)  (0xA4 根据RAM 内容显示 / 0xA5 每个oled都点亮 全部显示)
    oled_write_byte(OLED_CMD, 0xA6); // 设置显示方式(正常/反显) -- set normal display (0xA6 / 0xA7)
    oled_write_byte(OLED_CMD, 0xAF); // 打开OLED -- turn on oled panel ： OXAE 关闭OLED 休眠模式 0xaf 打开oled
    oled_clear();
#endif
#if 1
    oled_write_byte(OLED_CMD, 0xAE); /* 关闭OLED */
    oled_write_byte(OLED_CMD, 0x00); /* 设置列低4位地址 */
    oled_write_byte(OLED_CMD, 0x10); /* 设置列高4位地址 */
    oled_write_byte(OLED_CMD, 0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    oled_write_byte(OLED_CMD, 0x81); //--set contrast control register
    oled_write_byte(OLED_CMD, 0xCF); // Set SEG Output Current Brightness
    oled_write_byte(OLED_CMD, 0xA1); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    oled_write_byte(OLED_CMD, 0xC8); // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    oled_write_byte(OLED_CMD, 0xA6); // 正常模式
    oled_write_byte(OLED_CMD, 0xA8); //--set multiplex ratio(1 to 64)
    oled_write_byte(OLED_CMD, 0x3f); //--1/64 duty
    oled_write_byte(OLED_CMD, 0xD3); //-set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    oled_write_byte(OLED_CMD, 0x00); //-not offset
    oled_write_byte(OLED_CMD, 0xd5); //--set display clock divide ratio/oscillator frequency
    oled_write_byte(OLED_CMD, 0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    oled_write_byte(OLED_CMD, 0xD9); //--set pre-charge period
    oled_write_byte(OLED_CMD, 0xF1); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    oled_write_byte(OLED_CMD, 0xDA); //--set com pins hardware configuration
    oled_write_byte(OLED_CMD, 0x12);
    oled_write_byte(OLED_CMD, 0xDB); //--set vcomh
    oled_write_byte(OLED_CMD, 0x40); // Set VCOM Deselect Level
    oled_write_byte(OLED_CMD, 0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    oled_write_byte(OLED_CMD, 0x02); //
    oled_write_byte(OLED_CMD, 0x8D); //--set Charge Pump enable/disable
    oled_write_byte(OLED_CMD, 0x14); //--set(0x10) disable
    oled_write_byte(OLED_CMD, 0xA4); // Disable Entire Display On (0xa4/0xa5)
    oled_write_byte(OLED_CMD, 0xA6); // Disable Inverse Display On (0xa6/a7)
    oled_write_byte(OLED_CMD, 0xAF);
    oled_write_byte(OLED_CMD, 0xA6); //正常显示
    oled_write_byte(OLED_CMD, 0xC8); //正常显示
    oled_write_byte(OLED_CMD, 0xA1); //正常显示
    oled_clear();
#endif
}
