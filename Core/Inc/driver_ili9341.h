#ifndef __DRIVER_ILI9341_H
#define __DRIVER_ILI9341_H

#include "spi.h"
// ========================== Describe ================================
// saved in 24w0728
// ========================== Describe ================================

// ========================== Configure ================================
#define ILI9341_X_MAX_PIXEL 320
#define ILI9341_Y_MAX_PIXEL 240
#define ILI9341_CSL GPIOD->BSRR = 0x00100000
#define ILI9341_CSH GPIOD->BSRR = 0x00000010
#define ILI9341_DCL GPIOD->BSRR = 0x00200000
#define ILI9341_DCH GPIOD->BSRR = 0x00000020
#define ILI9341_REL GPIOD->BSRR = 0x00400000
#define ILI9341_REH GPIOD->BSRR = 0x00000040
#define ILI9341_COLOR_MODE_565
// #define ILI9341_COLOR_MODE_666

// ========================== Configure ================================

void lcd_ili9341_init(void);
void lcd_ili9341_fullscreencolor(uint32_t color);
void lcd_ili9341_drawpoint(uint16_t location_x, uint16_t location_y,
                           uint32_t color);
void lcd_ili9341_buffered_fullscreencolor(uint32_t color);
void lcd_ili9341_drawblock(uint16_t location_x_start, uint16_t location_y_start,
                           uint16_t location_x_end, uint16_t location_y_end,
                           uint32_t color);
void lcd_ili9341_drawimage(uint16_t location_x, uint16_t location_y,
                           uint16_t image_width, uint16_t image_height,
                           uint8_t *img);
void lcd_ili9341_writecolor(uint32_t color);

void lcd_ili9341_address_set(uint16_t x_start, uint16_t y_start, uint16_t x_end,
                             uint16_t y_end);
#endif
