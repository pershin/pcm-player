/*
 * File:   sd.c
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 8, 2020, 7:19 PM
 */

#include <avr/io.h>
#include "pins.h"
#include "spi.h"
#include "sd.h"

/* SD send command */
uint8_t sd_cmd(
        uint8_t cmd,
        uint8_t arg0,
        uint8_t arg1,
        uint8_t arg2,
        uint8_t arg3,
        uint8_t crc
        ) {
  uint8_t i, result;

  PORTB &= ~(1 << PIN_SPI_SS);
  spi_receive();

  spi_transmit(cmd);
  spi_transmit(arg0);
  spi_transmit(arg1);
  spi_transmit(arg2);
  spi_transmit(arg3);
  spi_transmit(crc);

  for (i = 10; 0 != i; i--) {
    result = spi_receive();
    if (!(result & 0x80)) {
      break;
    }
  }

  return result;
}

uint8_t sd_read(uint8_t *pointer, uint32_t sector) {
  uint8_t result, value;
  uint16_t i;

  result = SD_ERROR;

  /* CMD17 In the case of a Standard Capacity SD
   * Memory Card, this command, this
   * command reads a block of the size
   * selected by the SET_BLOCKLEN
   * command. 1
   * In the case of a High Capacity Card, block
   * length is fixed 512 Bytes regardless of the
   * SET_BLOCKLEN command. */
  if (0 == sd_cmd(0x51, (uint8_t) (sector >> 24), (uint8_t) (sector >> 16), (uint8_t) (sector >> 8), (uint8_t) (sector), 0x1)) { /* READ_SINGLE_BLOCK */
    for (i = 65535; 0 != i; i--) {
      value = spi_receive();

      if (0xFF != value) {
        break;
      }
    }

    if (0xFE == value) {
      for (i = 512; 0 != i; i--) {
        *pointer++ = spi_receive();
      }

      spi_receive();
      spi_receive();

      result = SD_OK;
    }
  }

  PORTB |= (1 << PIN_SPI_SS);
  spi_receive();

  return result;
}

/* Disk Initialization */
uint8_t sd_init(void) {
  uint8_t i, result;

  /* CMD0 Resets all cards to idle state */
  sd_cmd(0x40, 0x0, 0x0, 0x0, 0x0, 0x95);

  /*
    CMD8 Sends SD Memory Card interface
    condition, which includes host supply
    voltage information and asks the card
    whether card supports voltage. Reserved
    bits shall be set to '0'.
   */
  sd_cmd(0x48, 0x0, 0x0, 0x1, 0xAA, 0x87);

  spi_receive();
  spi_receive();
  spi_receive();

  for (i = 255; 0 != i; i--) {
    /*
      CMD55 Indicates to the card that the next
      command is an application specific
      command rather than a standard
      command
     */
    sd_cmd(0x77, 0x0, 0x0, 0x0, 0x0, 0x1);

    /*
      ACMD41 Sends host capacity support information
      (HCS) and asks the accessed card to
      send its operating condition register
      (OCR) content in the response on the
      CMD line. HCS is effective when card
      receives SEND_IF_COND command.
      Reserved bit shall be set to ‘0’. CCS bit
      is assigned to OCR[30].
     */
    result = sd_cmd(0x69, 0x40, 0x0, 0x0, 0x0, 0x1);

    if (0 == result) {
      break;
    }
  }

  return result;
}
