/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dcmi.h"
#include "demos/benchmark/lv_demo_benchmark.h"
#include "dma.h"
#include "eth.h"
#include "gpio.h"
#include "i2c.h"
#include "lv_btn.h"
#include "lv_checkbox.h"
#include "lv_color.h"
#include "lv_disp.h"
#include "lv_hal_disp.h"
#include "lv_label.h"
#include "lv_log.h"
#include "lv_obj.h"
#include "lv_obj_pos.h"
#include "lv_switch.h"
#include "lv_timer.h"
#include "memorymap.h"
#include "spi.h"
#include "src/extra/widgets/led/lv_led.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"
#include "tim.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "driver_genericLCD.h"
#include "wldtool_str.h"
#include <stdint.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BUFF_SIZE (320 * 10 * 2)
static uint8_t buf_1[BUFF_SIZE];
static uint8_t buf_2[BUFF_SIZE];
int test = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

void wld_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                  lv_color_t *color_p) {
  /*The most simple case (but also the slowest) to put all pixels to the screen
   *one-by-one `put_px` is just an example, it needs to implemented by you.*/
  int32_t x, y;
  lcd_generic_address_set(area->x1, area->y1, area->x2, area->y2);
  for (y = area->y1; y <= area->y2; y++) {
    for (x = area->x1; x <= area->x2; x++) {
      lcd_generic_writecolor(color_p->full);
      // lcd_generic_drawpoint(x, y, color_p->full);
      color_p++;
    }
  }

  /* IMPORTANT!!!
   * Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}

// void static wld_flush_cb(lv_display_t *display, const lv_area_t *area,
// uint8_t *px_map) {
///* The most simple case (also the slowest) to send all rendered pixels to the
//* screen one-by-one.  `put_px` is just an example.  It needs to be
//* implemented by you. */
// uint16_t *buf16 =
//(uint16_t *)px_map; /* Let's say it's a 16 bit (RGB565) display */
// int32_t x, y;
// for (y = area->y1; y <= area->y2; y++) {
// for (x = area->x1; x <= area->x2; x++) {
// lcd_generic_drawpoint(x, y, *buf16);
//// wldlcd_draw_point(x, y, *buf16);
// buf16++;
//}
//}
//
//
///* IMPORTANT!!!
//* Inform LVGL that flushing is complete so buffer can be modified again. */
// lv_display_flush_ready(display);
// }
void dialog_u1_8b(char data) {
  uint16_t udelay = 0;
  while (!(USART1->ISR & 0x40)) {
    udelay++;
    if (udelay > 60000)
      return;
  }
  USART1->TDR = data;
}
void my_log_cb(const char *buf) {
  while (*buf != 0) {
    dialog_u1_8b(*buf);
    buf++;
  }
  dialog_u1_8b('\r');
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_ETH_Init();
  MX_TIM3_Init();
  MX_DCMI_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  uint8_t spi_idk = 0;
  HAL_SPI_Transmit(&hspi1, &spi_idk, 1, 100);
  TIM3->CR1 |= 1;
  TIM3->DIER |= 1;
  lcd_generic_init();
  lcd_generic_fullscreencolor(0xffff);
  lv_init();
  lv_log_register_print_cb(my_log_cb);
  static lv_disp_draw_buf_t disp_buf;

  /*Static or global buffer(s). The second buffer is optional*/
  static lv_color_t buf_1[320 * 10];
  static lv_color_t buf_2[320 * 10];

  /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL
   * instead buf_2 */
  lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 320 * 10);

  static lv_disp_drv_t
      disp_drv; /*A variable to hold the drivers. Must be static or global.*/
  lv_disp_drv_init(&disp_drv);   /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
  disp_drv.flush_cb = wld_flush_cb;
  disp_drv.hor_res = 320; /*Set the horizontal resolution in pixels*/
  disp_drv.ver_res = 240; /*Set the vertical resolution in pixels*/

  lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
  lv_obj_t *screen = lv_disp_get_scr_act(disp);
  lv_scr_load(screen);
  // lv_obj_t *led = lv_led_create(screen);
  //  lv_obj_set_x(led, 10);
  //  lv_obj_set_y(led, 10);
  //  lv_obj_set_size(led, 10, 10);
  //  lv_obj_t *label = lv_label_create(screen);
  //  lv_obj_set_x(label, 50);
  //  lv_obj_set_y(label, 50);
  //  lv_obj_set_size(label, 100, 30);
  //  lv_label_set_text(label, "WTF LVGL");
  //  lv_obj_t *cb = lv_checkbox_create(screen);
  //  lv_obj_set_x(cb, 0);
  //  lv_obj_set_y(cb, 80);
  //  lv_obj_t *sw = lv_switch_create(screen);
  //  lv_obj_set_x(sw, 0);
  //  lv_obj_set_y(sw, 80);
  //  lv_obj_add_state(sw, LV_STATE_CHECKED);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int test = 0;
  lv_demo_benchmark();
  while (1) {

    // lv_obj_add_state(sw, LV_STATE_CHECKED);
    lv_timer_handler();
    // lv_obj_clear_state(sw, LV_STATE_CHECKED);
    // lv_timer_handler();

    /* USER CODE END WHILE */
    // lv_log("confused1\r\n");
    // lv_timer_handler();
    // lv_log("confused2\r\n");

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
   */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
   */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
  }

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
  }

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 1;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { test++; }
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void) {
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
   */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
