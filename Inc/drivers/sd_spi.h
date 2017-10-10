/*
 * sd_spi.h
 *
 *  Created on: Oct 6, 2017
 *      Author: khockuba
 */

#ifndef DRIVERS_SD_SPI_H_
#define DRIVERS_SD_SPI_H_

#ifdef SD_SPI

void SD_IO_Init(void);
void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength);
uint8_t SD_IO_Write(uint8_t data);
void SD_IO_CSState(uint8_t state);

#endif

#endif /* DRIVERS_SD_SPI_H_ */
