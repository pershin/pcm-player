/* 
 * File:   display.h
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 10, 2020, 4:05 PM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_track(uint16_t track);
void display_position(uint8_t minutes, uint8_t seconds);

#endif /* DISPLAY_H */
