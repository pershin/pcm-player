/*
 * File:   sd.h
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 8, 2020, 7:20 PM
 */

#ifndef SD_H
#define SD_H

#include <stdint.h>

/* Results */
#define SD_OK    0
#define SD_ERROR 1

uint8_t sd_init(void);
uint8_t sd_read(uint8_t *pointer, uint32_t sector);

#endif /* SD_H */
