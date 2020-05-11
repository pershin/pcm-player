/*
 * File:   main.c
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 7, 2020, 7:14 PM
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "player.h"
#include "pins.h"
#include "spi.h"
#include "sd.h"
#include "fat32.h"
#include "display.h"

extern uint8_t command_id;
uint16_t current_track;
volatile uint8_t minutes;
volatile uint8_t seconds;
volatile uint16_t buffer_position;
volatile uint16_t position_count;
uint8_t buffer[BUFFER_SIZE];
uint8_t buffer_n;

ISR(TIMER1_COMPA_vect) {
  OCR2B = buffer[buffer_position++]; /* Left channel */
  OCR0B = buffer[buffer_position++]; /* Right channel */

  if (BUFFER_SIZE == buffer_position) {
    buffer_position = 0;
  }

  position_count--;

  if (0 == position_count) {
    position_count = SAMPLE_RATE;
    seconds++;

    /* Fix BCD */
    if (9 < (seconds & ~0b11110000)) {
      seconds += 0b00000110;
    }
  }

  if (0x60 == seconds) { /* 60 */
    seconds = 0;
    minutes++;

    /* Fix BCD */
    if (9 < (minutes & ~0b11110000)) {
      minutes += 0b00000110;
    }
  }
}

void next(void);

void read_to_buffer(void) {
  int16_t offset, read_result;

  if (0 == TIMSK1) {
    return;
  }

  if (0 == buffer_n) {
    if (BUFFER_CHUNK > buffer_position) {
      return;
    }

    buffer_n = 1;
    offset = 0;
  } else {
    if (BUFFER_CHUNK <= buffer_position) {
      return;
    }

    buffer_n = 0;
    offset = BUFFER_CHUNK;
  }

  read_result = file_read(&buffer[offset]);

  if (-1 == read_result) {
    next();
    return;
  }

  if (BUFFER_CHUNK > read_result) {
    next();
  }
}

void play(void) {
  /* Start timer (TIMER1_COMPA_vect) */
  TIMSK1 = (1 << OCIE1A);
}

void stop(void) {
  TIMSK1 = 0;
  buffer_position = 0;
  buffer_n = 0;
  seconds = 0;
  minutes = 0;
  position_count = SAMPLE_RATE;
}

void open(uint16_t track) {
  if (file_open(track)) {
    next();
    return;
  }

  file_read(buffer);
  file_read(&buffer[BUFFER_CHUNK]);
}

void next(void) {
  stop();
  current_track++;
  open(current_track);
  play();
}

void prev(void) {
  stop();
  current_track--;
  open(current_track);
  play();
}

/* Initialization */
void init() {
  /* Set MOSI, SCK and SS output */
  DDRB |= (1 << PIN_DISPLAY_ENABLE) |
          (1 << PIN_DISPLAY_LATCH) |
          (1 << PIN_SPI_SS) |
          (1 << PIN_SPI_MOSI) |
          (1 << PIN_SPI_SCK);

  /* Set PIN_LOUT and PIN_ROUT as output (PWM) */
  DDRD |= (1 << PIN_LOUT) | (1 << PIN_ROUT);

  /* PWM (OCR0B, OCR2B) */
  TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR2A = TCCR0A;

  /* TIMER1_COMPA_vect */
  TCCR1B = (1 << WGM12) | (1 << CS10);

  /* 44.1 kHz */
  OCR1A = F_CPU / SAMPLE_RATE;

  /* Start PWM */
  TCCR0B = (1 << CS00); /* no prescaling */
  TCCR2B = TCCR0B;

  PORTD |= (1 << PIN_INT0) | (1 << PIN_NEXT) | (1 << PIN_PREV);

  EICRA = (1 << ISC01);
  EIMSK = (1 << INT0);

  /* Enable interrupts */
  __asm("sei");

  spi_init();
  sd_init();
  fat32_mount();
}

int main(void) {
  uint16_t old_track;
  uint8_t old_seconds, show_track;

  init();

  command_id = 0;
  old_track = 0;
  old_seconds = 0;
  show_track = 3;

  stop();
  current_track = 1;
  open(current_track);
  play();

  for (;;) {
    if (old_track != current_track) {
      old_track = current_track;
      show_track = 4;
      display_track(current_track);
    }

    if (0 != show_track && old_seconds != seconds && 0 != seconds) {
      show_track--;
    }

    if (0 == show_track && old_seconds != seconds) {
      old_seconds = seconds;
      display_position(minutes, seconds);
    }

    read_to_buffer();

    if (0 != command_id) {
      switch (command_id) {
        case COMMAND_NEXT:
          next();
          break;
        case COMMAND_PREV:
          prev();
          break;
      }

      command_id = 0;
    }
  }

  return 0;
}
