#ifndef __DRIVER_LCD_GENERIC_H
#define __DRIVER_LCD_GENERIC_H

#include "stdint.h"
// ========================== Describe ================================
// saved in 24w0728
// ========================== Describe ================================

// ========================== Configure ================================
#define LCD_GENERIC_X_MAX_PIXEL 320
#define LCD_GENERIC_Y_MAX_PIXEL 240
#define LCD_GENERIC_CSL GPIOD->BSRR = 0x00100000
#define LCD_GENERIC_CSH GPIOD->BSRR = 0x00000010
#define LCD_GENERIC_DCL GPIOD->BSRR = 0x00200000
#define LCD_GENERIC_DCH GPIOD->BSRR = 0x00000020
#define LCD_GENERIC_REL GPIOD->BSRR = 0x00400000
#define LCD_GENERIC_REH GPIOD->BSRR = 0x00000040

#define LCD_REVERSE_COLOR 0
#define LCD_REVERSE_X 0
#define LCD_REVERSE_Y 0
#define LCD_USE_ILI9341_INIT 1
#define LCD_USE_GENERIC_ADDRESS_FUNCTION 1

#define LCD_GENERIC_COLOR_MODE_565
// #define LCD_GENERIC_COLOR_MODE_666

// ========================== Configure ================================

void lcd_generic_init(void);
void lcd_generic_fullscreencolor(uint32_t color);
void lcd_generic_drawpoint(uint16_t location_x, uint16_t location_y,
                           uint32_t color);
void lcd_generic_buffered_fullscreencolor(uint32_t color);
void lcd_generic_drawblock(uint16_t location_x_start, uint16_t location_y_start,
                           uint16_t location_x_end, uint16_t location_y_end,
                           uint32_t color);
void lcd_generic_drawimage(uint16_t location_x, uint16_t location_y,
                           uint16_t image_width, uint16_t image_height,
                           uint8_t *img);
void lcd_generic_writecolor(uint32_t color);

void lcd_generic_address_set(uint16_t x_start, uint16_t y_start, uint16_t x_end,
                             uint16_t y_end);
#endif
