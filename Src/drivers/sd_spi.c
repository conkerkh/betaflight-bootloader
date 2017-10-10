/*
 * sd_spi.c
 *
 *  Created on: Oct 6, 2017
 *      Author: khockuba
 */
#include "stm32f4xx_hal.h"
#include "config.h"
#include "sd_spi.h"

#define SD_DUMMY_BYTE            0xFF
#define SD_NO_RESPONSE_EXPECTED  0x80

#ifdef SD_SPI
SPI_HandleTypeDef hspix;

void SD_IO_Init(void) {

	GPIO_InitTypeDef gpio;

	HAL_GPIO_WritePin(SD_CS_Port, SD_CS_Pin, GPIO_PIN_SET);
	gpio.Pin = SD_CS_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(SD_CS_Port, &gpio);

	gpio.Pin = SD_MISO_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#ifdef SPI1
	gpio.Alternate = GPIO_AF5_SPI1;
#elif defined(SPI2)
	gpio.Alternate = GPIO_AF5_SPI2;
#elif defined(SPI3)
	gpio.Alternate = GPIO_AF6_SPI3;
#endif
	HAL_GPIO_Init(SD_MISO_Port, &gpio);

	gpio.Pin = SD_MOSI_Pin;
	HAL_GPIO_Init(SD_MOSI_Port, &gpio);

	gpio.Pin = SD_CLK_Pin;
	HAL_GPIO_Init(SD_CLK_Port, &gpio);

#ifdef SD_DET_Pin
	gpio.Pin SD_DET_Pin
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLUP;
	gpio.Alternate = NULL;
	HAL_GPIO_Init(SD_DET_Port, &gpio);
#endif

	hspix.Instance =  SPI_INSTANCE;
	hspix.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspix.Init.Direction = SPI_DIRECTION_2LINES;
	hspix.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspix.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspix.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	hspix.Init.CRCPolynomial = 7;
	hspix.Init.DataSize = SPI_DATASIZE_8BIT;
	hspix.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspix.Init.NSS = SPI_NSS_SOFT;
	hspix.Init.TIMode = SPI_TIMODE_DISABLED;
	hspix.Init.Mode = SPI_MODE_MASTER;
	HAL_SPI_Init(&hspix);

	for (int i = 0; i < 9; i++) {
		SD_IO_Write(SD_DUMMY_BYTE);
	}
}

void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength) {
	 if (HAL_SPI_TransmitReceive(&hspix, DataIn, DataOut, DataLength, 1000) != HAL_OK) {
		 //XD add something here
	 }
}

uint8_t SD_IO_Write(uint8_t data) {
	uint8_t temp;
	if (HAL_SPI_TransmitReceive(&hspix, &data, &temp, 1, 1000) != HAL_OK) {
		return 0xFF;
	}
	return temp;
}

void SD_IO_CSState(uint8_t state) {
	if (state) {
		HAL_GPIO_WritePin(SD_CS_Port, SD_CS_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(SD_CS_Port, SD_CS_Pin, GPIO_PIN_RESET);
	}
}

#endif
