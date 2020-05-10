.nolist
#include <avr/io.h>
#include "player.h"
#include "pins.h"
.list


.comm command_id, 1, 1 ; extern uint8_t command_id;


;------------------------------------------------------------------------------;
; ISR(TIMER1_COMPA_vect)

.global INT0_vect
INT0_vect:
.func INT0_vect
  push r0
  in r0, AVR_STATUS_ADDR ; Save SREG
  push r0
  push r16
  push r17

  clr r16
  lds r17, PIND

  sbrs r17, PIN_NEXT
  ldi r16, COMMAND_NEXT

  sbrs r17, PIN_PREV
  ldi r16, COMMAND_PREV

  sts command_id, r16

  pop r17
  pop r16
  pop r0
  out AVR_STATUS_ADDR, r0 ; Restore SREG
  pop r0

  reti
.endfunc
