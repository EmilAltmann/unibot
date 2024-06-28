#ifndef _WS2812_TEST_H_ 
#define _WS2812_TEST_H_ 

#include "ws2812.pio.h"
#include "pico/stdlib.h"
#include "ws2812_8x8.h"
#include "src/imu/qmc5883.h"

// this module contains multiple examples for use of ws2812 led in a 8x8 matrix

void clear_ws2812_current_state();
void test_ws2812_orientation(struct pio_inst inst);
void test_ws2812_fully_on(struct pio_inst inst);
void test_ws2812_color_scrolling(struct pio_inst inst);
void test_ws2812_compass_free_running(uint8_t pin);
void test_ws2812_compass(uint8_t pin);

#endif
