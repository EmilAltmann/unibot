#ifndef _WS2812_8X8_H_
#define _WS2812_8X8_H_

#include "ws2812.pio.h"
#include <math.h>
#include <stdio.h>

// this module implenensts minimal functions for a 8x8 rgb matrix display

void rgb_8x8_matrix_init(uint pin);

void rgb_8x8_matrix_clear();

void rgb_8x8_matrix_update();

void rgb_8x8_matrix_fill(uint32_t color);

void rgb_8x8_matrix_circle( float_t x, float_t y, float_t w, float_t r, uint8_t filled, uint32_t color);

void rgb_8x8_matrix_line( float_t x1, float_t y1, float_t x2, float_t y2, float_t w, uint32_t color);

void rgb_8x8_matrix_square( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t color);

#endif
