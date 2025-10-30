/*
 * functions.h
 *
 *  Created on: Oct 13, 2025
 *      Author: Oleksiy
 */

#ifndef FUNCTIONS_FUNCTIONS_H_
#define FUNCTIONS_FUNCTIONS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


int16_t mapRange(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

#ifdef __cplusplus
}
#endif


#endif /* FUNCTIONS_FUNCTIONS_H_ */
