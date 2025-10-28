/*
 * mapRange.c
 *
 *  Created on: Oct 13, 2025
 *      Author: Oleksiy
 */
#include "functions.h"

int16_t mapRange(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

