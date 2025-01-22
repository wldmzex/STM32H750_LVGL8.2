
#include "driver_ili9341.h"
#include "spi.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_spi.h"
#include <stdint.h>
// ========================== Describe ================================
// driver for lcd ILI9341
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

void lcd_ili9341_spi_write(uint8_t data) {
  ILI9341_CSL;
  // HAL_SPI_Transmit(&hspi1, &data, 1, 100);
  lcd_experienal_spi_write(data);
  //         spi_readwrite_8bit_soft(data);
  ILI9341_CSH;
}
void lcd_ili9341_spi_buffered_write(uint8_t *buffered_data, uint8_t buffsize) {
  ILI9341_CSL;
  HAL_SPI_Transmit(&hspi1, buffered_data, buffsize, 100);
  // lcd_experienal_spi_write(data);
  //      spi_readwrite_8bit_soft(data);
  ILI9341_CSH;
}

void lcd_ili9341_delay(uint16_t delaytime) { HAL_Delay(delaytime); }
// ========================== Configure ================================
//
void lcd_ili9341_wcd8(uint8_t data) {
  ILI9341_DCL;
  lcd_ili9341_spi_write(data);
}
void lcd_ili9341_wdd8(uint8_t data) {
  ILI9341_DCH;
  lcd_ili9341_spi_write(data);
}
#ifdef ILI9341_COLOR_MODE_666
void lcd_ili9341_writecolor(uint32_t color) {
  ILI9341_DCH;
  lcd_ili9341_spi_write(color >> 16);
  lcd_ili9341_spi_write(color >> 8);
  lcd_ili9341_spi_write(color);
}

#endif /* ifdef ILI9341_co */
#ifdef ILI9341_COLOR_MODE_565
void lcd_ili9341_writecolor(uint32_t color) {
  ILI9341_DCH;
  lcd_ili9341_spi_write(color >> 8);
  lcd_ili9341_spi_write(color);
}

#endif /* ifdef ILI9341_co */
void lcd_ili9341_reset() {
  ILI9341_DCH;
  ILI9341_CSH;
  ILI9341_CSH;
  ILI9341_REH;
  lcd_ili9341_delay(150);
  ILI9341_REL;
  lcd_ili9341_delay(20);
  ILI9341_REH;
}
void lcd_ili9341_address_set(uint16_t x_start, uint16_t y_start, uint16_t x_end,
                             uint16_t y_end) {
  lcd_ili9341_wcd8(0x2a);
  lcd_ili9341_wdd8(x_start >> 8);
  lcd_ili9341_wdd8(x_start);
  lcd_ili9341_wdd8(x_end >> 8);
  lcd_ili9341_wdd8(x_end);
  lcd_ili9341_wcd8(0x2b);
  lcd_ili9341_wdd8(y_start >> 8);
  lcd_ili9341_wdd8(y_start);
  lcd_ili9341_wdd8(y_end >> 8);
  lcd_ili9341_wdd8(y_end);
  lcd_ili9341_wcd8(0x2c);
}
void lcd_ili9341_init() {
  lcd_ili9341_reset();
  lcd_ili9341_wcd8(0x11);
  lcd_ili9341_delay(150);

  lcd_ili9341_wcd8(0x11); // Sleep exit
  lcd_ili9341_delay(150);

  lcd_ili9341_wdd8(0x00);

  lcd_ili9341_wcd8(0xCF);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0XC1);
  lcd_ili9341_wdd8(0X30);

  lcd_ili9341_wcd8(0xED);
  lcd_ili9341_wdd8(0X64);
  lcd_ili9341_wdd8(0X03);
  lcd_ili9341_wdd8(0X12);
  lcd_ili9341_wdd8(0X81);

  lcd_ili9341_wcd8(0xE8);
  lcd_ili9341_wdd8(0X85);
  lcd_ili9341_wdd8(0X11);
  lcd_ili9341_wdd8(0X78);

  lcd_ili9341_wcd8(0xF6);
  lcd_ili9341_wdd8(0X01);
  lcd_ili9341_wdd8(0X30);
  lcd_ili9341_wdd8(0X00);

  lcd_ili9341_wcd8(0xCB);
  lcd_ili9341_wdd8(0X39);
  lcd_ili9341_wdd8(0X2C);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0X34);
  lcd_ili9341_wdd8(0X05);

  lcd_ili9341_wcd8(0xF7);
  lcd_ili9341_wdd8(0X20);

  lcd_ili9341_wcd8(0xEA);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0X00);

  lcd_ili9341_wcd8(0xC0);
  lcd_ili9341_wdd8(0X20);

  lcd_ili9341_wcd8(0xC1);
  lcd_ili9341_wdd8(0X11);

  lcd_ili9341_wcd8(0xC5);
  lcd_ili9341_wdd8(0X31);
  lcd_ili9341_wdd8(0X3C);

  lcd_ili9341_wcd8(0xC7);
  lcd_ili9341_wdd8(0XA9);

  lcd_ili9341_wcd8(0x3A);
  lcd_ili9341_wdd8(0X55);

  lcd_ili9341_wcd8(0x36);
  // lcd_ili9341_wdd8(0xE8); // ºáÆÁ²ÎÊý
  // lcd_ili9341_wdd8(0x48); // ÊúÆÁ²ÎÊý
  lcd_ili9341_wdd8(0xE8); // ºáÆÁ²ÎÊý
  //
  lcd_ili9341_wcd8(0x21);

  lcd_ili9341_wcd8(0xB1);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0X18);

  lcd_ili9341_wcd8(0xB4);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0X00);

  lcd_ili9341_wcd8(0xF2);
  lcd_ili9341_wdd8(0X00);

  lcd_ili9341_wcd8(0x26);
  lcd_ili9341_wdd8(0X01);

  lcd_ili9341_wcd8(0xE0);
  lcd_ili9341_wdd8(0X0F);
  lcd_ili9341_wdd8(0X17);
  lcd_ili9341_wdd8(0X14);
  lcd_ili9341_wdd8(0X09);
  lcd_ili9341_wdd8(0X0C);
  lcd_ili9341_wdd8(0X06);
  lcd_ili9341_wdd8(0X43);
  lcd_ili9341_wdd8(0X75);
  lcd_ili9341_wdd8(0X36);
  lcd_ili9341_wdd8(0X08);
  lcd_ili9341_wdd8(0X13);
  lcd_ili9341_wdd8(0X05);
  lcd_ili9341_wdd8(0X10);
  lcd_ili9341_wdd8(0X0B);
  lcd_ili9341_wdd8(0X08);

  lcd_ili9341_wcd8(0xE1);
  lcd_ili9341_wdd8(0X00);
  lcd_ili9341_wdd8(0X1F);
  lcd_ili9341_wdd8(0X23);
  lcd_ili9341_wdd8(0X03);
  lcd_ili9341_wdd8(0X0E);
  lcd_ili9341_wdd8(0X04);
  lcd_ili9341_wdd8(0X39);
  lcd_ili9341_wdd8(0X25);
  lcd_ili9341_wdd8(0X4D);
  lcd_ili9341_wdd8(0X06);
  lcd_ili9341_wdd8(0X0D);
  lcd_ili9341_wdd8(0X0B);
  lcd_ili9341_wdd8(0X33);
  lcd_ili9341_wdd8(0X37);
  lcd_ili9341_wdd8(0X0F);
  lcd_ili9341_wcd8(0x3A);
  lcd_ili9341_wdd8(0X55);

  lcd_ili9341_wcd8(0x29);
}

void lcd_ili9341_fullscreencolor(uint32_t color) {
  int i, j;
  lcd_ili9341_address_set(0, 0, ILI9341_X_MAX_PIXEL - 1,
                          ILI9341_Y_MAX_PIXEL - 1);
  for (i = 0; i < ILI9341_X_MAX_PIXEL; i++) {
    for (j = 0; j < ILI9341_Y_MAX_PIXEL; j++) {
      lcd_ili9341_writecolor(color);
    }
  }
}
/*uint8_t lcd_ili9341_buffer[32];
void lcd_ili9341_buffered_fullscreencolor(uint32_t color) {
  int i, j, buffsize = 0;
  lcd_ili9341s_address_set(0, 0, ILI9341_X_MAX_PIXEL, ILI9341_Y_MAX_PIXEL);
  for (i = 0; i < ILI9341_X_MAX_PIXEL; i++) {
    for (j = 0; j < ILI9341_Y_MAX_PIXEL; j++) {
      lcd_ili9341_buffer[buffsize] = color >> 8;
      buffsize++;
      lcd_ili9341_buffer[buffsize] = color >> 8;
      buffsize++;
      if (buffsize == 32) {
        lcd_ili9341_spi_buffered_write(lcd_ili9341_buffer, 32);
        buffsize = 0;
      }
    }
  }
  if (buffsize) {
    lcd_ili9341_spi_buffered_write(lcd_ili9341_buffer, buffsize);
  }
}*/
void lcd_ili9341_drawpoint(uint16_t location_x, uint16_t location_y,
                           uint32_t color) {
  lcd_ili9341_address_set(location_x, location_y, location_x, location_y);
  lcd_ili9341_wdd8(color >> 8);
  lcd_ili9341_wdd8(color);
}
void lcd_ili9341_drawblock(uint16_t location_x_start, uint16_t location_y_start,
                           uint16_t location_x_end, uint16_t location_y_end,
                           uint32_t color) {
  int i, j;
  lcd_ili9341_address_set(location_x_start, location_y_start, location_x_end,
                          location_y_end);
  for (i = location_x_start; i <= location_x_end; i++) {
    for (j = location_y_start; j <= location_y_end; j++) {
      lcd_ili9341_wdd8(color >> 8);
      lcd_ili9341_wdd8(color);
    }
  }
}
void lcd_ili9341_drawimage(uint16_t location_x, uint16_t location_y,
                           uint16_t image_width, uint16_t image_height,
                           uint8_t *image) {
  uint16_t i, j;
  lcd_ili9341_address_set(location_x, location_y, location_x + image_width - 1,
                          location_y + image_height - 1);
  uint8_t *p = image;
  for (i = location_x; i < location_x + image_width; i++) {
    for (j = location_y; j < location_y + image_height; j++) {

      lcd_ili9341_wdd8(*p);
      p++;
      lcd_ili9341_wdd8(*p);
      p++;
    }
  }
}
