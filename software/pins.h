/*
 * File:   pins.h
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 8, 2020, 7:20 PM
 */

#ifndef PINS_H
#define PINS_H

#define PIN_DISPLAY_ENABLE PB0 /* Enable (seven-segment display) */
#define PIN_DISPLAY_LATCH  PB1 /* Latch (seven-segment display) */
#define PIN_SPI_SS         PB2 /* CS (Slave Select) */
#define PIN_SPI_MOSI       PB3 /* DI (Master Out Slave In) */
#define PIN_SPI_MISO       PB4 /* D0 (Master In Slave Out) */
#define PIN_SPI_SCK        PB5 /* SCK (Serial Clock) */
#define PIN_INT0           PD2
#define PIN_LOUT           PD3 /* Left Channel */
#define PIN_ROUT           PD5 /* Right Channel */
#define PIN_NEXT           PD6
#define PIN_PREV           PD7

#endif /* PINS_H */
