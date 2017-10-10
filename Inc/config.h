/*
 * config.h
 *
 *  Created on: Oct 3, 2017
 *      Author: khockuba
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define USB_VBUS_Port 	GPIOA
#define USB_VBUS_Pin		GPIO_PIN_9

#define LED0_Port 		GPIOC
#define LED0_Pin			GPIO_PIN_14

#define LED1_Port		GPIOA
#define LED1_Pin			GPIO_PIN_15

#define SD_SW_Port		GPIOC
#define SD_SW_Pin		GPIO_PIN_5

#define SD_SDIO

#define SD_DET_Port		GPIOB
#define SD_DET_Pin		GPIO_PIN_15

#ifdef SPI

#undef SDIO
#define SD_SPI

#define SD_CS_Pin
#define SD_CS_Port

#define SD_MISO_Pin
#define SD_MISO_Port

#define SD_MOSI_Pin
#define SD_MOSI_Port

#define SD_CLK_Pin
#define SD_CLK_Port

#endif

#endif /* CONFIG_H_ */
