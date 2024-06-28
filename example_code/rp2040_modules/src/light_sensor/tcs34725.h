#ifndef _TCS34725_h_
#define _TCS34725_h_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "src/i2c/i2c_tool.h"

// This module is a example for a triple multiplexed RGB sensor

// default adress of tcs34725 RGB sensor
#define TCS34725_ADDR 0x29
                
void init_tcs34725();

void test_tcs34725();

void sample_tcs34725(uint16_t returnvalues[]);

#endif
