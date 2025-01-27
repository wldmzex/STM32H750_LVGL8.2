
#include "driver_genericLCD.h"
#include "spi.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include <stdint.h>
// ========================== Describe ================================
// driver for LCD_GENERIC
//
// saved in 24w0728
// ========================== Describe ================================

// ========================== Configure ================================
void lcd_experienal_spi_write(uint8_t data) {
  SPI1->CR1 |= 0x1;
  SPI1->CR2 = 0x1;
  SPI1->CR1 |= 0x200;
  SPI1->TXDR = data;
  while (!(SPI1->SR & 0x8)) {
  }
  SPI1->IFCR = 0x18;
}

void lcd_generic_spi_write(uint8_t data) {
  LCD_GENERIC_CSL;
  // HAL_SPI_Transmit(&hspi1, &data, 1, 100);
  lcd_experienal_spi_write(data);
  //         spi_readwrite_8bit_soft(data);
  LCD_GENERIC_CSH;
}
void lcd_generic_spi_buffered_write(uint8_t *buffered_data, uint8_t buffsize) {
  LCD_GENERIC_CSL;
  HAL_SPI_Transmit(&hspi1, buffered_data, buffsize, 100);
  // lcd_experienal_spi_write(data);
  //      spi_readwrite_8bit_soft(data);
  LCD_GENERIC_CSH;
}

void lcd_generic_delay(uint16_t delaytime) { HAL_Delay(delaytime); }
// ========================== Configure ================================
//
void lcd_generic_wcd8(uint8_t data) {
  LCD_GENERIC_DCL;
  lcd_generic_spi_write(data);
}
void lcd_generic_wdd8(uint8_t data) {
  LCD_GENERIC_DCH;
  lcd_generic_spi_write(data);
}
#ifdef LCD_GENERIC_COLOR_MODE_666
void lcd_generic_writecolor(uint32_t color) {
  LCD_GENERIC_DCH;
  lcd_generic_spi_write(color >> 16);
  lcd_generic_spi_write(color >> 8);
  lcd_generic_spi_write(color);
}

#endif /* ifdef LCD_GENERIC_co */
#ifdef LCD_GENERIC_COLOR_MODE_565
void lcd_generic_writecolor(uint32_t color) {
  LCD_GENERIC_DCH;
  lcd_generic_spi_write(color >> 8);
  lcd_generic_spi_write(color);
}

#endif /* ifdef LCD_GENERIC_co */
void lcd_generic_reset() {
  LCD_GENERIC_DCH;
  LCD_GENERIC_CSH;
  LCD_GENERIC_CSH;
  LCD_GENERIC_REH;
  lcd_generic_delay(150);
  LCD_GENERIC_REL;
  lcd_generic_delay(20);
  LCD_GENERIC_REH;
}

#if LCD_USE_GENERIC_ADDRESS_FUNCTION

void lcd_generic_address_set(uint16_t x_start, uint16_t y_start, uint16_t x_end,
                             uint16_t y_end) {
  lcd_generic_wcd8(0x2a);
  lcd_generic_wdd8(x_start >> 8);
  lcd_generic_wdd8(x_start);
  lcd_generic_wdd8(x_end >> 8);
  lcd_generic_wdd8(x_end);
  lcd_generic_wcd8(0x2b);
  lcd_generic_wdd8(y_start >> 8);
  lcd_generic_wdd8(y_start);
  lcd_generic_wdd8(y_end >> 8);
  lcd_generic_wdd8(y_end);
  lcd_generic_wcd8(0x2c);
}

#endif

#if LCD_USE_ILI9341_INIT
void lcd_generic_init() {
  lcd_generic_reset();
  lcd_generic_wcd8(0x11);
  lcd_generic_delay(150);

  lcd_generic_wcd8(0x11); // Sleep exit
  lcd_generic_delay(150);

  lcd_generic_wdd8(0x00);

  lcd_generic_wcd8(0xCF);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0XC1);
  lcd_generic_wdd8(0X30);

  lcd_generic_wcd8(0xED);
  lcd_generic_wdd8(0X64);
  lcd_generic_wdd8(0X03);
  lcd_generic_wdd8(0X12);
  lcd_generic_wdd8(0X81);

  lcd_generic_wcd8(0xE8);
  lcd_generic_wdd8(0X85);
  lcd_generic_wdd8(0X11);
  lcd_generic_wdd8(0X78);

  lcd_generic_wcd8(0xF6);
  lcd_generic_wdd8(0X01);
  lcd_generic_wdd8(0X30);
  lcd_generic_wdd8(0X00);

  lcd_generic_wcd8(0xCB);
  lcd_generic_wdd8(0X39);
  lcd_generic_wdd8(0X2C);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0X34);
  lcd_generic_wdd8(0X05);

  lcd_generic_wcd8(0xF7);
  lcd_generic_wdd8(0X20);

  lcd_generic_wcd8(0xEA);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0X00);

  lcd_generic_wcd8(0xC0);
  lcd_generic_wdd8(0X20);

  lcd_generic_wcd8(0xC1);
  lcd_generic_wdd8(0X11);

  lcd_generic_wcd8(0xC5);
  lcd_generic_wdd8(0X31);
  lcd_generic_wdd8(0X3C);

  lcd_generic_wcd8(0xC7);
  lcd_generic_wdd8(0XA9);

  lcd_generic_wcd8(0x3A);
  lcd_generic_wdd8(0X55);

  lcd_generic_wcd8(0x36);
#if LCD_REVERSE_X
  // lcd_generic_wdd8(0x48); // ÊúÆÁ²ÎÊý
#else
#if LCD_REVERSE_Y
#else
  lcd_generic_wdd8(0xE8); // ºáÆÁ²ÎÊý
#endif
#endif
#if LCD_REVERSE_COLOR
  lcd_generic_wcd8(0x20);
#else
  lcd_generic_wcd8(0x21);
#endif

  lcd_generic_wcd8(0xB1);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0X18);

  lcd_generic_wcd8(0xB4);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0X00);

  lcd_generic_wcd8(0xF2);
  lcd_generic_wdd8(0X00);

  lcd_generic_wcd8(0x26);
  lcd_generic_wdd8(0X01);

  lcd_generic_wcd8(0xE0);
  lcd_generic_wdd8(0X0F);
  lcd_generic_wdd8(0X17);
  lcd_generic_wdd8(0X14);
  lcd_generic_wdd8(0X09);
  lcd_generic_wdd8(0X0C);
  lcd_generic_wdd8(0X06);
  lcd_generic_wdd8(0X43);
  lcd_generic_wdd8(0X75);
  lcd_generic_wdd8(0X36);
  lcd_generic_wdd8(0X08);
  lcd_generic_wdd8(0X13);
  lcd_generic_wdd8(0X05);
  lcd_generic_wdd8(0X10);
  lcd_generic_wdd8(0X0B);
  lcd_generic_wdd8(0X08);

  lcd_generic_wcd8(0xE1);
  lcd_generic_wdd8(0X00);
  lcd_generic_wdd8(0X1F);
  lcd_generic_wdd8(0X23);
  lcd_generic_wdd8(0X03);
  lcd_generic_wdd8(0X0E);
  lcd_generic_wdd8(0X04);
  lcd_generic_wdd8(0X39);
  lcd_generic_wdd8(0X25);
  lcd_generic_wdd8(0X4D);
  lcd_generic_wdd8(0X06);
  lcd_generic_wdd8(0X0D);
  lcd_generic_wdd8(0X0B);
  lcd_generic_wdd8(0X33);
  lcd_generic_wdd8(0X37);
  lcd_generic_wdd8(0X0F);
  lcd_generic_wcd8(0x3A);
  lcd_generic_wdd8(0X55);

  lcd_generic_wcd8(0x29);
}
#endif

void lcd_generic_fullscreencolor(uint32_t color) {
  int i, j;
  lcd_generic_address_set(0, 0, LCD_GENERIC_X_MAX_PIXEL - 1,
                          LCD_GENERIC_Y_MAX_PIXEL - 1);
  for (i = 0; i < LCD_GENERIC_X_MAX_PIXEL; i++) {
    for (j = 0; j < LCD_GENERIC_Y_MAX_PIXEL; j++) {
      lcd_generic_writecolor(color);
    }
  }
}
/*uint8_t lcd_generic_buffer[32];
void lcd_generic_buffered_fullscreencolor(uint32_t color) {
  int i, j, buffsize = 0;
  lcd_generics_address_set(0, 0, LCD_GENERIC_X_MAX_PIXEL,
ILI9341_Y_MAX_PIXEL); for (i = 0; i < LCD_GENERIC_X_MAX_PIXEL; i++) { for (j =
0; j < LCD_GENERIC_Y_MAX_PIXEL; j++) { lcd_generic_buffer[buffsize] = color >>
8; buffsize++; lcd_generic_buffer[buffsize] = color >> 8; buffsize++; if
(buffsize == 32) { lcd_generic_spi_buffered_write(lcd_ili9341_buffer, 32);
        buffsize = 0;
      }
    }
  }
  if (buffsize) {
    lcd_generic_spi_buffered_write(lcd_ili9341_buffer, buffsize);
  }
}*/
void lcd_generic_drawpoint(uint16_t location_x, uint16_t location_y,
                           uint32_t color) {
  lcd_generic_address_set(location_x, location_y, location_x, location_y);
  lcd_generic_wdd8(color >> 8);
  lcd_generic_wdd8(color);
}
void lcd_generic_drawblock(uint16_t location_x_start, uint16_t location_y_start,
                           uint16_t location_x_end, uint16_t location_y_end,
                           uint32_t color) {
  int i, j;
  lcd_generic_address_set(location_x_start, location_y_start, location_x_end,
                          location_y_end);
  for (i = location_x_start; i <= location_x_end; i++) {
    for (j = location_y_start; j <= location_y_end; j++) {
      lcd_generic_wdd8(color >> 8);
      lcd_generic_wdd8(color);
    }
  }
}
void lcd_generic_drawimage(uint16_t location_x, uint16_t location_y,
                           uint16_t image_width, uint16_t image_height,
                           uint8_t *image) {
  uint16_t i, j;
  lcd_generic_address_set(location_x, location_y, location_x + image_width - 1,
                          location_y + image_height - 1);
  uint8_t *p = image;
  for (i = location_x; i < location_x + image_width; i++) {
    for (j = location_y; j < location_y + image_height; j++) {

      lcd_generic_wdd8(*p);
      p++;
      lcd_generic_wdd8(*p);
      p++;
    }
  }
}
