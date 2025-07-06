#include "oled.h"
#include "oledfont.h"
#include "i2c.h"
#include "i2c_io.h"
#include <stdio.h>



/**
 * [oled_write_byte OLEDдһ���ֽ� ����/����]
 * @param ctl  [�����ֽ� CMD/DATAָ��]
 * @param data [ָ��/����]
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
 * [oled_write_byte ��OLEDд����ֽ�����]
 * @param data [����ָ��]
 * @param size [���ݴ�С]
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
 * [set_col_addr_page ����ҳ��ַ ҳѰַģʽ��]
 * @param col_addr [�е�ַ]
 */
static void set_col_addr_page(uint8_t col_addr)
{
    if(col_addr > OLED_WIDTH - 1)   return;
    /* ��������ʼ��ַ��4λ */
    oled_write_byte(OLED_CMD, SET_LOWER_COLUMN_PAGE(col_addr));
    /* ��������ʼ��ַ��4λ */
    oled_write_byte(OLED_CMD, SET_HIGHER_COLUMN_PAGE(col_addr));
}
/**
 * @brief ����ҳ��ʼ��ַ(ҳѰַģʽ��)
 * @param [in] addr [ҳ��ַ]
 */
/* [] */
static void set_page_addr_page(uint8_t page)
{
    if(page > 7) return;
    /* ������ʼҳ��ַ */
    oled_write_byte(OLED_CMD, 0xB0 + page);
}
/**
 * @brief ������ʾ���λ��
 * @param [in] page ҳ��ַ(0-7)
 * @param [in] col  �е�ַ(0-127)
 */
void oled_set_pos(uint8_t page, uint8_t col)
{
    set_page_addr_page(page);
    set_col_addr_page(col);
}

/**
 * [oled_clear OLED����]
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
 * [OLED_ShowChar ��ʾһ���ַ�]
 * @param x     [������   8x16->0-7  16x32->0-3]
 * @param y     [������   8x16->0-15 16x32->0-2]
 * @param chr   [��ʾ���ַ�]
 * @param size1 [�����С EN_8X16 EN_16X32]
 */
void oled_put_char(uint8_t x, uint8_t y, uint8_t ch, enum FONT_SIZE size)
{

    uint8_t page = 0;
    uint8_t col  = 0;
    uint8_t size_heigth = 0;
    uint8_t size_width = 0;
    uint8_t *ptr_en_font = NULL; /* ָ����ģ��ַ */
    
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
 * @brief ��ʾ�ַ���
 * @param [in] x ������   8x16->0-7  16x32->0-3
 * @param [in] y ������   8x16->0-7  16x32->0-3
 * @param [in] str �ַ�������
 * @param [in] size �����С EN_8X16 EN_16X32
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
 * @brief ��ʾ��������
 * @param [in] x ������   8x16->0-7  16x32->0-3
 * @param [in] y ������   8x16->0-7  16x32->0-3
 * @param [in] num ����
 * @param [in] size �����С EN_8X16 EN_16X32
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
 * @brief ��ʾ����
 * @param [in] x ������   8x8->0-15  16x16->0-7 32x32->0-3
 * @param [in] y ������   8x8->0-7   16x16->0-3 32x32->0-1
 * @param [in] num ����
 * @param [in] size �����С CN_8X8 CN_16X16 CN_32X32
 */
void oled_put_chinese(int8_t x, uint8_t y, uint8_t cn_index, enum FONT_SIZE size)
{
    uint8_t page = 0;
    uint8_t col  = 0;
    uint8_t size_width = 0;  
    uint8_t *ptr_cn_font = NULL; /* ָ����ģ��ַ */
    

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
 * @brief ˮƽ������ʾ
 * @param [in] dir ��ʾ���� H_RIGHT���� H_LEFT����
 * @param [in] s_page  ��ʼҳ��ַ
 * @param [in] fr_time ֡���ʱ�� �ٶȿ��� 0x00-0x07
 * @param [in] e_page ����ҳ��ַ
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
 * @brief ˮƽ������ʾ
 * @param [in] dir ��ʾ���� H_RIGHT���� H_LEFT����
 * @param [in] s_page  ��ʼҳ��ַ
 * @param [in] fr_time ֡���ʱ�� �ٶȿ��� 0x00-0x07
 * @param [in] e_page ����ҳ��ַ
 */
void oled_hv_scroll(enum HV_SCROLL_DIR dir, uint8_t s_page, uint8_t fr_time, uint8_t e_page, uint8_t offset)
{
    if((dir != HV_RIGHT) && (dir != HV_LEFT))     return;
    if((s_page > 0x07) || (fr_time > 0x07) || (e_page > 0x07) || offset > 0x3f)    return;

    oled_write_byte(OLED_CMD, 0x2E);

    oled_write_byte(OLED_CMD, dir);
    oled_write_byte(OLED_CMD, 0x01);    /* 0x01ˮƽ��*/
    oled_write_byte(OLED_CMD, s_page);
    oled_write_byte(OLED_CMD, fr_time);
    oled_write_byte(OLED_CMD, e_page);
    oled_write_byte(OLED_CMD, offset);
    oled_write_byte(OLED_CMD, 0X00);   /* ˮƽ ����ʼ */
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
 * @brief oled��ʼ��
 */
void oled_init(void)
{
    /* 1����ʼ��I2C */
#if (I2C_TYPE==USE_HW_I2C)
    i2c1_init();
#elif(I2C_TYPE==USE_SW_I2C)
    sw_i2c_init();
#endif
    /* 2������OLED */
#if 0
    /* */
    oled_write_byte(OLED_CMD, 0xAE); // �ر�OLED -- turn off oled panel
    oled_write_byte(OLED_CMD, 0xD5); // ������ʾʱ�ӷ�Ƶ����/����Ƶ�� -- set display clock divide ratio/oscillator frequency
    oled_write_byte(OLED_CMD, 0x80); // A[3:0] ��Ƶ����, A[7:4] ��Ƶ������ Set Clock as 100 Frames/Sec
    oled_write_byte(OLED_CMD, 0x20); // �����ڴ�Ѱַģʽ -- Set Memory Addressing Mode (0x00 / 0x01 / 0x02)
    oled_write_byte(OLED_CMD, 0x02); // Page Addressing ����ΪҳѰַģʽ
    oled_write_byte(OLED_CMD, 0xA8); // ���ö�·������� -- set multiplex ratio (16 to 63)
    oled_write_byte(OLED_CMD, 0x3F); // 1 / 64 duty
    oled_write_byte(OLED_CMD, 0xDA); // ����������Ӳ������ -- set com pins hardware configuration
    oled_write_byte(OLED_CMD, 0x12); // Sequential COM pin configuration��Enable COM Left/Right remap
    oled_write_byte(OLED_CMD, 0xA1); // ���ö���ӳ�� -- Set SEG / Column Mapping     0xA0���ҷ��ã���λֵ�� 0xA1��������ӳ��ֵ��
    oled_write_byte(OLED_CMD, 0xC8); // ���������ɨ�跽�� -- Set COM / Row Scan Direction   0xc0���·��ã���λֵ�� 0xC8��������ӳ��ֵ��
    oled_write_byte(OLED_CMD, 0x40); // ����������Ļ��GDDRAM����ʼ�� -- Set Display Start Line (0x40~0x7F)
    oled_write_byte(OLED_CMD, 0xD3); // ������ʾƫ�� -- set display offset (0x00~0x3F)
    oled_write_byte(OLED_CMD, 0x00); // not offset ƫ��ֵ�� 0
    oled_write_byte(OLED_CMD, 0x81); // ���öԱȶ� -- set contrast control register (0x00~0x100)
    oled_write_byte(OLED_CMD, 0xCF); // Set SEG Output Current Brightness
    oled_write_byte(OLED_CMD, 0xD9); // ����Ԥ����ڼ�ĳ���ʱ�� -- set pre-charge period
    oled_write_byte(OLED_CMD, 0xF1); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    oled_write_byte(OLED_CMD, 0xDB); // ����VCOMH����������� -- set vcomh (0x00 / 0x20 / 0x30)
    oled_write_byte(OLED_CMD, 0x20); // Set VCOM Deselect Level
    oled_write_byte(OLED_CMD, 0x8D); // ��ɱ����� -- set Charge Pump enable / disable (0x14 / 0x10)
    oled_write_byte(OLED_CMD, 0x14); // ���õ�ɱ� Enable charge pump during display on
    oled_write_byte(OLED_CMD, 0xA4); // ȫ����ʾ����(����/����)  (0xA4 ����RAM ������ʾ / 0xA5 ÿ��oled������ ȫ����ʾ)
    oled_write_byte(OLED_CMD, 0xA6); // ������ʾ��ʽ(����/����) -- set normal display (0xA6 / 0xA7)
    oled_write_byte(OLED_CMD, 0xAF); // ��OLED -- turn on oled panel �� OXAE �ر�OLED ����ģʽ 0xaf ��oled
    oled_clear();
#endif
#if 1
    oled_write_byte(OLED_CMD, 0xAE); /* �ر�OLED */
    oled_write_byte(OLED_CMD, 0x00); /* �����е�4λ��ַ */
    oled_write_byte(OLED_CMD, 0x10); /* �����и�4λ��ַ */
    oled_write_byte(OLED_CMD, 0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    oled_write_byte(OLED_CMD, 0x81); //--set contrast control register
    oled_write_byte(OLED_CMD, 0xCF); // Set SEG Output Current Brightness
    oled_write_byte(OLED_CMD, 0xA1); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    oled_write_byte(OLED_CMD, 0xC8); // Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    oled_write_byte(OLED_CMD, 0xA6); // ����ģʽ
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
    oled_write_byte(OLED_CMD, 0xA6); //������ʾ
    oled_write_byte(OLED_CMD, 0xC8); //������ʾ
    oled_write_byte(OLED_CMD, 0xA1); //������ʾ
    oled_clear();
#endif
}
