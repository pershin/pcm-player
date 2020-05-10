;------------------------------------------------------------------------------;
; File:   spi.S
; Author: Sergey Pershin <sergey.pershin at hotmail.com>
;
; Created on May 7, 2020, 7:34 PM


.nolist
#include <avr/io.h>
.list


;------------------------------------------------------------------------------;
; SPI Initialization
;
; extern void spi_init(void);

.global spi_init
.func spi_init
spi_init:
  ; Enable SPI, Master
  ldi r16, (1 << SPE) | (1 << MSTR)
  sts SPCR, r16

  ret
.endfunc


;------------------------------------------------------------------------------;
; SPI Master Transmit
;
; extern void spi_transmit(uint8_t value);

.global spi_transmit
.func spi_transmit
spi_transmit:
  ; Start transmission
  sts SPDR, r24 ; SPDR = value

.spi_wait_transmit:
  ; Wait for transmission complete
  lds r18, SPSR
  sbrs r18, SPIF
  rjmp .spi_wait_transmit ; while (!(SPSR & (1 << SPIF)))

  ret
.endfunc


;------------------------------------------------------------------------------;
; SPI Receive
;
; extern uint8_t spi_receive(void);

.global spi_receive
.func spi_receive
spi_receive:
  clr r24
  sbr r24, 0xFF
  call spi_transmit ; spi_transmit(0xFF)

  lds r24, SPDR ; return SPDR

  ret
.endfunc
