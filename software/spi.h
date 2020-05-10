/* 
 * File:   spi.h
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 7, 2020, 7:34 PM
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

extern void spi_init(void);
extern void spi_transmit(uint8_t value);
extern uint8_t spi_receive(void);

#endif /* SPI_H */
