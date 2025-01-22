#ifndef __WLDTOOL_LCD_FRAMEWORK_H_
#define __WLDTOOL_LCD_FRAMEWORK_H_
#include "stdint.h"
#include <driver_ili9341.h>
#include <wldtool_lookuptable.h>
// ========================== Describe ================================
// wldlcd basic graphic render framework
// config abstract function in c file
// render axis:
// [0]=======x========>
// ||
// ||
//  y
// ||
// ||
//  v
//
// saved 24w0726
// ========================== Describe ================================
//
//  ========================== Configure ================================
#define __LCD_INFO_WIDTH         // optional
#define __LCD_INFO_HEIGHT        // optional
#define __WLDLCD_BUFFER_SIZE 360 // default 360
// ========================== Configure ================================
//
// ========================== UTIL ================================
//
#define COLOR_16BIT_RED_565 0xf800
#define COLOR_16BIT_GREEN_565 0x07e0
#define COLOR_16BIT_BLUE_565 0x001f
#define COLOR_16BIT_WHITE_565 0xffff
#define COLOR_16BIT_BLACK_565 0x0000
#define COLOR_16BIT_YELLOW_565 0xFFE0
#define COLOR_16BIT_GRAY0_565 0xEF7D // »ÒÉ«0 3165 00110 001011 00101
#define COLOR_16BIT_GRAY1_565 0x8410 // »ÒÉ«1      00000 000000 00000
#define COLOR_16BIT_GRAY2_565 0x4208

void wldlcd_init(void);
void wldlcd_draw_point(uint16_t location_x, uint16_t location_y,
                       uint32_t color);
void wldlcd_clearscreen(uint32_t color);
void wldlcd_draw_block(uint16_t location_x_start, uint16_t location_y_start,
                       uint16_t location_x_end, uint16_t location_y_end,
                       uint32_t color);
void wldlcd_draw_image(uint16_t location_x, uint16_t location_y,
                       uint16_t image_width, uint16_t image_height,
                       uint8_t *img);
// ========================== UTIL ================================
//
// ========================== NC ================================
void wldlcd_draw_soildBorder(uint16_t x_start, uint16_t y_start, uint16_t x_end,
                             uint16_t y_end, uint16_t width, uint32_t color);
void wldlcd_draw_solid_circle(uint16_t x, uint16_t y, uint16_t radius,
                              uint32_t color);
void wldlcd_draw_line_p2a(uint16_t x_start, uint16_t y_start, uint16_t length,
                          int16_t angle, uint32_t color, uint16_t width);
void wldlcd_draw_string_minium(uint16_t x, uint16_t y, char *string,
                               uint32_t color, uint16_t backgroundcolor);
void wldlcd_draw_string(uint16_t x, uint16_t y, char *string, uint32_t color,
                        uint32_t backgroundcolor, uint8_t fontsize);
// ========================== NC ================================
#endif
