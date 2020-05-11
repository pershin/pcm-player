/*
 * File:   display.c
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 10, 2020, 4:05 PM
 */

#include <avr/io.h>
#include "pins.h"
#include "spi.h"
#include "display.h"

const uint8_t digits[10] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11110110
};

void update_display(
        uint8_t digit_0,
        uint8_t digit_1,
        uint8_t digit_2,
        uint8_t digit_3
        ) {
  SPCR |= (1 << DORD) | (1 << SPR1);

  spi_transmit(digit_0);
  spi_transmit(digit_1);
  spi_transmit(digit_2);
  spi_transmit(digit_3);

  PORTB |= (1 << PIN_DISPLAY_LATCH);
  PORTB &= ~(1 << PIN_DISPLAY_LATCH);

  SPCR &= ~((1 << DORD) | (1 << SPR1));
}

void display_track(uint16_t track) {
  uint8_t n, digit_0, digit_1, digit_2, digit_3;

  n = track % 10;

  digit_0 = digits[n];
  digit_1 = 0;
  digit_2 = 0;
  digit_3 = 0;

  if (9 < track) {
    n = track / 10 % 10;
    digit_1 = digits[n];
  }

  if (99 < track) {
    n = track / 100 % 10;
    digit_2 = digits[n];
  }

  update_display(digit_0, digit_1, digit_2, digit_3);
}

void display_position(uint8_t minutes, uint8_t seconds) {
  uint8_t digit_0, digit_1, digit_2, digit_3;

  digit_0 = digits[seconds & ~0b11110000];
  digit_1 = digits[seconds >> 4];
  digit_2 = digits[minutes & ~0b11110000] | (1 << 0);
  digit_3 = digits[minutes >> 4];

  update_display(digit_0, digit_1, digit_2, digit_3);
}
